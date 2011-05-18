#include <iostream>
using namespace std;

struct Class {
	virtual void fun() { cout << "Class::fun" << endl; }
};

typedef void (*Fun)(void);

int main() {
	Class objClass;
	Fun pFun = (Fun)*(int*)*(int*)(&objClass+0);
	pFun();
	objClass.fun();
	return 0;
}