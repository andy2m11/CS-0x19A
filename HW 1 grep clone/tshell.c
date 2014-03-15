#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 1024

void err_sys(char* message)
{
   perror(message);
   exit(EXIT_FAILURE);
}

void* secure_malloc(int size)
{
   void* res = malloc(size);

   if(!res)
   {
      fprintf(stderr, "malloc() failure -- out of memory");
      exit(EXIT_FAILURE);
   }
   return res;
}

char* secure_strdup(char* source)
{
   void* res = secure_malloc(strlen(source)+1);

   strcpy(res, source);
   return res;  
}

int count_words(char* line)
{
   int words=0, in_word=0;  

   while(*line)
   {
      if(isspace(*line))
      {
	 in_word = 0;
      }
      else
      {
	 if(in_word == 0)
	 {
	    words++;
	    in_word = 1;
	 }
      }
      line++;
   }
   return words;
}

char **build_argv(char* line)
{
   int argc = count_words(line);
   int i;
   char *new;
   char **argv;

   if(argc ==0)
   {
      return NULL;
   }
   argv = secure_malloc(sizeof(char*)*(argc+1));   
   
   for(i=0; i<argc; i++)
   {
      while(isspace(*line))
      {
	 line++;
      }
      for(new=line; *new && !isspace(*new); new++);
      /* Empty body */
      *new = '\0';
      argv[i] = secure_strdup(line);
      line = new+1;
   }
   argv[i] = NULL;
   return argv;
}

void print_argv(char **argv)
{
   int i;

   printf("Command: %s\n", argv[0]);
   printf("Arguments:\n");
   for(i=0; argv[i]; i++)
   {
      printf("argv[%d]: ", i);
      printf("%s\n", argv[i]);
   }
   printf("=======\n");
}

int main(void)
{
//   pid_t  child_pid;
   char  line[MAX_LINE];
   char  *line_res;
   char **argv;
   
   while(1)
   {
      printf("# ");fflush(NULL);
      line_res = fgets(line, MAX_LINE, stdin);
      if(!line_res)
      {
	 break;
      }
      argv = build_argv(line);
      if(!argv)
      {
	 continue;
      }      
      print_argv(argv);

   }
   return EXIT_SUCCESS;
}
