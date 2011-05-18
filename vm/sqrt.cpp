#include "iostream"
template< int N, int Num >
class PowN
{
public:
	enum
   {
		result = Num * PowN<N - 1, Num>::result,
   };
};

template<int Num>
class PowN<0, Num> // 
{
public:
       enum
       {
           result = 1,
       };
};

// test case: 3
int main()
{
    std::cout<<"PowN<2, 3>::result"<< PowN<2, 3>::result << std::endl;
    // 
  const int n = 3;
  const int num = 10;

  std::cout<<"PowN<n, num>::result"<< PowN<n, num>::result << std::endl;

     return 0;
}