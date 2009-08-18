

	format PE GUI 4.0
	include 'win32ax.inc'
	entry	__Entry

macro @pushsz argc{
  
  local .string
  forward
  if ~ argc eq
    if argc eqtype ''
      call     .string	 
	db	 argc, 0
.string:
      else 
	 push  argc
     
      end if
   end if
}

struct IMAGE_EXPORT_DIRECTORY
  Characteristics	    dd	    ?  ;δʹ��
  TimeDateStamp 	    dd	    ?  ;�ļ�����ʱ��
  MajorVersion		    dw	    ?  ;���汾�ţ�һ��Ϊ0
  MinorVersion		    dw	    ?  ;�ΰ汾�ţ�һ��Ϊ0
  nName 		    dd	    ?  ;ģ�����ʵ����
  nBase 		    dd	    ?  ;����, �����������Ǻ�����ַ���������ֵ
  NumberOfFunctions	    dd	    ?  ;AddressOfFunctions���е�Ԫ�ظ���
  NumberOfNames 	    dd	    ?  ;AddressOfNames���е�Ԫ�ظ���
  AddressOfFunctions	    dd	    ?  ;ָ������ַ����
  AddressOfNames	    dd	    ?  ;�������ֵ�ָ���ַ
  AddressOfNameOrdinals     dd	    ?  ;ָ��������к�����
ends

.code

		
 __Entry:
	call	GetKrnlBase3
	
	@pushsz 'WinExec'
	push	eax
	call	GetApi
	
	push	SW_SHOW
	@pushsz "notepad.exe"
	call	eax
	ret
 
 

 ;++
 ;
 ; int
 ;  GetApi(
 ;   IN HINSTANCE hModule, 
 ;   IN char *    lpApiString,     
 ;   )
 ;
 ; Routine Description:
 ;
 ;    ��ȡָ���������ڴ��ַ
 ;
 ; Arguments:
 ;
 ;    (esp)          - return address
 ;
 ;    Data   (esp+4) - hDllHandle
 ;           (esp+8) - nReason
 ; Return Value:
 ;
 ;    eax -> Function Mem Address��
 ;
 ;--

 GetApi:
	pop	edx
	pop	eax			;hModule
	pop	ecx			;lpApiString
	push	edx	
	pushad
	mov	ebx, eax		;hModule        ebx
	mov	edi, ecx		;lpApiString    edi     
	xor	al, al
  .Scasb:
	scasb
	jnz	.Scasb
	dec	edi
	sub	edi, ecx
	xchg	edi, ecx		; edi = lpApiString, ecx = ApiLen
	
	mov	eax, [ebx+3ch]	
	mov	esi, [ebx+eax+78h]	;Get Export Rva
	lea	esi, [esi+ebx+IMAGE_EXPORT_DIRECTORY.NumberOfNames]
	lodsd
	xchg	eax, edx		; edx = NumberOfNames
	lodsd
	push	eax			; [esp] = AddressOfFunctions
	lodsd
	xchg	eax, ebp
	lodsd
	xchg	eax, ebp		; ebp = AddressOfNameOrdinals, eax = AddressOfNames
	add	eax, ebx
	
	mov	[esp+4*6], edi		;��ʱ�洢
	mov	[esp+4*5], ecx		;��ʱ�洢

  .LoopScas:	
	dec	edx
	jz	.Ret
	mov	esi, [eax+edx*4]
	add	esi, ebx
	repz	cmpsb
	jz	.GetAddr
	mov	edi, [esp+4*6]		
	mov	ecx, [esp+4*5]		
	jmp	.LoopScas
	
  .GetAddr:
	shl	edx, 1
	add	ebp, edx
	movzx	eax, word [ebp+ebx]
	shl	eax, 2
	add	eax, [esp]
	mov	eax, [ebx+eax]
	add	eax, ebx
  .Ret:
	pop	ecx
	mov	[esp+4*7], eax
	popad
	ret





 ;++
 ;
 ; BOOL
 ;   IsPe(
 ;      HMODULE pMemory
 ;   )
 ;
 ; Routine Description:
 ;
 ;    �����ļ��Ƿ���PE�ļ���ʽ��
 ;
 ; Arguments:
 ;
 ;    (esp)          - return address
 ;
 ;    Data   (esp+4) - Is Pe of pMemory
 ;
 ;
 ; Return Value:
 ;
 ;    eax = TRUE, succeeds; eax = FALSE, fails��
 ;
 ;--
 
 IsPe:
	pop	eax	; (eax) = return address
	pop	edx
	push	eax	; (eax) = return address
	
	cmp	word [edx], 'MZ'
	jnz	.RetFails
	mov	eax, [edx+3ch]
	cmp	word [eax+edx],'PE'
	jnz	 .RetFails
	xor	eax, eax
	inc	eax
	ret
	
  .RetFails:
	xor	eax, eax
	ret
 ;--
 
 ;++
 ;
 ; int
 ;   GetKrnlBase(
 ;      int KrnlApiAddress
 ;   )
 ;
 ; Routine Description:
 ;
 ;    ���kernel32����ַ
 ;
 ; Arguments:
 ;
 ;    (esp)          - return address
 ;
 ;    Data   (esp+4) - KrnlApiAddress, ptr ApiAddress
 ;
 ;
 ; Return Value:
 ;
 ;    eax =  krnl32 base
 ;
 ;--

 GetKrnlBase:
	pop	eax
	pop	edx
	push	eax
	
 .Next:
	cmp	word [edx], 'MZ' 
	jz	.IsPe
	dec	edx
	xor	dx, dx
	jmp	.Next
 
 .IsPe: 
	mov	eax, [edx+3ch]
	cmp	word [eax+edx], 'PE'
	jnz	.Next
	xchg	eax, edx
	ret
	
 ;++
 ;
 ; int
 ;   GetKrnlBase2(
 ;    void
 ;   )
 ;
 ; Routine Description:
 ;
 ;    ���kernel32����ַ
 ;
 ; Arguments:
 ;
 ;    (esp)          - return address
 ;
 ;
 ; Return Value:
 ;
 ;    eax =  krnl32 base
 ;
 ;--
 
 GetKrnlBase2:
	xor	edx, edx
	mov	eax, [fs:edx]
  .Next:
	mov	edx, [eax]
	inc	edx
	jz	.Krnl
	mov	eax, [eax]
	jmp	.Next
  .Krnl:
	mov	edx, [eax+4]
  .Loop:
	dec	edx
	xor	dx, dx
	cmp	word [edx], 'MZ' 
	jz	.IsPe
	jmp	.Loop
	
  .IsPe:	
	mov	eax, [edx+3ch]
	cmp	word [eax+edx], 'PE'
	jnz	.Loop
	xchg	eax, edx
	ret
	
 ;++
 ;
 ; int
 ;   GetKrnlBase3(
 ;    void
 ;   )
 ;
 ; Routine Description:
 ;
 ;    ���kernel32����ַ
 ;
 ; Arguments:
 ;
 ;    (esp)          - return address
 ;
 ;
 ; Return Value:
 ;
 ;    eax =  krnl32 base
 ;
 ;--
 
 GetKrnlBase3:
	mov	eax, [fs:30h]
	mov	eax, [eax+0ch]
	mov	eax, [eax+1ch]
	mov	eax, [eax]
	mov	eax, [eax+8h]
	ret	
	
	
