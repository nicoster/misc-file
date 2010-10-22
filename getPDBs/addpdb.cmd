@echo off
echo AddPDB v1.01 - Add PDB files into datastore
echo Copyright (C) 2007 Nick Xiao (nickx@sz.webex.com)
echo Webex - www.webex.com
echo.

echo %1
symstore add /f "%1" /s \\10.224.115.227\symbols /t "Connect" /v "build" /o

echo.

