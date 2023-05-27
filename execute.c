#include "shell.h"

/**
 * Cria um processo progénito e executa um programa
 * @param numargs Número de argumentos
 * @param args Array de argumentos
 */
void execute(int numargs, char **args)
{
  int pid, pidFilho, status, fd[2];
  int code = ultimo(&numargs, args);

  if ((pid = fork()) < 0)
  {                  /* cria um processo progenito */
    perror("forks"); /* NOTE: perror() produz uma pequema mensagem de erro para o stream */
    exit(1);         /* estandardizado de erros que descreve o ultimo erro encontrado */
  }                  /* durante uma chamada ao sistema ou funcao duma biblioteca */

  if (pid == 0)
  {
    int indice = containsPipe(numargs, args);
    if (-1 == indice)
      execommand(&numargs, args);
    if (indice > 0)
    {
      args[indice] = NULL;
      pipe(fd);
      pidFilho = fork();
      if (0 == pidFilho) // write
      {
        numargs = indice;
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
      }
      else // read
      {
        args = args + indice + 1;
        numargs = numargs - indice - 1;
        dup2(fd[0], STDIN_FILENO); // duplicar o descritor de ficheiro de leitura do PIPE para a posição na tabele de FD do STDIN
        close(fd[1]);
        close(fd[0]); // fechar o descritor do ficheiro do pipe que este processo não necessita.
      }
      execommand(&numargs, args); // Chamar a função execvp() para executar os comandos agora ligados via um pipe.
    }
    /* NOTE:
     * As versoes execv() e execvp() de execl() sao uteis quando
     * o numero de argumentos nao e. conhecido. Os argumentos de execv()
     * e execvp() sao o nome do ficheiro a ser executado e um vector de
     * strings que contem os argumentos. O ultimo argument
     */
    perror(*args);
    exit(1);
  }

  if (FG == code) // Se for FG, esperar pelo filho
    while (wait(&status) != pid)
      /* spin fazer nada */;

  return;
}

/**
 * Verifica se existem redirecionamentos
 * @param numargs Número de argumentos
 * @param args Array de argumentos
 * @return FG (-1) se não existirem redirecionamentos, BG (0) se existirem
 */
int ultimo(int *numargs, char **args)
{
  if (args[*numargs - 1][0] == '&')
  {
    *numargs = *numargs - 1;
    args[*numargs] = NULL;
    return BG;
  }
  return FG; /* return FG ou BG definidos no shell.h */
}

/**
 * Executa um comando com redirecionamentos
 * @param numargs Número de argumentos
 * @param args Array de argumentos
 */
void execommand(int *numargs, char **args)
{
  if (-1 != redirects(*numargs, args))
  {
    if (NULL == strstr(*args, "/"))
      execvp(*args, args);
    else
      execl(*args, *args, (char *)NULL);
  }
  else
    exit(1);
}

/**
 * Verifica se existe um pipe no array de strings
 * @param numargs Número de argumentos
 * @param args Array de argumentos
 * @return Índice do pipe ou -1 se não existir
 */
int containsPipe(int numargs, char **args)
{
  int index;
  for (index = 0; index < numargs; index++)
    if (args[index][0] == '|')
    {
      return index;
    }
  return -1;
}
