//#include <windows.h>
#include <afxcmn.h>
#include <zlib.h>
#pragma comment(lib, "zdll.lib")
void CompressFile(LPCTSTR strFilePath)
{
HANDLE   hFile,   hFileToWrite;   
    
  //打开要进行压缩的文件   
  hFile   =   CreateFile(strFilePath,   //   file   name   
          GENERIC_READ,   //   open   for   reading   
          FILE_SHARE_READ,   //   share   for   reading   
          NULL,   //   no   security   
          OPEN_EXISTING,   //   existing   file   only   
          FILE_ATTRIBUTE_NORMAL,   //   normal   file   
          NULL);   //   no   attr.   template   
    
  if   (hFile   ==   INVALID_HANDLE_VALUE)   
  {   
          AfxMessageBox("Could   not   open   file   to   read");   //   process   error   
          return;   
  }   
    
  HANDLE   hMapFile,   hMapFileToWrite;   
    
  //创建一个文件映射   
  hMapFile   =   CreateFileMapping(hFile,   //   Current   file   handle.   
  NULL,   //   Default   security.   
  PAGE_READONLY,   //   Read/write   permission.   
  0,   //   Max.   object   size.   
  0,   //   Size   of   hFile.   
  "ZipTestMappingObjectForRead");   //   Name   of   mapping   object.   
    
  if   (hMapFile   ==   NULL)   
  {   
  AfxMessageBox("Could   not   create   file   mapping   object");   
  return;   
  }   
    
  LPVOID   lpMapAddress,   lpMapAddressToWrite;   
    
  //创建一个文件映射的视图用来作为source   
  lpMapAddress   =   MapViewOfFile(hMapFile,   //   Handle   to   mapping   object.   
  FILE_MAP_READ,   //   Read/write   permission   
  0,   //   Max.   object   size.   
  0,   //   Size   of   hFile.   
  0);   //   Map   entire   file.   
    
  if   (lpMapAddress   ==   NULL)   
  {   
  AfxMessageBox("Could   not   map   view   of   file");   
  return;   
  }   
    
  //////////////////////////////////////////////////////////////////////////////////   
  DWORD   dwFileLength,dwFileLengthToWrite;   
  dwFileLength   =   GetFileSize(hFile,   NULL);   
  //因为压缩函数的输出缓冲必须比输入大0.1%   +   12   然后一个DWORD用来保存压缩前的大小，   
  //   解压缩的时候用，当然还可以保存更多的信息，这里用不到   
  dwFileLengthToWrite   =   (double)dwFileLength*1.001   +   12   +   sizeof(DWORD);   
    
  //以下是创建一个文件，用来保存压缩后的文件   
  hFileToWrite   =   CreateFile("c:\\demoFile.gz",   //   create   demo.gz   
  GENERIC_WRITE|GENERIC_READ,   //   open   for   writing   
  0,   //   do   not   share   
  NULL,   //   no   security   
  CREATE_ALWAYS,   //   overwrite   existing   
  FILE_ATTRIBUTE_NORMAL   ,   //   normal   file   
  NULL);   //   no   attr.   template   
    
  if   (hFileToWrite   ==   INVALID_HANDLE_VALUE)   
  {   
  AfxMessageBox("Could   not   open   file   to   write");   //   process   error   
  return;   
  }   
    
  hMapFileToWrite   =   CreateFileMapping(hFileToWrite,   //   Current   file   handle.   
  NULL,   //   Default   security.   
  PAGE_READWRITE,   //   Read/write   permission.   
  0,   //   Max.   object   size.   
  dwFileLengthToWrite,   //   Size   of   hFile.   
  "ZipTestMappingObjectForWrite");   //   Name   of   mapping   object.   
    
  if   (hMapFileToWrite   ==   NULL)   
  {   
  AfxMessageBox("Could   not   create   file   mapping   object   for   write");   
  return;   
  }   
    
  lpMapAddressToWrite   =   MapViewOfFile(hMapFileToWrite,   //   Handle   to   mapping   object.   
  FILE_MAP_WRITE,   //   Read/write   permission   
  0,   //   Max.   object   size.   
  0,   //   Size   of   hFile.   
  0);   //   Map   entire   file.   
    
  if   (lpMapAddressToWrite   ==   NULL)   
  {   
  AfxMessageBox("Could   not   map   view   of   file");   
  return;   
  }   
    
  //这里是将压缩前的大小保存在文件的第一个DWORD里面   
  LPVOID   pBuf   =   lpMapAddressToWrite;   
  (*(DWORD*)pBuf)   =   dwFileLength;   
  pBuf   =   (DWORD*)pBuf   +   1;   
    
    
  //////////////////////////////////////////////////////////////////////   
    
  //这里就是最重要的，zlib里面提供的一个方法，将源缓存的数据压缩至目的缓存   
  //原形如下：   
  //int   compress   (Bytef   *dest,   uLongf   *destLen,   const   Bytef   *source,   uLong   sourceLen);   
  //参数destLen返回实际压缩后的文件大小。   
  compress((Bytef*)pBuf,&dwFileLengthToWrite,   (Bytef*)lpMapAddress,   dwFileLength);   
    
  //////////////////////////////////////////////////////////////////////   
    
  UnmapViewOfFile(lpMapAddress);   
  CloseHandle(hMapFile);   
  CloseHandle(hFile);   
    
  UnmapViewOfFile(lpMapAddressToWrite);   
  CloseHandle(hMapFileToWrite);   
  //这里将文件大小重新设置一下   
  SetFilePointer(hFileToWrite,dwFileLengthToWrite   +   sizeof(DWORD)   ,NULL,FILE_BEGIN);   
  SetEndOfFile(hFileToWrite);   
  CloseHandle(hFileToWrite);   
}

void main()
{
	CompressFile(_T("c:\\xml.xml"));
}