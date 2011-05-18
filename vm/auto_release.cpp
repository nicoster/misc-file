#include <string>
#include <memory>
using namespace std;
void main()
{
	auto_ptr<string> p(new string("aa"));
}