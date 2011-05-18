#include <iostream.h>
#include <string.h>
template<class T, int WNDCLASSNAME>
class TimerWndT
{
public:
	TimerWndT()
	{
		
		cout<<typeid(T).raw_name()<<endl;
	}
};

class type_info {
public:
    _CRTIMP virtual ~type_info();
    _CRTIMP bool operator==(const type_info& rhs) const;
    _CRTIMP bool operator!=(const type_info& rhs) const;
    _CRTIMP int before(const type_info& rhs) const;
    _CRTIMP const char* name() const;
    _CRTIMP const char* raw_name() const;
};

void main()
{
	char name[5];
	strncpy(name, "aaaaaa", 5);
	cout<<name<<endl;
	TimerWndT<type_info, 1> t;
	TimerWndT<long, 1> t2;
}