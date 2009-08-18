
format PE GUI 4.0
entry start

include 'win32ax.inc'

.code

  start:

	invoke	MyMessageBox
	invoke	ExitProcess,0


;.end start
section '.idata' import data readable writeable

  library kernel,'KERNEL32.DLL',\
	   msg,'MSG2.DLL'

  import kernel,\
	 ExitProcess,'ExitProcess'

  import msg,\
	 MyMessageBox,'MyMessageBox'

