@echo off
echo wscript.sleep 10000>sleep.vbs 
title Desktop Heap Monitor v8.1
dheapmon.exe /l
:show
cls
for /f "usebackq tokens=3 delims=() " %%i in (`"dheapmon.exe  /v /w "WinSta0" -d "Default"|findstr Rate"`) do set dh=%%i&title  %%i%% Desktop Heap
echo %dh%
if %dh% geq '95' echo   
cscript sleep.vbs >nul 
goto show