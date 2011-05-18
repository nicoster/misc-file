	TITLE	asmfoo.cpp
	.386P
include listing.inc
if @Version gt 510
.model FLAT
else
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS
;	COMDAT ?dummy@foo@@QAEXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
FLAT	GROUP _DATA, CONST, _BSS
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif
PUBLIC	?dummy@foo@@QAEXH@Z				; foo::dummy
PUBLIC	_main
_TEXT	SEGMENT
_f$ = -4
_main	PROC NEAR

; 13   : void main(){foo f; f.dummy(5);}

	push	ebp
	mov	ebp, esp
	push	ecx
	push	5
	lea	ecx, DWORD PTR _f$[ebp]
	call	?dummy@foo@@QAEXH@Z			; foo::dummy
	mov	esp, ebp
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
;	COMDAT ?dummy@foo@@QAEXH@Z
_TEXT	SEGMENT
_this$ = -4
?dummy@foo@@QAEXH@Z PROC NEAR				; foo::dummy, COMDAT

; 11   : 	void dummy(int){};

	push	ebp
	mov	ebp, esp
	push	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	esp, ebp
	pop	ebp
	ret	4
?dummy@foo@@QAEXH@Z ENDP				; foo::dummy
_TEXT	ENDS
END
