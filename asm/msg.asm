
  format PE GUI 4.0 DLL
  include 'win32ax.inc'
  entry  __DllEntry
  
section '.text' code readable executable

 ;++
 ;
 ; BOOL
 ;   DllMain(
 ;   IN HINSTANCE hDllHandle, 
 ;   IN DWORD     nReason,    
 ;   IN LPVOID    Reserved    
 ;   )
 ;
 ; Routine Description:
 ;
 ;    测试文件是否是PE文件格式。
 ;
 ; Arguments:
 ;
 ;    (esp)          - return address
 ;
 ;    Data   (esp+4) - hDllHandle
 ;       (esp+8) - nReason
 ;       (esp+12)- Reserved
 ;
 ; Return Value:
 ;
 ;    eax = TRUE, initialization succeeds; eax = FALSE, initialization fails。
 ;
 ;--

 __DllEntry:
   xor	eax, eax
   inc	eax	 
   ret	4*3



 __MyMessageBox:
  push ebp
  mov ebp, esp
  xor  eax, eax
;  ret
  push	eax
  push	eax
  push	eax
  push	eax
  call	[MessageBox]
  pop ebp
  ret
  
section '.idata' import data readable writeable
  library user,'USER32.DLL'

  import user,\
	 MessageBox,'MessageBoxA'

section  '.edata' export data	 readable

 __IMAGE_EXPORT_DIRECTORY:
   dd  0, 0, 0, rva szName, 0, 1, 1
   dd  rva Address_Tab
   dd	rva FuncName_Tab
   dd  rva Ordinals_Tab
   

  ;dll name
  szName  db 'Msg.dll', 0
  
  ;
  
  Address_Tab:
    dd rva __MyMessageBox   ;取__MyMessageBox过程 rva地址
  
  FuncName_Tab:
    dd rva ($+4)     ; ($ + 4) ptr "MyMessageBox"
    db 'MyMessageBox', 0
  
  Ordinals_Tab:
    dw 0
  
  



section '.reloc' fixups data readable discardable	; needed for Win32s