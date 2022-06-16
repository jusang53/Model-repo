SHELL := cmd.exe
CYGWIN=nontsec
export PATH := C:\Program Files\Eclipse Adoptium\jdk-11.0.14.101-hotspot\bin;C:\Program Files\IBM\ILOG\CPLEX_Studio_Community201\opl\bin\x64_win64;C:\Program Files\IBM\ILOG\CPLEX_Studio_Community201\opl\oplide\;C:\Program Files\IBM\ILOG\CPLEX_Studio_Community201\cplex\bin\x64_win64;C:\Program Files\IBM\ILOG\CPLEX_Studio_Community201\cpoptimizer\bin\x64_win64;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files\dotnet\;C:\Program Files\MATLAB\R2022a\runtime\win64;C:\Program Files\MATLAB\R2022a\bin;C:\Program Files\MATLAB\R2021a\runtime\win64;C:\Program Files\MATLAB\R2021a\bin;C:\Program Files\MATLAB\R2020b\bin;C:\Program Files (x86)\Eclipse\Sumo\bin\;C:\Program Files (x86)\Eclipse\Sumo\tools\;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\170\Tools\Binn\;C:\Program Files\Git LFS;C:\Program Files\Git\cmd;C:\Users\PC\AppData\Local\Programs\Python\Python38;C:\Users\PC\AppData\Local\Programs\Python\Python38\Scripts;C:\Program Files\MATLAB\R2019b\runtime\win64;C:\Program Files\MATLAB\R2019b\bin;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Windows\System32;C:\Users\PC\AppData\Local\Programs\Python\Python38\Scripts\;C:\Users\PC\AppData\Local\Programs\Python\Python38\;C:\Users\PC\AppData\Local\Programs\Python\Python39\Scripts\;C:\Users\PC\AppData\Local\Programs\Python\Python39\;C:\Users\PC\AppData\Local\Microsoft\WindowsApps;C:\Users\PC\AppData\Local\Programs\Microsoft VS Code\bin;C:\Program Files (x86)\Common Files\Hilscher GmbH\TLRDecode;C:\Windows\System32;C:\Users\PC\AppData\Local\Programs\Python\Python38\Scripts\;C:\Users\PC\AppData\Local\Programs\Python\Python38\;C:\Users\PC\AppData\Local\Programs\Python\Python39\Scripts\;C:\Users\PC\AppData\Local\Programs\Python\Python39\;C:\Users\PC\AppData\Local\Microsoft\WindowsApps;C:\Users\PC\AppData\Local\Programs\Microsoft VS Code\bin;C:\Program Files (x86)\Common Files\Hilscher GmbH\TLRDecode
export AS_BUILD_MODE := BuildAndTransfer
export AS_VERSION := 4.5.2.102
export AS_COMPANY_NAME :=  
export AS_USER_NAME := PC
export AS_PATH := C:/BrAutomation/AS45
export AS_BIN_PATH := C:/BrAutomation/AS45/Bin-en
export AS_PROJECT_PATH := C:/Users/PC/Desktop/PIL_PLC/GIT/JS
export AS_PROJECT_NAME := JS
export AS_SYSTEM_PATH := C:/BrAutomation/AS/System
export AS_VC_PATH := C:/BrAutomation/AS45/AS/VC
export AS_TEMP_PATH := C:/Users/PC/Desktop/PIL_PLC/GIT/JS/Temp
export AS_CONFIGURATION := PLC
export AS_BINARIES_PATH := C:/Users/PC/Desktop/PIL_PLC/GIT/JS/Binaries
export AS_GNU_INST_PATH := C:/BrAutomation/AS45/AS/GnuInst/V4.1.2
export AS_GNU_BIN_PATH := $(AS_GNU_INST_PATH)/bin
export AS_GNU_INST_PATH_SUB_MAKE := C:/BrAutomation/AS45/AS/GnuInst/V4.1.2
export AS_GNU_BIN_PATH_SUB_MAKE := $(AS_GNU_INST_PATH_SUB_MAKE)/bin
export AS_INSTALL_PATH := C:/BrAutomation/AS45
export WIN32_AS_PATH := "C:\BrAutomation\AS45"
export WIN32_AS_BIN_PATH := "C:\BrAutomation\AS45\Bin-en"
export WIN32_AS_PROJECT_PATH := "C:\Users\PC\Desktop\PIL_PLC\GIT\JS"
export WIN32_AS_SYSTEM_PATH := "C:\BrAutomation\AS\System"
export WIN32_AS_VC_PATH := "C:\BrAutomation\AS45\AS\VC"
export WIN32_AS_TEMP_PATH := "C:\Users\PC\Desktop\PIL_PLC\GIT\JS\Temp"
export WIN32_AS_BINARIES_PATH := "C:\Users\PC\Desktop\PIL_PLC\GIT\JS\Binaries"
export WIN32_AS_GNU_INST_PATH := "C:\BrAutomation\AS45\AS\GnuInst\V4.1.2"
export WIN32_AS_GNU_BIN_PATH := "$(WIN32_AS_GNU_INST_PATH)\\bin" 
export WIN32_AS_INSTALL_PATH := "C:\BrAutomation\AS45"

.suffixes:

ProjectMakeFile:

	@'$(AS_BIN_PATH)/BR.AS.AnalyseProject.exe' '$(AS_PROJECT_PATH)/JS.apj' -t '$(AS_TEMP_PATH)' -c '$(AS_CONFIGURATION)' -o '$(AS_BINARIES_PATH)'   -sfas -buildMode 'BuildAndTransfer'   

