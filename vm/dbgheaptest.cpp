/////////////////// copied and pasted relevant lines from dbgint.h

/*
* For diagnostic purpose, blocks are allocated with extra information and
* stored in a doubly-linked list.  This makes all blocks registered with
* how big they are, when they were allocated, and what they are used for.
*/

#define nNoMansLandSize 4

typedef struct _CrtMemBlockHeader
{
	struct _CrtMemBlockHeader * pBlockHeaderNext;
	struct _CrtMemBlockHeader * pBlockHeaderPrev;
	char *                      szFileName;
	int                         nLine;
#ifdef _WIN64
	/* These items are reversed on Win64 to eliminate gaps in the struct
	* and ensure that sizeof(struct)%16 == 0, so 16-byte alignment is
	* maintained in the debug heap.
	*/
	int                         nBlockUse;
	size_t                      nDataSize;
#else  /* _WIN64 */
	size_t                      nDataSize;
	int                         nBlockUse;
#endif  /* _WIN64 */
	long                        lRequest;
	unsigned char               gap[nNoMansLandSize];
	/* followed by:
	*  unsigned char           data[nDataSize];
	*  unsigned char           anotherGap[nNoMansLandSize];
	*/
} _CrtMemBlockHeader;

#define pbData(pblock) ((unsigned char *)((_CrtMemBlockHeader *)pblock + 1))
#define pHdr(pbData) (((_CrtMemBlockHeader *)pbData)-1)

/////////////////// end of copy and paste

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef unsigned long ulong;
typedef unsigned char uchar;

void hexdump(const void * buf, size_t size)
{
	const uchar * cbuf = (const uchar *) buf;
	const ulong BYTES_PER_LINE = 16;
	ulong offset, minioffset;

	for (offset = 0; offset < size; offset += BYTES_PER_LINE)
	{
		// OFFSETXX  xx xx xx xx xx xx xx xx  xx xx ...
		//       ... xx xx xx xx xx xx   abcdefghijklmnop
		printf("%08x  ", cbuf + offset);
		for (minioffset = offset;
			minioffset < offset + BYTES_PER_LINE;
			minioffset++)
		{
			if (minioffset - offset == (BYTES_PER_LINE / 2)) {
				printf(" ");
			}

			if (minioffset < size) {
				printf("%02x ", cbuf[minioffset]);
			} else {
				printf("   ");
			}
		}
		printf("  ");

		for (minioffset = offset;
			minioffset < offset + BYTES_PER_LINE;
			minioffset++)
		{
			if (minioffset >= size)
				break;

			if (cbuf[minioffset] < 0x20 ||
				cbuf[minioffset] > 0x7e)
			{
				printf(".");
			} else {
				printf("%c", cbuf[minioffset]);
			}
		}
		printf("\n");
	}
}

#define BUF_SIZE		10
#define ALIGNMENT		4
#define ALIGNED_SIZE	12

int main()
{
	char * p = (char *) malloc(BUF_SIZE);
	strcpy(p, "Yoni");

	printf("Before freeing:\n\n");
	hexdump(pHdr(p), sizeof(_CrtMemBlockHeader) + BUF_SIZE + nNoMansLandSize);
	printf("\n\n");

	free(p);

	printf("After freeing:\n\n");
	hexdump(pHdr(p), sizeof(_CrtMemBlockHeader) + BUF_SIZE + nNoMansLandSize);
	printf("\n\n");

	return 0;
}
