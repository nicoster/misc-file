#pragma warning(disable:4786)

#include <iostream>
#include <string>
#include <map>

using namespace std ;

typedef map<string, int> STRING2INT;

void main()
{
    _asm int 3;
    STRING2INT MyMap, MyMap2;
    STRING2INT::iterator MyIterator;
    string MyBuffer;

    // print the maximum number of <key,data> pairs that MyMap can hold
    cout << "MyMap is capable of holding " << MyMap.max_size()
         << " <string,int> pairs" << endl;

    if(!MyMap.empty())
        cout << "MyMap has " << MyMap.size() << " entries" << endl;
    else
        cout << "MyMap is empty" << endl;
        cout << "Entering new entries in MyMap" << endl;
    // Fill in MyMap with the months of the year, mapped to their number
    // January - 1, February - 2, etc. using operator[].
    MyMap["January"] = 1;
    MyMap["February"] = 2;
    MyMap["March"] = 3;
    MyMap["April"] = 4;
    MyMap["May"] = 5;
    MyMap["June"] = 6;
    MyMap["July"] = 7;
    MyMap["August"] = 8;
    MyMap["September"] = 9;
    MyMap["October"] = 10;
    MyMap["November"] = 11;
    MyMap["December"] = 12;
    
    _asm int 3;
    MyMap2 = MyMap;
    
    cout << MyMap["a"]<<endl;
	return;
	MyMap.erase("a");

    if(!MyMap.empty())
        cout << "MyMap has " << MyMap.size() << " entries" << endl;
    else
        cout << "MyMap is empty" << endl;

    // Ask the user for a month of the year and print the number
    // that corresponds to the month entered
    //MyIterator = MyMap.end();
    while(MyIterator == MyMap.end()){
        cout << "Enter a Month :";
        cin >> MyBuffer;
        if((MyIterator = MyMap.find(MyBuffer)) != MyMap.end())
            cout << (*MyIterator).first << " is Month Number "
                 << (*MyIterator).second << endl;
        else
            cout << "Enter a Valid Month (example: March)" << endl;
    }

    // empty MyMap - note that clear simply calls erase(begin(),end());
    MyMap.clear();

    if(!MyMap.empty())
        cout << "MyMap has " << MyMap.size() << " entries" << endl;
    else
        cout << "MyMap is empty" << endl;
        cout << "Entering new entries in MyMap" << endl;
    // Fill MyMap with the days of the week, each mapped to an int
    MyMap["Monday"] = 1;
    MyMap["Tuesday"] = 2;
    MyMap["Wednesday"] = 3;
    MyMap["Thursday"] = 4;
    MyMap["Friday"] = 5;
    MyMap["Saturday"] = 6;
    MyMap["Sunday"] = 7;

    if(!MyMap.empty())
        cout << "MyMap has " << MyMap.size() << " entries" << endl;
    else
        cout << "MyMap is empty" << endl;

    // Ask the user for a day of the week and print the number
    // that corresponds to the day entered
    MyIterator = MyMap.end();
    while(MyIterator == MyMap.end()){
        cout << "Enter a Day of the Week:";
        cin >> MyBuffer;
        if((MyIterator = MyMap.find(MyBuffer)) != MyMap.end())
            cout << (*MyIterator).first << " is Day Number "
                 << (*MyIterator).second << endl;
        else
            cout <<"Enter a Valid Day of the Week(example: Monday)"<< endl;
    }
// Now clear MyMap again - this time using erase instead of clear
    MyMap.erase(MyMap.begin(), MyMap.end());

    if(!MyMap.empty())
        cout << "MyMap has " << MyMap.size() << " entries" << endl;
    else
        cout << "MyMap is empty" << endl;

}

