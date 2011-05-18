#include <sstream>
#include <iostream>
using namespace std;

class aputil_stream : public ostream
{
public:
	explicit aputil_stream() : ostream(&m_streambuf) {}
	~aputil_stream(){ }//*this<<endl; cout << str();}
	aputil_stream& l_value(){return *this;}
public:
	stringbuf *rdbuf() const
	{
		return ((stringbuf *)&m_streambuf);
	}
	string str(){	return m_streambuf.str();}
private:
	stringbuf m_streambuf;
};	

char* buf = " \
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\
";

void main()
{
//	_asm int 3;
	const int buf2len = 10 * 1024 * 1024;
	char* buf2 = new char[buf2len];
	memset(buf2, 0, buf2len);
	int buflen = strlen(buf);
	for (int i = 0; i < buf2len / buflen; i ++)
		memcpy(buf2 + i * buflen, buf, buflen);
	cout << strlen(buf2);
// 	string str;
// 	str += buf2;
	aputil_stream s;
	s << buf2;
}