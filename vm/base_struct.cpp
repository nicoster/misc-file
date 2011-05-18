#define BASE_STRUCT(T) \
struct T; \
inline T::T(){init();} \
struct T
	
BASE_STRUCT(foo)
{
	void init(){};
};

void main()
{
	foo fl;
}