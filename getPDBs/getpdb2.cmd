@echo off
echo GetPDB v1.00 - Get PDB files from autoftp in sz.webex.com
echo Copyright (C) 2007 Nick Xiao (nickx@sz.webex.com)
echo Webex - www.webex.com
echo.
set buildnum=%1
if "%buildnum%" == "" (
echo Usage:  %0 xxxx
echo.
echo         xxxx - build number
echo.
set /p buildnum=So, which build of pdb files do you want? [xxxx]: 
)
if "%buildnum%" == "" (echo Canceled)&&pause&&exit

:map-T25SP41_TRICON_BE3-3352.zip
set filename=map-T25SP41_TRICON_BE-%buildnum%
set zip=d:\Progra~1\7-Zip\7z.exe

if "%destdir%" == "" set destdir=%cd%
set tempdir=%temp%
set workdir=%cd%

echo webex_us>%temp%\ftpcmd
echo awk159>>%temp%\ftpcmd
echo bin>>%temp%\ftpcmd
echo lcd %tempdir%>>%temp%\ftpcmd
echo get home/webex_us/client/us/%filename%.zip>>%temp%\ftpcmd
echo bye>>%temp%\ftpcmd

ftp -s:%temp%\ftpcmd 172.16.250.36
if errorlevel 1 goto thend;
cd /d %tempdir%
del *.pdb
%zip% e -y -ir!*.pdb %filename%.zip
if errorlevel 1 (
	echo.
	echo %filename%.zip is corrupted or not complete.
	goto thend;
)

:symstore add /f *.pdb /s \\172.16.252.234\symbols /t "Connect" /v "build%buildnum%"

:thend
cd %workdir%
echo.
pause
