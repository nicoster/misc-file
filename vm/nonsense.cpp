#include <tchar.h>
#include <string>
#include <iostream>
using namespace std;

void main()
{
	bool bHasSpaceFeature = true;
	string str("asdf" + bHasSpaceFeature);
	cout << str;
	
	//~ cout << _T("CTriMainView::OnClientPolicyChanged....") + bHasSpaceFeature ;
//~ _T("CTriMainView::OnClientPolicyChanged....") + bHasSpaceFeature ? _T("notify has space.") : _T("notify has NO space.");
}