#include <iostream.h>
struct foo
{
    virtual ~foo()
    {}
};

template<class T>struct bar : public T, public foo
{};

struct zoo
{
    ~zoo()
    {
        cout << "~zoo\n";
    }
};

void main()
{
    delete (foo*)new bar<zoo>;
}