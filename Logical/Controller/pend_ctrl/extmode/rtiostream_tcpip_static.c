/*
 * File: rtiostream_tcpip_static.c
 *
 * Abstract: This source file implements server-side TCP/IP
 *  communication.
 *
 */

#include <string.h> /* necessary for memcpy and memmove */

#include "rtiostream.h"

/* Various typedefs */
#include "rtwtypes.h"

/* ext_types.h handles (among others) memory- management. */
#include "ext_types.h"

/* In ext_share.h the header of a packet is defined
Knowing the structure of the header is necessary to bypass the
while- loops in the 'higher level files' */
#include "ext_share.h"

/* Interface to the B&R- System. (next two 'includes') */
#include <AsDefault.h>
#include <AsTCP.h>

/* Implementation of the B&R Logging feature */
#include "bur_logging.h"

#ifndef TRUE
# define TRUE                          (1U)
#endif

#ifndef FALSE
# define FALSE                         (0U)
#endif

#ifndef UNUSED_PARAMETER
# define UNUSED_PARAMETER(x) (void)x;
#endif

/***************** DEFINES ****************************************************/

#define SERVER_STREAM_ID (1) /* Allow a single server-side connection */

#ifndef SERVER_PORT_NUM    /* If not defined, use default port. */
# define SERVER_PORT_NUM  (17725U)   /* sqrt(pi)*10000 */
#endif

/*  STAT_BUF_SIZE is the size of the buffers 'rcv_buffer', 'send_buffer1'
    and 'send_buffer2' */
#define STAT_BUFSIZE (1<<20)

/*  STAT_RECVBUF_SIZE is the size of the static buffer 'stat_rcv_buffer'
    which is handed over to the TcpRecv()- function */
#define  STAT_RECVBUF_SIZE (256U)

# define INVALID_SOCKET (-1)
# define SOCK_ERR (-1)

/***************** TYPEDEFS **************************************************/


/** B&R- Typedefs **/

typedef unsigned long SOCKET;
typedef unsigned long ulong_t;

/* Current state of some Socket. */
typedef enum SockState_e {
    state_closed = 0,   /* Socket is closed */
    state_configuring1, /* Configuring Linger- options */
    state_configuring2, /* Configuring no-wait options
                            (Nagle's Algorithm) */
    state_open,         /* Socket is open */
    state_closing       /* Socket is being closed */
} SockState_t;

typedef struct ServerCommsData_tag {
    ulong_t         port;
    SOCKET          listenSock; /* listening socket to accept incoming connections */
    SockState_t     listenState; /* current state of the listening socket */
    SOCKET          sock;       /* socket to send/receive packets */
    SockState_t     sockState;
} ServerCommsData;

typedef struct Buffer_s {
    char      buf_data[STAT_BUFSIZE];
    size_t    buf_load;
}Buffer_t;


/** End B&R- Typedefs **/

/**************** LOCAL DATA *************************************************/

static ServerCommsData ServerData = {SERVER_PORT_NUM, INVALID_SOCKET,
                                    state_closed, INVALID_SOCKET, state_closed};

/** B&R- Local data **/

/* Instance- variables of the necessary AsTcp- FUB's */
static TcpOpen_typ open_var;
static TcpServer_typ server_var;
static TcpClose_typ close_var;
static TcpSend_typ send_var;
static TcpRecv_typ recv_var;
static TcpIoctl_typ ioctl_var;
static tcpLINGER_typ lingeropt_var;

static char ip_address[20];     /* Here the IP- address of the client is stored */

/* Receive buffer for the TcpRecv()- function */
static char stat_rcv_buffer[STAT_RECVBUF_SIZE];

    /* Create dynamic Buffers and initialize:
        void *buf_data = NULL;
        size_t buf_load = 0; */
static Buffer_t rcv_buffer  = {"", 0};
static Buffer_t send_buffer1 = {"", 0};
static Buffer_t send_buffer2 = {"", 0};

