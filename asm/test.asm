macro align value { rb (value-1)-($+value-1) mod value }
rb 5
macro strtbl name,[string]
{
  common
  label name dword
  forward
  local label2
  dd label2
  forward
  label2 db string,0
}
strtbl strings, "1234", "qwert", "asdfg", "zxcv"
dd strings


macro mov op1,op2
{
  if op1 in <cs, ds, es, fs>  & op2 in	  <cs, ds, es, fs>
    push op2
    pop op1
  else
    mov op1,op2
  end if
}

mov eax, 0

display 'abasdf'
value = 8
db 17 dup(?)
db (value-1)-($+value-1) mod value
align 8
db $
;rb 100
db $
mov eax, 0
dd 0xffffffff

