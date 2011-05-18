#include <windows.h>

#include <TCHAR.h>

#define _NO_CVCONST_H // We should define the constant in order to ...

#include <dbghelp.h>

#include <stdio.h>

 

#pragma comment( lib, "dbghelp.lib" )

 

BOOL CALLBACK SymEnumSymbolsProc(PSYMBOL_INFO pSymInfo, ULONG SymbolSize, PVOID UserContext ) 

{

     if( pSymInfo != NULL ) 

     {

         // Show the symbol

         _tprintf(_T("TYPE INDEX:%d  "), pSymInfo->TypeIndex);

         _tprintf(_T("SIZE:%d  "), pSymInfo->Size);

         _tprintf(_T("VALUE: %d  "), pSymInfo->Value);

         _tprintf(_T("NAME: %s\n"), pSymInfo->Name);        

         _tprintf(_T("    SYMBOL ADDRESS:0x%X  "), pSymInfo->Address);

         _tprintf(_T("PDB CLASSIFICATION: %d\n"), pSymInfo->Tag);         

         

          

     }

     return TRUE; 

}

 

int _tmain( int argc, const TCHAR* argv[] ) 

{

     TCHAR pszExt[MAX_PATH];

   
     DWORD64 dw64Base     = 0; // if the image is a .pdb file, dw64Base cannot be zero.
	DWORD64 dw64ModAddress = 0;
                               // if the value is zero, the library obtains the load address

                               //  from the symbol file.

     DWORD   dwFileSize = 0; // if the image is a .pdb file, dwFileSize cannot be zero.

                                   // if the value is zero, the library obtains the size

                               //  from the symbol file.

     if(argc < 2)

     {

        goto FAILED_PARAM;

     }

 

     // Initilaize the symbol handle for the current process

     if(!SymInitialize( GetCurrentProcess(),  

                                    NULL,                 

                               FALSE ))   

     {

         _tprintf(_T("Failed when SymInitialize():%d\n"), GetLastError());

         return 0; 

     }

 

     if( argv[1] == NULL )

     {

         goto FAILED_PARAM;

     }

 

     //------------------------------------------------------------------------

     // Set initial parameters

   _tsplitpath( argv[1], NULL, NULL, NULL, pszExt );


     _tcslwr(pszExt);

     if(_tcsicmp(pszExt, _T(".pdb")) == 0)

     {

         // this is a .pdb file, and so we should set the load address and file size;

         dw64Base = 0x10000000;

         // get the file size

         HANDLE hFile = CreateFile( argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL ); 

         if( INVALID_HANDLE_VALUE == hFile )

         {

              _tprintf(_T("Failed when open %s: %d"), argv[1], GetLastError());

              goto FAILED_PARAM;

         }

         if( INVALID_FILE_SIZE == ( dwFileSize = GetFileSize(hFile, NULL)) )

         {

              _tprintf(_T("Failed when read the size of %s: %d"), argv[1], GetLastError());

              goto FAILED_PARAM;

         }

         CloseHandle(hFile); 

     }

 

     //------------------------------------------------------------------------

     // Load symbol table

     _tprintf(_T("Loading... %s\n"), argv[1]);

     dw64ModAddress = SymLoadModule64( GetCurrentProcess(),

                                                     NULL,               

                                                     (char*)argv[1],           

                                                     NULL,               

                                                     dw64Base,          

                                                     dwFileSize); 

 

     if( dw64ModAddress == 0 ) 

     {

         _tprintf(_T("Failed when SymLoadModule64(): %d \n"), GetLastError());

         return 0;

     }

     _tprintf(_T("Load Address: %I64x \n"), dw64ModAddress); 

 

     //------------------------------------------------------------------------

     // Show symbol information supported by the loaded file

     IMAGEHLP_MODULE64 ImageModule; 

 

     memset(&ImageModule, 0, sizeof(ImageModule) ); 

     ImageModule.SizeOfStruct = sizeof(ImageModule);

     if(!SymGetModuleInfo64( GetCurrentProcess(), 

                             dw64ModAddress, 

                                &ImageModule ))

     {

         _tprintf(_T("Failed when load image info:%d"), GetLastError());

         return 0;

     } 

 

     // Show informations included in the IMAGEHLP_MODULE64

     _tprintf(_T("CheckSum                : %d\n"), ImageModule.CheckSum);

     _tprintf(_T("Number of Loaded Symbols: %d\n"), ImageModule.NumSyms);

     switch(ImageModule.SymType)

     {

     case SymCoff:

         _tprintf(_T("Symbol Type: COFF symbols\n") );

         break;

     case SymCv:

         _tprintf(_T("Symbol Type: CodeView symbols\n") );

         break;

     case SymDeferred:

         _tprintf(_T("Symbol Type: Symbol loading deferred\n") );

         break;

     case SymDia:

         _tprintf(_T("Symbol Type: DIA symbols\n") );

         break;

     case SymExport:

         _tprintf(_T("Symbol Type: Symbols generated from a DLL export table\n") );

         break;

     case SymNone:

         _tprintf(_T("Symbol Type: No symbols are loaded\n") );

         break;

     case SymPdb:

         _tprintf(_T("Symbol Type: PDB symbols\n") );

         break;

     case SymSym:

         _tprintf(_T("Symbol Type: .sym file\n") );

         break;

     case SymVirtual:

         _tprintf(_T("Symbol Type: Virtual module created by SymLoadModuleEx with SLMFLAG_VIRTUAL\n") );

         break;

     }

     _tprintf(_T("Module Name      : %s\n"), ImageModule.ModuleName);

     _tprintf(_T("Image Name       : %s\n"), ImageModule.ImageName);

     _tprintf(_T("Loaded Image Name: %s\n"), ImageModule.LoadedImageName);

     _tprintf(_T("Loaded PDB Name  : %s\n"), ImageModule.LoadedPdbName);

     _tprintf(_T("CV Signature     : %d\n"), ImageModule.CVSig);

     _tprintf(_T("CV Data          : %s\n"), ImageModule.CVData);

     _tprintf(_T("PDB Signature    : %d\n"), ImageModule.PdbSig);

     if( ImageModule.PdbSig70 != GUID_NULL )

     {

         WCHAR wcsBuffer[MAX_PATH];

         if(0 == StringFromGUID2( ImageModule.PdbSig70,

                                      wcsBuffer,

                                      MAX_PATH))

         {

            _tprintf(_T("PDB Signature 7.0: Unknown GUID\n"));   

         }

         else

         {

              _tprintf(_T("PDB Signature 7.0: %S\n"), wcsBuffer); 

         }

     }

     else

     {

         _tprintf(_T("PDB Signature 7.0: GUID_NULL \n"));

     }

     _tprintf(_T("DBI Age of PDB   : %d\n"), ImageModule.PdbAge);

     _tprintf(_T("Loaded PDB is unmatched             : %s\n"), ImageModule.PdbUnmatched ? _T("Yes"):_T("No"));

     _tprintf(_T("Loaded DBG is unmatched             : %s\n"), ImageModule.DbgUnmatched ? _T("Yes"):_T("No"));

     _tprintf(_T("Line number information is available: %s\n"), ImageModule.LineNumbers ? _T("Yes"):_T("No"));

     _tprintf(_T("Symbol information is available     : %s\n"), ImageModule.GlobalSymbols ? _T("Yes"):_T("No"));

     _tprintf(_T("Type information is available       : %s\n"), ImageModule.TypeInfo ? _T("Yes"):_T("No"));

     

     //------------------------------------------------------------------------

     // Enumerate symbols in the module

     _tprintf(_T("Symbols List:\n"));

     if(!SymEnumSymbols( GetCurrentProcess(),

                            dw64ModAddress,

                            NULL, // Null point out that list all symbols

                            SymEnumSymbolsProc,

                            NULL))

     {

         _tprintf( _T("Failed when SymEnumSymbols(): %d \n"), GetLastError() ); 

     }

 

     //------------------------------------------------------------------------

     // Unload symbols table 

     if(!SymUnloadModule64( GetCurrentProcess(), dw64ModAddress ))        

     {

         _tprintf( _T("Failed when SymUnloadModule64() : %d \n"), GetLastError() ); 

     }

 

     if(!SymCleanup(GetCurrentProcess()))

     {

         _tprintf(_T("Failed when SymCleanup(): %d \n"), GetLastError());

         return 0; 

     }

 

 

     return 0; 

 

FAILED_PARAM:

     _tprintf(_T("Failed Parameter!\n"));

     _tprintf(_T("Usage: SymDump -filename\n"));

     _tprintf(_T("filename: a EXE, DLL or PDB file\n"));

     return 0;

}