/*  send_buffer1 is the buffer for TcpSend().
    This buffer must not be modified during sending process.
    send_buffer2 stores data until a new sending process
    can be started. */

#define SNDBUF_MAX (1<<13)
/*  Maximum size of the two send- buffers together. This is the default
    size of the TCP- Stack in X20 systems. See rtIOStreamSend(...)
    for more details. */

static BOOL recv_hdr_next = TRUE;
/*  recv_hdr_next is to synchronize the rtIOStreamRecv- function.
    If set to TRUE a packet- header is expected.
    The variable is set to TRUE after the connection to the Client was
    established or a complete packet was handed over to the 'higher levels'. */

static BOOL firstPacket = TRUE;
/*  This is the flag to indicate the first packet received.
    For more detail information see function rtIOStreamRcv. */

static BOOL closeOnError = FALSE;
/*  Is set TRUE if TcpRecv() or TcpSend() return an error- status.
    rtIOStreamRcv then returns RTIOSTREAM_ERROR as long as closeOnError
    is set TRUE. This is the only way to correctly close the connetion
    in this case. closeOnError is set FALSE in function closeClientSocket
    which is called by ExtForceDisconnect().
    For more detail information see B&R- External Mode Documentation. */

static BOOL sending = FALSE;
/*  Signals wheter data- sending is in progress or not.
    Global visibility is necessary to know if there's
    sending in progress when closing the connection
    (whole data must be sent before closing). */


/** End B&R- Local data **/

/** B&R- Public data **/

/*  num_calls_rtIOStream is a variable to count
    how often rtIOStreamRecv was called from other
    functions (from the 'higher level files').
    If called more than 'MAX_CALLS' there might
    be a loop in the calling function.
    The variable is reset at the begin of every cycle
    in the main-file. */

int num_calls_rtIOStream = 0;
#define MAX_CALLS (5U)

/** End B&R- Public data **/


/** B&R- Public function prototypes **/

void closeListenSocket();
void closeClientSocket();

/** End B&R- Public function prototypes **/


/** B&R- Local function prototypes **/

static void init_open();
static void init_ioctl_linger(SOCKET ident);
static void init_ioctl_nagle(SOCKET ident);
static void init_serve();
static void init_recv();
static void init_send();
static void init_close(SOCKET ident);

static void SocketWork(
    SOCKET *sock, SockState_t *state,
    BOOL isListenSocket,
    BOOL keepClosed);

static BOOL put_buf(
    Buffer_t *buffer,    /* Pointer to Buffer- Instance */
    void     *src,       /* Pointer to new Data */
    size_t    size);     /* size of new Data */

static BOOL get_buf(
    Buffer_t *buffer,    /* Pointer to Buffer- Instance */
    void     *dst,       /* Pointer to destination */
    size_t    size);     /* size to get */

static BOOL clear_buf(Buffer_t *buffer); /* Free buffers */

/* swap two pointers */
static void swapPtr(Buffer_t **Ptr1, Buffer_t **Ptr2);

/** End B&R- Local function prototypes **/

/***************** PUBLIC FUNCTIONS ******************************************/

/* Function: rtIOStreamOpen =================================================
 * Abstract:
 *  Open the connection with the target.
 */
 /* There is no need to implement the client- side
     so return the server-stream- identifier */

int rtIOStreamOpen(int argc, void * argv[])
{
    return SERVER_STREAM_ID;
}

/* Function: rtIOStreamSend =====================================================
 * Abstract:
 *  Sends the specified number of bytes on the comm line. Returns the number of
 *  bytes sent (if successful) or a negative value if an error occurred. As long
 *  as an error does not occur, this function is guaranteed to set the requested
 *  number of bytes; the function blocks if tcpip's send buffer doesn't have
 *  room for all of the data to be sent
 */

BOOL logSend = 0;	/* boolean for loggerentry*/

