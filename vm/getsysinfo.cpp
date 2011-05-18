#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "advapi32.lib")
TCHAR* envVarStrings[] =
{
  "OS         = %OS%",
  "PATH       = %PATH%",
  "HOMEPATH   = %HOMEPATH%",
  "TEMP       = %TEMP%"
};
#define  ENV_VAR_STRING_COUNT  (sizeof(envVarStrings)/sizeof(TCHAR*))
#define INFO_BUFFER_SIZE 32767
void printError( TCHAR* msg );

void main( )
{
  DWORD i;
  TCHAR  infoBuf[INFO_BUFFER_SIZE];
  DWORD  bufCharCount = INFO_BUFFER_SIZE;
 
  // Get and display the name of the computer. 
  bufCharCount = INFO_BUFFER_SIZE;
  if( !GetComputerName( infoBuf, &bufCharCount ) )
    printError( "GetComputerName" ); 
  printf( "\nComputer name:      %s", infoBuf ); 
 
  // Get and display the user name. 
  bufCharCount = INFO_BUFFER_SIZE;
  if( !GetUserName( infoBuf, &bufCharCount ) )
    printError( "GetUserName" ); 
  printf( "\nUser name:          %s", infoBuf ); 
 
  // Get and display the system directory. 
  if( !GetSystemDirectory( infoBuf, INFO_BUFFER_SIZE ) )
    printError( "GetSystemDirectory" ); 
  printf( "\nSystem Directory:   %s", infoBuf ); 
 
  // Get and display the Windows directory. 
  if( !GetWindowsDirectory( infoBuf, INFO_BUFFER_SIZE ) )
    printError( "GetWindowsDirectory" ); 
  printf( "\nWindows Directory:  %s", infoBuf ); 
 
  // Expand and display a few environment variables. 
  printf( "\n\nSmall selection of Environment Variables:" ); 
  for( i = 0; i < ENV_VAR_STRING_COUNT; ++i )
  {
    bufCharCount = ExpandEnvironmentStrings(envVarStrings[i], infoBuf,
        INFO_BUFFER_SIZE ); 
    if( bufCharCount > INFO_BUFFER_SIZE )
      printf( "\n\t(Buffer too small to expand: \"%s\")", 
              envVarStrings[i] );
    else if( !bufCharCount )
      printError( "ExpandEnvironmentStrings" );
    else
      printf( "\n   %s", infoBuf );
  }
}

void printError( TCHAR* msg )
{
  DWORD eNum;
  TCHAR sysMsg[256];
  TCHAR* p;

  eNum = GetLastError( );
  FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | 
         FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, eNum,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
         sysMsg, 256, NULL );

  // Trim the end of the line and terminate it with a null
  p = sysMsg;
  while( ( *p > 31 ) || ( *p == 9 ) )
    ++p;
  do { *p-- = 0; } while( ( p >= sysMsg ) &&
                          ( ( *p == '.' ) || ( *p < 33 ) ) );

  // Display the message
  printf( "\n\t%s failed with error %d (%s)", msg, eNum, sysMsg );
}