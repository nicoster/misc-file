#pragma once
#include <BugslayerUtil.h>
#pragma comment(lib, "bugslayerutil.lib")

class CUnhandledExceptionFilter
{
public:
	CUnhandledExceptionFilter()
	{
		SetCrashHandlerFilter(_UnhandledExceptionFilter);
	}

private:
	static LONG __stdcall _UnhandledExceptionFilter(PEXCEPTION_POINTERS pExPtrs)
	{
		CString csExceptLogs, csTemp;
//		CTimeSpan span(CTime::GetCurrentTime() - theApp.m_tmStart); 
//		csExceptLogs.Format(_T("%s RnmsAdaptor access violation and exit. Runned for %d:%d:%d\r\n"), 
//			CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"), 
//			span.GetHours(), span.GetMinutes(), span.GetSeconds());
		
		csExceptLogs = csExceptLogs + GetFaultReason ( pExPtrs ) + _T("\r\n") ;
		
		csExceptLogs = csExceptLogs + GetRegisterString ( pExPtrs ) + _T("\r\n") ;
		
		const char * szBuff = GetFirstStackTraceString ( GSTSO_PARAMS | GSTSO_MODULE | GSTSO_SYMBOL | GSTSO_SRCLINE, pExPtrs  ) ;
		do
		{
			csExceptLogs = csExceptLogs + szBuff + _T("\r\n");
			szBuff = GetNextStackTraceString ( GSTSO_PARAMS | GSTSO_MODULE | GSTSO_SYMBOL | GSTSO_SRCLINE , pExPtrs ) ;
		}
		while ( NULL != szBuff ) ;
		
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		
		CString csPath(szPath);
		CString const & csFile = csPath.Left(csPath.ReverseFind(_T('.'))) + _T(".log"); 
		
		CStdioFile f;
		if (! f.Open(csFile, CFile::modeCreate | CFile::modeNoTruncate |
			CFile::modeWrite | CFile::shareDenyWrite))
		{
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else
		{
			/* D.H 2003-12-24 write exception log info */
			f.SeekToEnd();
			f.WriteString(csExceptLogs);
			
			/* log finished */
			f.Close();
		}
		
//		ShellExecute(NULL, "open", szPath, NULL, NULL, NULL);
		
		return EXCEPTION_EXECUTE_HANDLER;
	}
};
