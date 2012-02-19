#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

typedef struct {
	char *name;
} Command;

Command commands[] = {
	(char*)"login",
	(char*)"im",
	(char*)"re",
	(char*)"ls",
	(char*)"cat",
	(char*)"groupchat",
	(char*)"join",
	(char*)"leave",
	(char*)"help",
	(char*)"sendfile",
	(char*)"set",
	(char*)"switch",
	(char*)"add",
	(char*)"del",
	(char*)"addgroup",
	(char*)"delgroup",
	(char*)"ren",
	0
};

/* A static variable for holding the line. */
static char *line_read = (char *)NULL;

char *
rl_gets ()
{
  /* If the buffer has already been allocated,
     return the memory to the free pool. */
  if (line_read)
    {
      free (line_read);
      line_read = (char *)NULL;
    }

  /* Get a line from the user. */
  line_read = readline ("- ");

  /* If the line has any text in it,
     save it on the history. */
  if (line_read && *line_read)
    add_history (line_read);

  return (line_read);
}

/* Generator function for command completion.  STATE lets us
   know whether to start from scratch; without any state
   (i.e. STATE == 0), then we start at the top of the list. */
char *
command_generator
   (const char *text,
   int state)
{
   static int list_index, len;
   char *name;

   /* If this is a new word to complete, initialize now.  This
      includes saving the length of TEXT for efficiency, and
      initializing the index variable to 0. */
   if (!state)
   {
      list_index = 0;
      len = strlen (text);
   }

   /* Return the next name which partially matches from the
      command list. */
   while (name = commands[list_index].name)
   {
      list_index++;

      if (strncmp (name, text, len) == 0)
		{
		   char *ret = (char*)malloc (strlen (name) + 1);
		   strcpy (ret, name);
		   return (ret);
		}
   }

   /* If no names matched, then return NULL. */
   return ((char *)NULL);
}

/* Attempt to complete on the contents of TEXT.  START and END
   bound the region of rl_line_buffer that contains the word to
   complete.  TEXT is the word to complete.  We can use the entire
   contents of rl_line_buffer in case we want to do some simple
   parsing.  Returnthe array of matches, or NULL if there aren't any. */
char **
jabber_completion (const char* text, int start, int end)
{
   char **matches;

   matches = (char **)NULL;

   /* If this word is at the start of the line, then it is a command
      to complete.  Otherwise it is the name of a file in the current
      directory. */
   if (start == 0)
      /* TODO */
      matches = completion_matches (text, command_generator);
      /* matches = rl_completion_matches (text, command_generator); */

   return (matches);
}

int main(int, char**)
{
//	rl_readline_name = (char*)"readln ";
	rl_attempted_completion_function = jabber_completion;
	while(rl_gets());
}