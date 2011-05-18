#include <stdio.h>
struct gzip_header_t{short w[5];} gzip_header = {0x8b1f, 8, 0, 0, 0};
void main()
{
	gzip_header_t tmp;
	
	if (tmp == gzip_header);
}
