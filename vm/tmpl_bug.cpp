#include <iostream>
using namespace std;

template <size_t n> void foo( void )
{
    cout << n << endl;
};
void bar1( void )
{
    foo<1>();
}
void bar2( void )
{
    foo<2>();
}

int main(int argc, char* argv[])
{
    bar1();
    bar2();

return 0;
}