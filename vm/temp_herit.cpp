#include "common.h"

template <class T>
struct foo{};
	
template <class T>
struct bar : public foo<T>{};
	
void main()
{
	bar<int> *p = new foo<int>;
}