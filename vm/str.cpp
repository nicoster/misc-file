#include <iostream>
using namespace std;

void main()
{
    string str(0, '*');
    cout << str.c_str() << endl;
    return;
    
//    cout << (int)(string("") < string("1"));
    // string str(0);
//	cout<<string(4, 'a').c_str()<<endl;
}
/*
struct MapCompare : public binary_function<MapKey, MapKey, bool>
{
    bool operator()(const MapKey& left, const MapKey& right) const
    {
        return left.bstrStreamName < right.bstrStreamName ? true : left.bstr
        
        bool ret = false;

        if (left.bstrAccountName == right.bstrAccountName)
        {
            if (left.bstrStreamName == right.bstrStreamName)
            {
                if (left.bstrID < right.bstrID)
                {
                    ret = true;
                }
                else if (left.bstrGUID < right.bstrGUID)
                {
                    ret = true;
                }
            }
            else if (left.bstrStreamName < right.bstrStreamName)
            {
                ret = true;
            }
        }
        else if (left.bstrAccountName < right.bstrAccountName)
        {
            ret = true;
        }

        return ret;
    }
};
*/