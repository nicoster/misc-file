void main()
{
	_asm int 3;
	char a[] = "abcde";
	char b[80] = "abcde";
	char c[40] = {0};
	
	int n;
	char szLabel[128]={""}; 
	a[0] = b[0] = c[0] = szLabel[0] = '\0';
}