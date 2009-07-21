@echo off
set dst=%ProgramFiles%\makedump
set reg=%cd%\unmkdmp.reg

taskkill /im taskmgrex.exe
ping  -n 2 127.0.0.1 >nul
del /q "%dst%"
rd "%dst%"

: modify reg
echo Windows Registry Editor Version 5.00>%reg%
echo.>>%reg%
echo [-HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskmgr.exe]>>%reg%
echo.>>%reg%
regedit /s %reg%

pause