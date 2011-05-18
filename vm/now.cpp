#include "common.h"
#include "time.h"

void main()
{
	time_t now;
	time(&now);
	now += 3600;
	cout << hex << now << endl;
}