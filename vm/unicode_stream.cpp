#define UNICODE
#define _UNICODE
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
class unicode_stream : public wostream
{
public:
	unicode_stream() : wostream(&m_streambuf){}
	wstringbuf *rdbuf() 
	{
		return &m_streambuf;
	}
	
	wstring str()
	{
		return m_streambuf.str();
	}
private:
	wstringbuf m_streambuf;
	
};

void main()
{
	unicode_stream s;
	s << 1 << L"ssss"<<endl;
	wcout << s.str();
}