#include "common.h"
#include <iostream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
//define multimap type as string/string dictionary
    typedef multimap<string,string> StrStrMMap;

//create empty dictionary
    StrStrMMap dict;

//insert some elements in random order
    dict.insert(make_pair("day","Tag"));
    dict.insert(make_pair("strange","fremd"));
    dict.insert(make_pair("car","Auto"));
    dict.insert(make_pair("smart","elegant"));
    dict.insert(make_pair("trait","Merkmal"));
    dict.insert(make_pair("strange","seltsam"));
    dict.insert(make_pair("smart","raffiniert"));
    dict.insert(make_pair("smart","klug"));
    dict.insert(make_pair("clever","raffiniert"));

//print all elements
    StrStrMMap::iterator pos;
    cout.setf (ios::left, ios::adjustfield);
    cout << ' ' << setw(10) << "english "
    << "german " << endl;
    cout << setfil('-') << setw(20) << ""
    << setfil(' ') << endl;
    for (pos = dict.begin(); pos != dict.end(); ++pos)
    {
        cout << ' ' << setw(10) << pos>first.c_str()
        << pos->second << endl;
    }
    cout << endl;

//print all values for key "smart"
    string word("smart");
    cout << word << ": " << endl;

    for (pos = dict.lower_bound(word);
            pos != dict.upper_bound(word); ++pos)
    {
        cout << " " << pos->second << endl;
    }

//print all keys for value "raffiniert"
    word = ("raffiniert");
    cout << word << ": " << endl;
    for (pos = dict.begin(); pos != dict.end(); ++pos)
    {
        if (pos->second == word)
        {
            cout << " " << pos->first << endl;
        }
    }
}

