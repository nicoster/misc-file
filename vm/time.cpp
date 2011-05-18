#include "common.h"

void main()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time ( &rawtime );
    rawtime += 24 * 60 * 60;
    timeinfo = localtime ( &rawtime );

    strftime (buffer,80,"%x %X> ",timeinfo);
    cout << buffer;
}