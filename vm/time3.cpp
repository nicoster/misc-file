#include "common.h"

void main()
{
	tm t;
        t.tm_sec = 1;     /* seconds after the minute - [0,59] */
        t.tm_min = 1;     /* minutes after the hour - [0,59] */
        t.tm_hour = 1;    /* hours since midnight - [0,23] */
        t.tm_mday = 1;    /* day of the month - [1,31] */
        t.tm_mon = 1;     /* months since January - [0,11] */
        t.tm_year=105;    /* years since 1900 */
        t.tm_wday = 0;    /* days since Sunday - [0,6] */
        t.tm_yday = 0;    /* days since January 1 - [0,365] */
        t.tm_isdst = 0;   /* daylight savings time flag */

	time_t t2 = mktime(&t);
	cout << ctime(&t2);
}