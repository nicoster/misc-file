@echo off
set /p cont=This program is designed to run in Windows XP. Continue? [Y/N]

if "%cont%"=="N" goto thend
if "%cont%"=="n" goto thend

set dst=%ProgramFiles%\makedump
set cp=copy /y
set reg=%cd%\mkdmp.reg

taskkill /im taskmgr.exe
taskkill /im taskmgrex.exe
ping  -n 2 127.0.0.1 >nul

md "%dst%"
%cp% %windir%\system32\taskmgr.exe "%dst%\taskmgrex.exe"
%cp% makedump.exe "%dst%"
%cp% makedmp.dll "%dst%"

setdll /d:"%dst%\makedmp.dll" "%dst%\taskmgrex.exe"

: modify reg
echo Windows Registry Editor Version 5.00>%reg%
echo.>>%reg%
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskmgr.exe]>>%reg%
echo "debugger"="%dst:\=\\%\\taskmgrex.exe">>%reg%
echo.>>%reg%
regedit /s %reg%

start readme.htm
start taskmgr
:thend
pause
