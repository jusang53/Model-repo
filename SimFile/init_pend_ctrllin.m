%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% 
%%% Inverted Pendulum on a cart:
%%% Linear closed loop control and 
%%% simulation of the linear and non-linear model
%%%
%%% Required toolboxes: 
%%% Simulink, Control Systems
%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%
%%% Example for Automation Studio Target for Simulink
%%% Bernecker + Rainer Industrieelektronik Ges.m.b.H.
%%%
%%% created:    02.03.2010
%%% modified:   16.03.2010
%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Initializing simulation parameters
% Constants
g = 9.81;   % m/s^2 ... gravitational constant
Ts = 0.01;  % Sample time of controller

% Parameters
M = 1000;   % kg ... mass of cart
m = 0.1;    % kg ... mass of pendulum (<< M)
l = 0.5;    % m  ... length of pendulum
dv = 0.0;   % Nms/rad ... bearing damping (speed proportional friction)

% State variables & initial values
x10 = 0;   % m     ... position of cart
x20 = 0;   % m/s   ... speed of cart
x30 = 0.01;   % rad   ... angle of pendulum (swing up necessary)
x40 = 0;   % rad/s ... angular speed of pendulum
x0 = [x10; x20; x30; x40];
xlin0 = [x10; x20; x30; x40];

%% State space equations
A = [0 1      0 0;
     0 0 -m*g/M 0;
     0 0      0 1;
     0 0    g/l 0];
b = [0;
      1/M;
      0;
      -1/(M*l)];
c = [1 0;
     0 0;
     0 1;
     0 0];
d = [0;0];

ssPend_y = ss(A,b,c',d);                % Only feed y=[x, theta] to output
ssPend = ss(A,b,eye(4),zeros(4,1));     % Feed all states to output for state regulator
tfPend = tf(ssPend_y);
ssPend_disc = c2d(ssPend,Ts);           % Dicretize model for controller design

% Compile C-MEX S-function
% if exist('csfunc_pend.c','file')        % Check if C-MEX S-function is available
%     if (~exist('csfunc_pend.mexw32','file') || ~exist('csfunc_pend.mexw64','file'))
%         mex('csfunc_pend.c');
%     end
% end
        
%% Eigenvalues of uncontrolled system
disp('Eigenvalues of uncontrolled system:')
eig(A)

%% Closed-loop controller (state regulator with 'acker')
disp('Designing linear state feedback controller (acker)')
%%% closed-loop controller (state regulator)
% desired eigenvalues
disp('Desired discrete eigenvalues:')
lambda = exp(Ts*[-4; -5; -1+1.5i; -1-1.5i])    %Transfer eigenvalues from continuous to discrete time domain
keig = acker(ssPend_disc.A, ssPend_disc.b, lambda);
Veig = 1/(c(:,1)' * inv(eye(4)-ssPend_disc.A+ssPend_disc.b*keig) * ssPend_disc.b + d(1,:));

disp('Eigenvalues of controlled system (acker):')
eig(ssPend_disc.A-ssPend_disc.b*keig)


%% Closed-loop controller (state regulator with 'LQR')
disp('Designing linear state feedback controller (LQR)')
% Desired cost function matrices
Q = zeros(4,4);
Q(1,1) = 1000; %1;
Q(2,2) = 0; 10000;
Q(3,3) = 1; %1;
Q(4,4) = 0; %0.000001;
R = 0.0001;
[klqr,Slqr,Elqr] = dlqr(ssPend_disc.A,ssPend_disc.b,Q,R);
Vlqr = 1/(c(:,1)' * inv(eye(4) - ssPend_disc.A+ssPend_disc.b*klqr) * ssPend_disc.b + d(1,:));

disp('Eigenvalues of controlled system (LQR):')
eig(ssPend_disc.A-ssPend_disc.b*klqr)
