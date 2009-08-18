macro message arg
{
  if arg eqtype ""
    local str
    jmp @f
    str db arg,0Dh,0Ah,24h
    @@:
    mov dx,str
  else
    mov dx,arg
  end if
  mov ah,9
  int 21h
}

message "aaaa"