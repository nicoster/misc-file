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
set zip=d:\Progra~1\7-Zip\7z.exe

if "%destdir%" == "" set destdir=%cd%
set tempdir=%temp%
set workdir=%cd%

echo ca>%temp%\ftpcmd
echo ca$ftp>>%temp%\ftpcmd
echo bin>>%temp%\ftpcmd
echo lcd %tempdir%>>%temp%\ftpcmd
echo cd autoftp>>%temp%\ftpcmd
echo mget map*%buildnum%*.zip>>%temp%\ftpcmd
echo y>>%temp%\ftpcmd
echo bye>>%temp%\ftpcmd

cd /d %tempdir%
del map*%buildnum%* /q
ftp -s:%temp%\ftpcmd ftp.hz.webex.com
if errorlevel 1 goto thend;
del *.pdb
for /F "usebackq" %%i in (`dir /b map*%buildnum%*`) do set filename=%%i
%zip% e -y -ir!*.pdb %filename%
if errorlevel 1 (
	echo.
	echo %filename%.zip is corrupted or not complete.
	goto thend;
)

symstore add /f *.pdb /s \\10.224.115.227\symbols /t "Connect" /v "build%buildnum%" /o | findstr /C:"Failed to copy" /C:"SYMSTORE:"

:thend
if errorlevel 0 (echo &&balloon "PDB for %buildnum% is ready. " "Get PDB" 3)
cd %workdir%
echo.
pause
