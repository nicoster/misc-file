#include "common.h"

struct key_t
{	
	string first, second;
	operator < (key_t const& rhs) const
	{
		return first < rhs.first || second < rhs.second;
		
		if (first == rhs.first) 
			return second < rhs.second;
		else
			return first < rhs.first;
	}
};

void main()
{
	map<key_t, int> m;
	key_t k1, k2;
	k1.first = "1"; k1.second = "4";
	k2.first = "2"; k2.second = "3";
	cout << (k1 < k2) << endl << (k2 < k1) << endl;
	
	m[k2] = 0;
	m[k1] = 0;
	
	cout << (m.find(k1) == m.end()) << endl;
}