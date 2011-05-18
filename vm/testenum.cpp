class foo{public:enum et{A,B};};
class bar{typedef foo::et et; bar(){foo::A;}};
void main(){}