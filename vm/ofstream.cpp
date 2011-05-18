#include <fstream>
using namespace std;
void main()
{
	ofstream f("c:\\a.txt", ios::app);
	f<<"a\r\n";
}