int rtIOStreamSend(
    int streamID,
    const void *src,
    size_t size,
    size_t *sizeSent)
{
    int i;  /* counter- variable for the FOR- loop */

	/* start logging  */
	loggingWork();
	
    /*  SendBuf contains the address of the current sending- buffer.
        (This is handed over to TcpSend(...) ) */
    static Buffer_t *SendBuf = &send_buffer1;

    /*  StoreBuf contains the address of the current storing- buffer.
        New data is pushed into this buffer if sending is currently in progress. */
    static Buffer_t *StoreBuf = &send_buffer2;

    if(sizeSent != NULL) /* sizeSent = NULL when called from rtIOStreamRecv */
        *sizeSent = 0;

    UNUSED_PARAMETER(streamID);

    if(sending)
    {       /*  if total buffer- load exceeds boundary SNDBUF_MAX
                (note that in this case also the TCP- Stack of the OS is loaded)
                maybe a bottleneck occurred somewhere
                --> close the connection */
        if( ((SendBuf->buf_load + StoreBuf->buf_load + size) > SNDBUF_MAX) ||
            /* or no more memory available */
            (put_buf(StoreBuf, (void*)src, size) == FALSE) )
        {
            /* sending = FALSE; */
            /* sendBuffer is full, but no need to disconnect,
			 --> following lines get commented to not close the connection*/
			
			/* create loggerentry if this happens */
			if(logSend == 0)
			{
				logSend = 1;
				writeLogEntry( 2, 33311 , "Sendbuffer full, data loss may occur!"); 
			}

			/* closeOnError = TRUE; */
	        /* return RTIOSTREAM_NO_ERROR; */
        }
    }
    else
    {
		logSend = 0;
        /* when rtIOStreamSend is called from rtIOStreamRecv
           (size = 0) and no sending is in progress --> return */
        if(size == 0)return RTIOSTREAM_NO_ERROR;

        if(put_buf(SendBuf, (void*)src, size) == FALSE)
        {   /* no more memory available */
            sending = FALSE;

			/* sendBuffer is full, but no need to disconnect,
			 --> following lines get commented to not close the connection*/

			/* create loggerentry if this happens */
			if(logSend == 0)
			{
				logSend = 1;
				writeLogEntry( 2, 33311 , "Sendbuffer full, data loss may occur!"); 
			}

			/* closeOnError = TRUE; */
	        /*return RTIOSTREAM_NO_ERROR; */
		}

        init_send(SendBuf->buf_data, SendBuf->buf_load);

        sending = TRUE;
    }

    for(i = 0;i <= 1; i++)
    {
        TcpSend(&send_var);
        if( (send_var.status == ERR_OK) ||	/* Everything is fine --> Data sent */
			(send_var.status == tcpERR_SENTLEN) )	/* Not all data sent --> no problem */
        {
            get_buf(SendBuf, NULL, send_var.sentlen);
            if(SendBuf->buf_load > 0);
            else if(StoreBuf->buf_load > 0)
            {
                swapPtr((Buffer_t**)&SendBuf, (Buffer_t**)&StoreBuf);
            }
            else
            {
                sending = FALSE;
                break;
            }

            init_send(SendBuf->buf_data, SendBuf->buf_load);
        }
        else if( (send_var.status == ERR_FUB_BUSY) || /* Fub is Busy --> sending data */
					/* Tcp- Stack full --> Try again later */
				 (send_var.status == tcpERR_WOULDBLOCK) )break;
        else
        {
            /* error occurred while sending --> close connection */
            sending = FALSE;
            closeOnError = TRUE;
            return RTIOSTREAM_ERROR;
        }
    }

	if(sizeSent != NULL)
	{
		*sizeSent = size;
	}
	
    return RTIOSTREAM_NO_ERROR;
}


/* Function: rtIOStreamRecv ================================================
 * Abstract: receive data
 *
 */

