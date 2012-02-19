#include <iostream>
using namespace std;

class 
	__declspec(novtable) 
Base {
public:
    Base() {
        cout << "In Base" << endl;
        cout << "Virtual Pointer = " << (int*)this << endl;
        cout << "Address of Vtable = " << (int*)*(int*)this << endl;
  //      cout << "Value at Vtable = " << (int*)*(int*)*(int*)this << endl;
        cout << endl;
    }
    virtual void f1() { cout << "Base::f1" << endl; }
};

class Drive : public Base {
public:
    Drive() {
        cout << "In Drive" << endl;
        cout << "Virtual Pointer = " << (int*)this << endl;
        cout << "Address of Vtable = " << (int*)*(int*)this << endl;
        cout << "Value at Vtable = " << (int*)*(int*)*(int*)this << endl;
        cout << endl;
    }
    virtual void f1() { cout << "Drive::f2" << endl; }
};

class Drive2 : public Base {
public:
    Drive2() {
        cout << "In Drive2" << endl;
        cout << "Virtual Pointer = " << (int*)this << endl;
        cout << "Address of Vtable = " << (int*)*(int*)this << endl;
        cout << "Value at Vtable = " << (int*)*(int*)*(int*)this << endl;
        cout << endl;
    }
    virtual void f1() { cout << "Drive2::f2" << endl; }
};

int main() {
	Base b;
	cout << "sizeof Base:" << sizeof(b) << endl;
    Drive d;
	Drive2 d2;
    return 0;
}