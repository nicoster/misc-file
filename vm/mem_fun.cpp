#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
typedef wstring CTString;

struct identity_t
{
	
};

typedef struct app_t
{
	CTString 
		strName,
		strID,
		strCurrentDir,
		strStatus,
		appConsPackage;
	vector<identity_t> identities;
	int clear()
	{
		strName = strID = strCurrentDir = strStatus = L"";
		return 0;
	}
}widget_t;

struct library_t
{
	CTString 
		strName,
		strID,
		strType;
	vector<app_t> apps;
	int clear()
	{
		strName = strID = strType = L"";
		for_each(apps.begin(), apps.end(), mem_fun_ref(app_t::clear));
		return 0;
	}
};

void main(){}