BOOL logRecv = 0;	/* boolean for loggerentry*/

int rtIOStreamRecv(
    int      streamID,
    void   * dst,
    size_t   size,
    size_t * sizeRecvd)
{
	boolean_T logged = 0; /* boolean for loggerentry*/
	*sizeRecvd = 0;
	num_calls_rtIOStream++;

    /* detect failures and loops
          in the 'higher-level-functions',
          also packet(header)- synchronism is checked */

    if( (closeOnError) || /* Socket has to be closed */
        (streamID != SERVER_STREAM_ID) ||   /* failure */
        (recv_hdr_next && (size != sizeof(PktHeader))) || /* synchronism */
        (num_calls_rtIOStream > MAX_CALLS) )
        /*  too much calls per sample --> maybe the function
            is called in a loop */
    {
        return RTIOSTREAM_ERROR;
    }

    /* Check the state of the socket */
    /* Open new connection if necessary */

    if(ServerData.sockState != state_open)
    {
        /* Attempt to open new connection */
        SocketWork(&ServerData.sock, &ServerData.sockState, FALSE, FALSE);
        if(ServerData.sockState != state_open)
        { /* if there's still no connection return */
            return RTIOSTREAM_NO_ERROR;
        }
    }

    /* Before receiving --> poll sending */

    rtIOStreamSend(streamID, NULL, 0, NULL);

    /* Begin receiving - connection to the client present */

    TcpRecv(&recv_var);

    if(recv_var.status == ERR_OK)
    {
        if(recv_var.recvlen == 0)
        {   /* Connection was closed by client */
            closeOnError = TRUE;
            return RTIOSTREAM_ERROR;
        }

		/* 	data is present now (more than 0 Bytes)
       		--> put it into the buffer */
	    if(put_buf(&rcv_buffer, stat_rcv_buffer, recv_var.recvlen) == FALSE)
	    {
	        /* if put_buf returns FALSE --> no more memory available
	           --> close the connection an return an error */

			if(logRecv == 0)
			{
				logRecv = 1;
				writeLogEntry( 2, 33312 , "Receivebuffer full, data loss may occur!"); 
			}

			/* closeOnError = TRUE; */
	        /* return RTIOSTREAM_ERROR; */
	    }
		else
		{
			logRecv = 0;
		}
    }
    else if( (recv_var.status == ERR_FUB_BUSY) ||
             (recv_var.status == tcpERR_NO_DATA) );
    else
    {
        /* Some error occurred while receiving --> close the connection */
        closeOnError = TRUE;
        return RTIOSTREAM_ERROR;
    }

    /* now let's see if a full packet is in the buffer */
    {
        static size_t bytesToTransfer = 0;
		static size_t fullPacket = 0;


        if(recv_hdr_next && (rcv_buffer.buf_load >= sizeof(PktHeader)) )
        {   /* full packetheader is available in buffer */
            PktHeader *temp_hdr;
			recv_hdr_next = FALSE;
			temp_hdr = (PktHeader*)rcv_buffer.buf_data;
            if(!firstPacket)
			{
			    fullPacket = sizeof(PktHeader) + temp_hdr->size;
                /* ! hack ! ... any other suggestion ?
                     --> Mathworks reads the header this way in file ext_svr.c
                    (Revision: 1.1.6.14)
                */
			}
			else
			{
                /*  The very first packet should contain the string: 'ext-mode'.
                    It is used as a flag to start the handshaking process.
                    But the key is: It's not organized like a normal packet(Header + Body)
                    --> it's just a string, so we can't analyze the header.
                    Lenght of the first packet is equal to length of packet-header.
                    firstPacket is set TRUE after a new connection to the client
                    was established.
                */
				fullPacket = sizeof(PktHeader);
				firstPacket = FALSE;
			}
        }

        if(!recv_hdr_next)
        {   /* now we already have the header, let's see if the whole
               packet is available */

            /* if full packet is available in buffer -->
               start handing over packet to the 'higher level functions' */
            if(rcv_buffer.buf_load >= fullPacket && fullPacket != 0)
            {
                bytesToTransfer = fullPacket;
                fullPacket = 0;
            }
        }

        if(bytesToTransfer > 0)
        {
            if(!get_buf(&rcv_buffer, dst, size))
            {   /* getting data failed --> close the Socket */
                closeOnError = TRUE;
                return RTIOSTREAM_ERROR;
            }
            *sizeRecvd = size;
            bytesToTransfer -= size;
			if(bytesToTransfer == 0)recv_hdr_next = TRUE;
        }
    }
    return RTIOSTREAM_NO_ERROR;
}

