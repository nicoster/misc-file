#include "common.h"

typedef wstring CTString;
struct Buddies 
{
	LPCWSTR strScreenName;
	DWORD dwBuddyCryptLevel;
	BOOL bsLogin;
};

class ComparerBuddy
{
public:
	bool operator () (const Buddies & va1, const Buddies & va2)
	{		
		wcout << va1.strScreenName << L", " << va2.strScreenName << endl;
		return va1.dwBuddyCryptLevel >= va2.dwBuddyCryptLevel;
		//~ if(va1.dwBuddyCryptLevel<va2.dwBuddyCryptLevel)
			//~ return FALSE;
		//~ else return TRUE;
		
	}
};

void main()
{
	//~ int int_array[20];
	//~ sort(int_array, int_array + 20);
	//~ return;
	vector<Buddies> vecSortedMembers;
	{
		Buddies b;
		b.strScreenName = L"1"; b.dwBuddyCryptLevel = 1; vecSortedMembers.push_back(b);
		b.strScreenName = L"2"; b.dwBuddyCryptLevel = 1; vecSortedMembers.push_back(b);
		b.strScreenName = L"3"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"4"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"5"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"6"; b.dwBuddyCryptLevel = 1; vecSortedMembers.push_back(b);
		b.strScreenName = L"7"; b.dwBuddyCryptLevel = 1; vecSortedMembers.push_back(b);
		b.strScreenName = L"8"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"9"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"10"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"11"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"12"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"13"; b.dwBuddyCryptLevel = 1; vecSortedMembers.push_back(b);
		b.strScreenName = L"14"; b.dwBuddyCryptLevel = 4; vecSortedMembers.push_back(b);
		b.strScreenName = L"15"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"16"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"17"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"18"; b.dwBuddyCryptLevel = 7; vecSortedMembers.push_back(b);
		b.strScreenName = L"19"; b.dwBuddyCryptLevel = 1; vecSortedMembers.push_back(b);
	}
	
	sort(vecSortedMembers.begin(),vecSortedMembers.end(),ComparerBuddy());
	
	for (vector<Buddies>::iterator i = vecSortedMembers.begin(); i != vecSortedMembers.end(); i ++)
	{
		wcout << i->strScreenName << L"/" << i->dwBuddyCryptLevel << endl;
	}
	
}