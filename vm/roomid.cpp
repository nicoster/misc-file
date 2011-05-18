#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
using namespace std;

BOOL DecodeRoomID(string const & strRoomID, string & strTabID, string & strWidgetID, string & strObjectID, string& strPluginID)
{
	string::size_type nStart = 0, nTemp = 0;
	nTemp = strRoomID.find_first_of(_T('|'), nStart);
	if (nTemp == -1) return FALSE;
	strTabID = strRoomID.substr(nStart, nTemp - nStart);
	nStart = nTemp + 1;
	nTemp = strRoomID.find_first_of(_T('|'), nStart); 
	if (nTemp == -1) return FALSE;
	strWidgetID = strRoomID.substr(nStart, nTemp - nStart);
	nStart = nTemp + 1;
	nTemp = strRoomID.find_first_of(_T('|'), nStart); 
	if (nTemp == -1) return FALSE;
	strObjectID = strRoomID.substr(nStart, nTemp - nStart);
	nStart = nTemp + 1;
	strPluginID = strRoomID.substr(nStart, strRoomID.length() - nStart);
	return TRUE;
}

void main()
{
	//_asm int 3;
	string strTabID, strWidgetID, strObjectID, strPluginID;
	DecodeRoomID("abcd|1234|xyzqwerty", strTabID, strWidgetID, strObjectID, strPluginID);
	cout<< strTabID << "\n" << strWidgetID << "\n" << strObjectID << "\n" << strPluginID;
}