/* Function: rtIOStreamClose ================================================
 * Abstract: close the connection.
 *
 */

  /*  finalShutdown is TRUE if ExtShutDown()
    was called during the _EXIT- procedure. The _EXIT-
    procedure is called when the Task is deinstalled.
    In special cases rtIOStreamClose() is set FALSE. */

BOOL finalShutdown = TRUE;

int rtIOStreamClose(int streamID)
{
    if(finalShutdown)
    {
        while(  (ServerData.sockState != state_closed) ||
                (ServerData.listenState != state_closed) )
        {
            SocketWork(&ServerData.sock, &ServerData.sockState, FALSE, TRUE);
        }
    }

    UNUSED_PARAMETER(streamID);
    return 1;
}

/** B&R- Public functions **/

void closeClientSocket()
{
    init_close(ServerData.sock);
    ServerData.sockState = state_closing;

    closeOnError = FALSE;

    SocketWork(&ServerData.sock, &ServerData.sockState, FALSE, FALSE);
}

void closeListenSocket()
{
    init_close(ServerData.listenSock);
    ServerData.listenState = state_closing;
}

/** End B&R- Public functions **/

/** B&R- Local functions **/

/*  The following functions with prefix 'init_' are needed
    to konfigure the instance- variables for the tcp- functions
    from the library 'AsTcp'. */

static void init_send(void* src, size_t len)
{
	send_var.enable = TRUE;
	send_var.ident = ServerData.sock;
	send_var.flags = 0;
	send_var.pData = (UDINT)src;
	send_var.datalen = len;
}

static void init_close(SOCKET ident)
{
	close_var.enable = TRUE;
	close_var.how = 0; 		/* shutdown as given in "Linger-options" (IO- Control) */
	close_var.ident = ident;
}

static void init_recv()
{
    recv_var.enable = TRUE;
	recv_var.ident = ServerData.sock;
	recv_var.pData = (UDINT)stat_rcv_buffer;
	recv_var.datamax = sizeof(stat_rcv_buffer);
	recv_var.flags = 0;
}

static void init_serve()
{
    server_var.enable = TRUE;
	server_var.ident = ServerData.listenSock;
	server_var.backlog = 1;
	server_var.pIpAddr = (UDINT)&ip_address;
}

static void init_ioctl_linger(SOCKET ident)
{
    ioctl_var.enable = TRUE;			/* Enable FUB */
	ioctl_var.ident = ident; 			/* ident of socket */
	ioctl_var.ioctl = tcpSO_LINGER_SET;	/* IO-Control --> set Linger-options */

	lingeropt_var.lLinger = 3;			/* Linger-Time 3 sek.
										   Wait 3 sek. before closing the socket.
										   --> if cycle- time is e.g. 400µs the NIC
										   could have problems sending packets that
										   are currently in TCP-
										   (or IP- or ETH- ... however) Stack */

	lingeropt_var.lOnOff = 1;			/* Linger-option ON */

	ioctl_var.pData = (UDINT)&lingeropt_var;
	ioctl_var.datalen = sizeof(lingeropt_var);
}

