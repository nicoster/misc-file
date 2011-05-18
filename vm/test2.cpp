#include "common.h"

typedef wstring CTString;
#define GetLength length
#define Find find

BOOL IsNewXMLAPIVersion(CTString strCurVersion,CTString strVersion)
{
 // XML API version format is "WebEx XML API Vx.x.x"
 if ((strCurVersion.GetLength() < 1) || (strVersion.GetLength() < 1 ))
  return FALSE;
 
 INT nPos = strCurVersion.Find(L'V');
 if (nPos == -1)
  return FALSE;
 
 CTString strSubVer;
 strSubVer = strCurVersion.substr(nPos + 1);//strCurVersion.GetLength() - (nPos+1));
 //strSubVer.TrimLeft();
// strSubVer.TrimRight();
 if (strSubVer.GetLength() < 1)
  return FALSE;
 
 // Compare the first version bit
 INT nSubPos = strSubVer.Find('.');
 INT nSubPos2 = strVersion.Find('.');
 if ((nSubPos == -1) || (nSubPos2 == -1))
  return FALSE;
 
 //CTString strFirst = strSubVer.substr(0, nSubPos);
 INT nFirst = //_wtoi(strFirst);
  _wtoi(strSubVer.substr(0, strSubVer.GetLength() - nSubPos -1));
 CTString strFirst2 = strVersion.substr();
 INT nFirst2 = _wtoi(strVersion.Left(strVersion.GetLength() - nSubPos2 -1));
 
 CTString strSubRight = strSubVer.Right(strSubVer.GetLength() - nSubPos -1);
 CTString strSubRight2 = strVersion.Right(strVersion.GetLength() - nSubPos2 -1);
 strSubRight.TrimLeft();
 strSubRight.TrimRight();
 strSubRight2.TrimLeft();
 strSubRight2.TrimRight();
 
 if (nFirst > nFirst2)
  return TRUE;
 else
 {
  if (nFirst == nFirst2)
  {
   // Compare the second version bit
   nSubPos = strSubRight.Find('.');
   nSubPos2 = strSubRight2.Find('.');
   if ((nSubPos == -1) || (nSubPos2 == -1))
    return FALSE;
 
   INT nSecond = _wtoi(strSubRight.Left(strSubRight.GetLength() - nSubPos -1));
   INT nSecond2 = _wtoi(strSubRight2.Left(strSubRight2.GetLength() - nSubPos2 -1));
 
   if (nSecond > nSecond2)
    return TRUE;
   else
   {
    if (nSecond == nSecond2)
    {
     //Compare the third version bit
     INT nThird = _wtoi(strSubRight.Right(strSubRight.GetLength() - nSubPos -1));
     INT nThird2 = _wtoi(strSubRight2.Right(strSubRight2.GetLength() - nSubPos2 -1));
     if(nThird >= nThird2)
      return TRUE;
    }
   }
  }
 }
 
 return FALSE;
}

void main()
{
}