LegoWeDoCpp
=======

C++ support for LEGO WeDo USB Hub.

##What's good?
* You can use multi WeDo USB Hubs.
* You can use LEDs.

##Requirements
* Windows PC
* Visual Studio
* hid.dll, setupapi.dll
* WeDo USB Hub

DLLs must be in C:\Windows\system32.

If you don't have these, install wdksetup.exe from <http://msdn.microsoft.com/en-US/en-EN/windows/hardware/hh852365>
 
I confirmed these codes runs as win32 console application

##How to use it
Create new win32 console application project on Visual Studio and copy wedo.h, wedo_utils.h and hid.h to the project directory.

If the project names is 'WeDoSmaple', files must be like below.

    WeDoSample/
     |-WeDoSample.sln
     |- other files...
     |-WeDoSample/
       |-WeDoSample.h
       |-wedo.h
       |-wedo_utils.h
       |-hid.h
       |-WeDoSample.cpp
       |- other files and directories...

##Known Problems
* Sometimes fails to detect device, especially motors and LEDs

##I referred to
* [WeDoMore](https://github.com/itdaniher/WeDoMore)
* [Philo's LEGO_Power_Functions_RC.pdf](http://www.philohome.com/pf/LEGO_Power_Functions_RC_v120.pdf)
* <http://www.crimson-systems.com/tips/t085a.htm>

##About me
Please visit my blog.

<http://enthusiastickcoding.blogspot.jp/>
