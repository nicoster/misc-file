#include <iostream>
using namespace std;

struct tri_char_traits : public char_traits<char>
{
    static size_t __cdecl length(const char*_U)
    {
        if (! _U) return 0;
        return (strlen(_U));
    }
};

typedef basic_string<char, tri_char_traits> string2;
void main()
{
    string2 str;
    char* psz = 0;
    str.insert(0, "1");
    //~ str.insert(0, psz);
    //~ str = psz;
    //~ str += psz;
    cout << str.c_str();
}