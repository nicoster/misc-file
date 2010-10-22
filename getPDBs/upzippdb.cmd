@echo off
echo UnzipPDB v1.00 - Unzip PDB files and add them to symstore
echo Copyright (C) 2009 Nick Xiao (nickx@sz.webex.com)
echo Webex - www.webex.com
echo.
set buildnum=%1
if "%filename%" == "" (
echo Usage:  %0 xxxx.zip
echo.
echo         xxxx - zip file name
echo.
set /p filename=So, which build of pdb files do you want? [xxxx.zip]: 
)
if "%filename%" == "" (echo Canceled)&&pause&&exit
set zip=d:\Progra~1\7-Zip\7z.exe

if "%destdir%" == "" set destdir=%cd%
set tempdir=%temp%
set workdir=%cd%

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
