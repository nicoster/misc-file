
  format PE GUI 4.0
  include 'win32ax.inc'
   entry  __DllEntry

 __DllEntry:
  xor  eax, eax
  push	eax
push  eax
push eax
  push	eax
  call	[MessageBox]
   ret
