;-----------------------------------------
; Format Pe File  By:XFish
;------------------------------------------
 Code_Base   = 1000h
 File_Algin  = 200h
 Rva_Del     = Code_Base - @Code
 Image_Base  = 00400000h
;________________________________________________________________
DOS_HEADER:
.e_magic		db	'MZ'
.e_cblp 		dw	0
.e_cp			dw	0
.e_crlc 		dw	0
.e_cparhdr		dw	0
.e_minalloc		dw	0
.e_maxalloc		dw	0
.e_ss			dw	0
.e_sp			dw	0
.e_csum 		dw	0
.e_ip			dw	0
.e_cs			dw	0
.e_lfarlc		dw	0
.e_ovno 		dw	0
.e_res			dw   4 dup(0)
.e_oemid		dw	0
.e_oeminfo		dw	0
.e_res2 		dw  10 dup(0)
.e_lfanew		dd  NT_HEADERS



Dos_Stub:
	mov ah, 4ch
	int 21h
	
	

NT_HEADERS:
.Signature		dd	'PE'
;++                                     ;IMAGE_FILE_HEADER
.Machine		dw	14ch	 ;.Inten I386
.NumberOfSections	dw	1
.TimeDateStamp		dd	0
.PointerToSymbolTable	dd	0
.NumberOfSymbols	dd	0	
.SizeOfOptionalHeader	dw	0E0h
.Characteristics	dw	010fh	 ;.exe Signature
;--
;++                                     ;IMAGE_OPTIONAL_HEADER32
.Magic			dw	10Bh	 ;.exe file
.MajorLinkerVersion	db	0
.MinorLinkerVersion	db	0
.SizeOfCode		dd	File_Algin
.SizeOfInitializedData	dd	0
.SizeOfUninitializedData dd	0
.AddressOfEntryPoint	dd	@Code + Rva_Del ;oep
.BaseOfCode		dd	Code_Base	;Code Section Rva
.BaseOfData		dd	0		;Data Section Rva
.ImageBase		dd	Image_Base
.SectionAlignment	dd	Code_Base	;Section Mem Align
.FileAlignment		dd	File_Algin	;Section Disk Align
.MajorOperSystemVersion dw	0		;system version 主
.MinorOperSystemVersion dw	0		;system version 次
.MajorImageVersion	dw	0		;user version   主
.MinorImageVersion	dw	0		;user version   次
.MajorSubsystemVersion	dw	4
.MinorSubsystemVersion	dw	0
.Win32VersionValue	dd	0		;Reserved 0
.SizeOfImage		dd	2000h
.SizeOfHeaders		dd	File_Algin	;DosHeader + DosStub + NtHeader + Section Header
.CheckSum		dd	0
.SubSystem		dw	2		;Gui
.DllCharacteristics	dw	0
.SizeOfStackReserve	dd	10000h		
.SizeOfStackCommit	dd	1000h		;Stack = 4kb
.SizeOfHeapReserve	dd	10000h
.SizeOfHeapCommit	dd	1000h		;Heap = 4kb
.LoaderFlags		dd	0
.NumberOfRvaAndSizes	dd	10h		;16
.Export 		rd	2
.Import 		rd	2
.Misc_Section		rd	28
	

_SECTION_HEADER:
.Name1			db	'.code', 0, 0, 0
.VirtualSize		dd	1000h
.VirtualAddress 	dd	Code_Base
.SizeOfRawData		dd	@Code_End - @Code
.PointerToRawData	dd	@Code
.PointerToRelocations	dd	0
.PointerToLinenumbers	dd	0
.NumberOfRelocations	dw	0
.NumberOfLinenumbers	dw	0
.Characteristics	dd	0E0000020h

align	200h
;------------------------------------

@Code:

	ret
	

@Code_End:


		


