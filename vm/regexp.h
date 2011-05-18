#pragma once
#include "deelx.h"

template <class T>
inline T RegGetGroup(T const& src, MatchResult const& mr, int group)
{
	if (! mr.IsMatched()) return T();
	int start = mr.GetGroupStart(group), end = mr.GetGroupEnd(group);
	return src.substr(start, end - start);
}

template <class T>
inline basic_string<T, char_traits<T>, allocator<T> > RegReplace(CRegexpT<T> const& reg, basic_string<T, char_traits<T>, allocator<T> > const& strSrc, basic_string<T, char_traits<char>, allocator<char> > const& strReplacePattern)
{
	basic_string<T, char_traits<T>, allocator<T> > strRet;
	T* pstr = reg.Replace(strSrc.c_str(), strReplacePattern.c_str());
	strRet = pstr;
	reg.ReleaseString(pstr);
	return strRet;
}
