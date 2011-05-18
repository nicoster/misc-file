#include <string.h>
#include <stdio.h>

char string[] = "A string\0of ,,tokens\0and some  more tokens";
char seps[]   = " ,\t\0";
char *token;

void main( void )
{
   printf( "%s\n\nTokens:\n", string );
   /* Establish string and get the first token: */
   token = strtok( string, seps );
   while( token != NULL )
   {
      /* While there are tokens in "string" */
      printf( " %s\n", token );
      /* Get next token: */
      token = strtok( NULL, seps );
   }
}
