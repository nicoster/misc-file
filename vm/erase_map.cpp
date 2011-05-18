#include <map>
#include <iostream>
using namespace std;

void main()
{
	map<int, int> v;
	v[1] = 1; 	v[112] = 11; 	v[1112] = 111; v[1111] = 1111;
    for(map<int, int>::iterator vi=v.begin();vi!=v.end();)
    {
        if(vi->first % 2 == 0)
        {
            cout << "Erasing " << vi->first << endl;
            vi = v.erase(vi);
        }
        else ++vi;
    }	
	
	cout << v.size();
}