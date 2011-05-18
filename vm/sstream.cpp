#include <sstream>
#include <iostream>
using namespace std;


class aputil_stream : public ostream
{
public:
	explicit aputil_stream() : ostream(&m_streambuf) {}
	~aputil_stream(){ *this<<endl; cout << str();}
	aputil_stream& l_value(){return *this;}
public:
	stringbuf *rdbuf() const{return ((stringbuf *)&m_streambuf);}
	string str(){	return m_streambuf.str();}
private:
	stringbuf m_streambuf;
};	

template<class _E, class _Tr, class _A> 
inline aputil_stream& __cdecl operator<<(
    aputil_stream& _O,
    const basic_string<_E, _Tr, _A>& _X)
{
	if (_X.length() > 2)
		((basic_ostream<_E, _Tr>&)_O)  << _X.substr(0, 2) << "...";
	else
		((basic_ostream<_E, _Tr>&)_O) << _X;
	return (_O); 
}

//template<class _E> 
inline aputil_stream& __cdecl operator<<(
		aputil_stream& _O, const char *_X)
{
	if (_X) _O << string(_X);
	return _O;
}

void main()
{
	string str("aa");
	aputil_stream ss;
	char * p = "5678";
	ss << p;
	ss << "asdf"<< str << "123456";

	//cout << string("123456").substr(0, 2);
	return;	
	ostringstream oss;
	//~ oss.str();
	
	//~ int n;
	//~ cout<< ostringstream().operator <<("2").rdbuf()->str();
	//~ cout<<n;
	//~ stringstream ss;
	//~ ss << "5" << "7";
	//~ ss >> n;
	//~ ss.clear();
	//~ cout << n;
	//~ ss << "6";
	//~ ss >> n;
	//~ cout << n;
	//~ return; 
	//~ stringstream("a5a")>>n;
	//~ cout << n;
	//~ return;
	//~ stringstream("7").operator >>(n);
	//~ _asm int 3;
	//~ stringstream(1) >> n;
	//~ cout<<n;
}