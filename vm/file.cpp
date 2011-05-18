#include "afx.h"
#include "afxcmn.h"

void main()
{
	try
	{
		UINT nOpenFlag = CFile::modeCreate | CFile::modeWrite | CFile::typeText;
		nOpenFlag |= CFile::modeNoTruncate;
		CStdioFile file(_T("c:\\cs.txt"), nOpenFlag);

		file.SeekToEnd();
		if (file.GetPosition() == CFile::begin)
		{
			file.WriteString(_T(".LOG\n"));
		}
		file.WriteString(_T("aaaaaaaaaaaaaa\n"));
		file.Close();
	}
	catch (CFileException*e)
	{
		UNUSED_ALWAYS(e);
	}
}