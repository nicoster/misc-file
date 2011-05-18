#include <stdio.h>
#include <iostream.h>
void main( void )
{
   char  tokenstring[] = "15 12 14...";
   char  s[81];
   char  s2[81];
   char  c;
   int   i;
   float fp;

   /* Input various data from tokenstring: */
   cout<<sscanf( tokenstring, "%s %s", s, s2 )<<endl;
   cout<<sscanf( tokenstring, "%c", &c )<<endl;
   cout<<sscanf( tokenstring, "%d", &i )<<endl;
   cout<<sscanf( tokenstring, "%f", &fp )<<endl;

   /* Output the data read */
   printf( "String    = %s\n", s2 );
   printf( "Character = %c\n", c );
   printf( "Integer:  = %d\n", i );
   printf( "Real:     = %f\n", fp );
}
