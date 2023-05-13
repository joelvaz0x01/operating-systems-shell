#include "shell.h"

char prompt[100];

int main ()
{
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf ("%s", prompt);
    if (fgets (linha, 1023, stdin) == NULL)
    {
      printf ("\n");
      exit (0);
    }
    len = strlen (linha);
    if (1 == len)
      continue;/* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    parse (linha, args);/* particiona a string em argumentos */

    if (!builtin (args))
      execute (args);/* executa o comando */
    }
  return 0;
}

int builtin (char **args)
{
  if (strcmp (args[0], "sair") == 0)
  {
    exit (0);
    return 1;
  }
  if (strncmp (args[0], "42", 2) == 0)
  {
    printf ("42 is the answer to life the universe and everything\n");
    return 1;/* funcionalidade embutida */
  }
  /* IMPORTANTE : 
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
