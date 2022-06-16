<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio Version=4.5.2.102?><SwConfiguration xmlns="http://br-automation.co.at/AS/SwConfiguration" CpuAddress="SL1">
   <TaskClass Name="Cyclic#1">
      <Task AdditionalIncludeDirectories="\Logical\MATLAB_includes\R2019b\"
            BuildOptions="-lm -D MODEL=pend_mod_nlin -D NUMST=2 -D NCSTATES=4 -D HAVESTDIO -D MODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -D CLASSIC_INTERFACE=0 -D ALLOCATIONFCN=0 -D TID01EQ=1 -D TERMFCN=1 -D ONESTEPFCN=0 -D MAT_FILE=0 -D MULTI_INSTANCE_CODE=0 -D INTEGER_CODE=0 -D MT=0 "
            Debugging="false"
            Language="ANSIC"
            Memory="UserROM"
            Name="pend_mod"
            Source="Model.pend_mod.prg"/>
      <Task AdditionalIncludeDirectories="\Logical\MATLAB_includes\R2019b\"
            BuildOptions="-lm -D MODEL=pend_ctrl_lin -D NUMST=1 -D NCSTATES=0 -D HAVESTDIO -D MODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -D CLASSIC_INTERFACE=0 -D ALLOCATIONFCN=0 -D TID01EQ=0 -D TERMFCN=1 -D ONESTEPFCN=0 -D MAT_FILE=0 -D MULTI_INSTANCE_CODE=0 -D INTEGER_CODE=0 -D MT=0 "
            Debugging="false"
            Language="ANSIC"
            Memory="UserROM"
            Name="pend_ctrl"
            Source="Controller.pend_ctrl.prg"/>
   </TaskClass>
   <TaskClass Name="Cyclic#2"/>
   <TaskClass Name="Cyclic#3"/>
   <TaskClass Name="Cyclic#4"/>
   <Libraries>
      <LibraryObject Debugging="true" Language="binary" Memory="UserROM" Name="brsystem"
                     Source="Libraries.brsystem.lby"/>
      <LibraryObject Debugging="true" Language="binary" Memory="UserROM" Name="runtime"
                     Source="Libraries.runtime.lby"/>
      <LibraryObject Debugging="true" Language="binary" Memory="UserROM" Name="sys_lib"
                     Source="Libraries.sys_lib.lby"/>
      <LibraryObject AdditionalIncludeDirectories="\Logical\MATLAB_includes\R2019b\"
                     BuildOptions="-lm -D MODEL=pend_ctrl_fun -D NUMST=1 -D NCSTATES=0 -D HAVESTDIO -D MODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -D CLASSIC_INTERFACE=0 -D ALLOCATIONFCN=0 -D TID01EQ=0 -D TERMFCN=1 -D ONESTEPFCN=1 -D MAT_FILE=0 -D MULTI_INSTANCE_CODE=1 -D INTEGER_CODE=0 -D MT=0 "
                     Debugging="false"
                     Language="ANSIC"
                     Memory="UserROM"
                     Name="pctr_fun"
                     Source="Libraries.pctr_fun.lby"/>
   </Libraries>
</SwConfiguration>