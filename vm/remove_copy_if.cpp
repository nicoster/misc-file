#include <algorithm>
#include <iostream>
using namespace std;

template<class _Char>
inline void trim_all( const basic_string<_Char>& src, basic_string<_Char>& target, const _Char& filter )
{
	target.resize( src.size() );
	basic_string<_Char>::iterator iter = remove_copy( src.begin(), src.end(), target.begin(), filter);
	if (iter != target.end())
		target.erase( iter, target.end() );
}

void main()
{
	wstring sz1 = L" 12 3 4 2 3 2", sz2;
//	wstring::iterator i = remove_copy(sz1, sz1 + 7, sz2, L'1');
	trim_all(sz1, sz1, L' ');
	wcout << sz1.c_str();
}