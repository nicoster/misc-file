#include <iostream> 

using namespace std; 

template <typename T = int> 
class C 
{ 
private: 
class _helper 
{ 
public: 
_helper() { cout << "C::_helper::_helper()" << endl; } 
~_helper() { cout << "C::_helper::~_helper()" << endl; } 
}; 

public: 
void foo(){void * x = &data_;} 
static _helper data_; 
}; 
template<typename T> 
typename C<T>::_helper C<T>::data_; 

template <typename T> 
inline void ignore_warning(const T&) {} 

int main() 
{ 
cout<<"1\n";
C<int> c; 
cout<<"2\n";
c.foo(); 
ignore_warning(c); 
} 