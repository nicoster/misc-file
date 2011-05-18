#include "common.h"
#include "GdiPlus.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

void main()
{
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput m_gdiplusStartupInput; 
	GdiplusStartup(&gdiplusToken, &m_gdiplusStartupInput, NULL);      

	BITMAP bmp("d:\\a.bmp");

	CLSID pngClsid;
	GetEncoderClsid("image/jpeg", &pngClsid);
	
	bmp.Save("d:\\a.jpg", &pngClsid, NULL);
	GdiplusShutdown(gdiplusToken);
	
}