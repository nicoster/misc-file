set rar=d:\progra~1\winrar\rar.exe
set dist=dist\

md %dist%
copy img.png %dist% /y
copy install.cmd %dist% /y
copy readme.htm %dist% /y
copy setdll.exe %dist% /y
copy uninstall.cmd %dist%  /y
copy makedmp.dll %dist%  /y
copy makedump.exe %dist%  /y

cd %dist%
del *.rar
%rar% a -ag"YYYY-MM-DD HH.MM'" -r -o- -xdebug\ -xdebug\ -idp -m5 -ed -isnd -x*.rar "makedump .rar" 

pause