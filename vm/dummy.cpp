#include <sstream>
using namespace std;

char* buf = " \
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\
";
void main()
{
	ostringstream s;
	s << buf;
}