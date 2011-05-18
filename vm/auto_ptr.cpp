#include "common.h"

void main()
{
    try
    {
        auto_ptr<char> sp;
//        string str(sp.get());
        cout << sp.get() << "";
    }
    catch (...)
    {
        cout << "crash...";
    }
}