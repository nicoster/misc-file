@echo off
title Desktop Heap Monitor v8.1
dheapmon.exe /l
:show
cls
dheapmon.exe  /v /w "WinSta0" -d "Default"
echo.
echo.
echo                      [Enter to refresh]
set /p dummy=
goto show