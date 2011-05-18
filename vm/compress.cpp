//#include <windows.h>
#include <afxcmn.h>
#include <zlib.h>
#pragma comment(lib, "zdll.lib")
void CompressFile(LPCTSTR strFilePath)
{
HANDLE   hFile,   hFileToWrite;   
    
  //��Ҫ����ѹ�����ļ�   
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
    
  //����һ���ļ�ӳ��   
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
    
  //����һ���ļ�ӳ�����ͼ������Ϊsource   
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
  //��Ϊѹ������������������������0.1%   +   12   Ȼ��һ��DWORD��������ѹ��ǰ�Ĵ�С��   
  //   ��ѹ����ʱ���ã���Ȼ�����Ա���������Ϣ�������ò���   
  dwFileLengthToWrite   =   (double)dwFileLength*1.001   +   12   +   sizeof(DWORD);   
    
  //�����Ǵ���һ���ļ�����������ѹ������ļ�   
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
    
  //�����ǽ�ѹ��ǰ�Ĵ�С�������ļ��ĵ�һ��DWORD����   
  LPVOID   pBuf   =   lpMapAddressToWrite;   
  (*(DWORD*)pBuf)   =   dwFileLength;   
  pBuf   =   (DWORD*)pBuf   +   1;   
    
    
  //////////////////////////////////////////////////////////////////////   
    
  //�����������Ҫ�ģ�zlib�����ṩ��һ����������Դ���������ѹ����Ŀ�Ļ���   
  //ԭ�����£�   
  //int   compress   (Bytef   *dest,   uLongf   *destLen,   const   Bytef   *source,   uLong   sourceLen);   
  //����destLen����ʵ��ѹ������ļ���С��   
  compress((Bytef*)pBuf,&dwFileLengthToWrite,   (Bytef*)lpMapAddress,   dwFileLength);   
    
  //////////////////////////////////////////////////////////////////////   
    
  UnmapViewOfFile(lpMapAddress);   
  CloseHandle(hMapFile);   
  CloseHandle(hFile);   
    
  UnmapViewOfFile(lpMapAddressToWrite);   
  CloseHandle(hMapFileToWrite);   
  //���ｫ�ļ���С��������һ��   
  SetFilePointer(hFileToWrite,dwFileLengthToWrite   +   sizeof(DWORD)   ,NULL,FILE_BEGIN);   
  SetEndOfFile(hFileToWrite);   
  CloseHandle(hFileToWrite);   
}

void main()
{
	CompressFile(_T("c:\\xml.xml"));
}