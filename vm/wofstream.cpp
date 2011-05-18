#include <fstream>
#include <string>

using namespace std;

wofstream fs;

void main()
{
	fs.open("d:\\log.log");

	wstring str, str2;

	for(int i = 0; i < 5000; i ++) str += L"this is a testdsdsfa";
	for (int j = 0; j < 100; j ++) str2 += L"this is a testdsdsfa";
		
	fs << str2 << endl << endl;
	fs.flush();
	fs << str2 << endl << endl;
	fs.flush();
	fs << str << endl << endl;
	fs.flush();
	fs << str2 << endl << endl;
	fs.flush();
	
	fs << L"Over!";
}