static void init_ioctl_nagle(SOCKET ident)
{
    UDINT no_delay;

    ioctl_var.enable = TRUE;			    /* Enable FUB */
	ioctl_var.ident = ident; 			    /* ident of socket */
	ioctl_var.ioctl = tcpTCP_NODELAY_SET;	/* IO-Control --> set NO-DELAY */

    no_delay = 1;                           /* Disable Nagle's Algorithm */

	ioctl_var.pData = (UDINT)&no_delay;
	ioctl_var.datalen = sizeof(no_delay);
}

static void init_open()
{
	open_var.enable = TRUE;			    /* Enable FUB */
	open_var.pIfAddr = 0;			    /* Bind Socket to any IP- address */
	open_var.port = ServerData.port;	/* Port-Nr. */
	open_var.options = tcpOPT_REUSEADDR;/* Reuse address */
}

/*  Function put_buf()
    This function puts data pointed to by 'src'
    and of size 'size' at the back of a buffer 'buffer'. */

static BOOL put_buf(
    Buffer_t *buffer,    /* Pointer to Buffer- Instance */
    void     *src,       /* Pointer to new data */
    size_t    size)      /* size of new data */
{
    size_t size_needed;

    if(size == 0)return TRUE;
    if((src == 0) || (buffer == NULL))return FALSE;

    size_needed = buffer->buf_load + size;
    
    if(size_needed > sizeof(buffer->buf_data))
        /* Buffer is too small to store data */
    {
        return FALSE;
    }

    /* Copy new data to the buffer */

    memcpy((void*)(buffer->buf_data + buffer->buf_load), src, size);
    buffer->buf_load = size_needed;

    return TRUE;
}

static BOOL get_buf(
    Buffer_t *buffer,    /* Pointer to Buffer- Instance */
    void     *dst,       /* Pointer to destination */
    size_t    size)      /* size to get */
{

    /* Check if parameters are useful */
    if(size == 0)return TRUE;
    if((buffer == NULL) || (buffer->buf_data == NULL) ||
        (size > buffer->buf_load))return FALSE;

    /* Copy if dst != NULL */
    if(dst != NULL)
        memcpy(dst, buffer->buf_data, size);

    buffer->buf_load -= size;

    memmove(buffer->buf_data, buffer->buf_data + size, buffer->buf_load);

    return TRUE;
}

static BOOL clear_buf(Buffer_t *buffer)
{
    if(!(buffer))return TRUE;

    buffer->buf_load = 0;

    return TRUE;
}

static void swapPtr(Buffer_t **Ptr1, Buffer_t **Ptr2)
{
    Buffer_t *tmp_ptr;

    tmp_ptr = *Ptr1;
    *Ptr1 = *Ptr2;
    *Ptr2 = tmp_ptr;
}


/* Function: SocketWork =================================================
 * Abstract:
 *  Called when the target is not currently connected to the host, this
 *  function attempts to open the connection.
 *
 *  In the case of sockets, this is a passive operation in that the host
 *  initiates contact, the target simply listens for connection requests.
 *
 * NOTES:

 * When polling, there may be no open requests pending.  In this case, this
 * function returns without making a connection; this is not an error.
 */
