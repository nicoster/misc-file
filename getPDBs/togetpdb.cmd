set zip=V:\Progra~1\7-Zip\7z.exe

if "%destdir%" == "" set destdir=%cd%
set tempdir=%temp%
set workdir=%cd%

echo webex_us>%temp%\ftpcmd
echo awk159>>%temp%\ftpcmd
echo bin>>%temp%\ftpcmd
echo lcd %tempdir%>>%temp%\ftpcmd
echo cd home/webex_us/client/us/>>%temp%\ftpcmd
:type %temp%\ftpcmd
ftp -s:%temp%\ftpcmd 10.224.114.246