static void SocketWork(
    SOCKET *sock, SockState_t *state,
    BOOL isListenSocket,
    BOOL keepClosed)
{
    /* Check parameters first */
    if((sock == 0) || (state == 0) || (*state == state_open))return;

    switch(*state)
    {
        case state_closed:
            if(isListenSocket == FALSE) /* (isListenSocket = FALSE) --> Process the "Data"- Socket */
            {
                if(ServerData.listenState != state_open)
                {
                    SocketWork(&ServerData.listenSock,
                               &ServerData.listenState,
                               TRUE, keepClosed);
                    if(ServerData.listenState != state_open)
                        break; /* Listen- Socket still closed */
                }

                /* So the listen- Socket is open --> begin serving */

                init_serve();
                /* Poll for some Client who wants to connect */
                TcpServer(&server_var);
                if(server_var.status == ERR_OK)	/* Everything is fine --> Client connected to Server */
                {
                    *sock = server_var.identclnt;
                    /* Initialize IO- options for recently obtained socket (Client) */
                    init_ioctl_linger(*sock);
                    *state = state_configuring1;
                    /* No need to place a "break;" here */
                }
                else if(server_var.status == ERR_FUB_BUSY)break;  /* Fub is Busy
                                                --> Keep on waiting for Client to connect */
                else
                {
                    /* An error occurred while serving --> close listening- Socket */
                    init_close(ServerData.listenSock);
                    ServerData.listenState = state_closing;
                    break;
                }
            }
            else /* (isListenSocket = TRUE) --> Process the "Listen"- Socket */
            {
                if(keepClosed)break;
                init_open();            /* Initialize opening */
                TcpOpen(&open_var);		/* Generate Socket */

                if(open_var.status == ERR_OK)	/* Everything is fine */
                {
                    *sock = open_var.ident;
                    /* Initialize IO- options for recently created socket (Server) */
                    init_ioctl_linger(*sock);
                    *state = state_configuring1;
                    /* No need to place a "break;" here */
                }
                else if(open_var.status == ERR_FUB_BUSY)break;  /* Fub is Busy */
                else
                {
                    /* An error occurred */
                    /* No Socket created --> Socket closed */
                    *sock = INVALID_SOCKET;
                    *state = state_closed;
                    break;
                }
            }

        case state_configuring1:	 /* Adjust IO-Options (IO Control) */
			TcpIoctl(&ioctl_var);
			if(ioctl_var.status == ERR_OK)	/* Everything is fine */
			{
				init_ioctl_nagle(*sock);
				*state = state_configuring2;
			}
			else if(ioctl_var.status == ERR_FUB_BUSY)break;  /* Fub is Busy */
			else
			{
				/* Error while configuration --> Close the Connection */
				init_close(*sock);
				*state = state_closing;
				break;
			}

        case state_configuring2:	 /* Adjust IO-Options (IO Control) */
			TcpIoctl(&ioctl_var);
			if(ioctl_var.status == ERR_OK)	/* Everything is fine */
			{
			    /* Finally the Socket was created successfully */
				*state = state_open;
				recv_hdr_next = TRUE;
				firstPacket = TRUE;
				init_recv();
				break;
			}
			else if(ioctl_var.status == ERR_FUB_BUSY)break;  /* Fub is Busy */
			else
			{
				/* Error while configuration --> Close the Connection */
				init_close(*sock);
				*state = state_closing;
			}

        case state_closing:

            /*  If there's still data pending in the send- Buffers
                or sending is in progress and no error occurs
                --> don't close Socket */
            if( !isListenSocket && sending &&
                (rtIOStreamSend(SERVER_STREAM_ID, NULL, 0, NULL) != RTIOSTREAM_ERROR))
                    break;

            TcpClose(&close_var);
			if(close_var.status == ERR_OK)	/* Everything is fine --> Connection closed */
			{
				*sock = INVALID_SOCKET;
				*state = state_closed;
				if(!isListenSocket)
				{
                    clear_buf(&rcv_buffer);
                    clear_buf(&send_buffer1);
                    clear_buf(&send_buffer2);
				}
				break;
			}
			else if(close_var.status == ERR_FUB_BUSY)break;  /* Fub is Busy --> closing connection */
			else
			{
				/* Error while closing --> assume that the
				   Socket is invalid anyway */
				*sock = INVALID_SOCKET;
				*state = state_closed;
				break;
			}

        case state_open:
            break;

        default:
            /* Probably an error occurred somewhere
               In this case try to close the Listen- Socket */
            init_close(*sock);
            *state = state_closing;
            break;
    }
}

/** End B&R- Local functions **/
