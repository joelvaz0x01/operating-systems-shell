#include "shell.h"

char prompt[100];

int main()
{
  int len;
  char linha[1024]; /* um comando */
  char *args[64];   /* com um maximo de 64 argumentos */

  strcpy(prompt, "SOSHELL: Introduza um comando : prompt> ");
  while (1)
  {
    printf(B_GRN "%s", prompt);
    printf(MR_WHITE);
    if (fgets(linha, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }
    len = strlen(linha);
    if (1 == len)
      continue; /* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    int numargs = parse(linha, args); /* particiona a string em argumentos */

    if (!builtin(numargs, args)) /* particiona a string em argumentos */
      execute(numargs, args);    /* executa o comando */
  }
  return 0;
}

/**
 * Verifica se o comando é embutido
 * @param numargs Número de argumentos
 * @param args Array de argumentos
 * @return 1 se for embutido, 0 se não for embutido
 */
int builtin(int numargs, char **args)
{
  if (strcmp(args[0], "sair") == 0)
  {
    exit(0);
    return 1;
  }
  if (strncmp(args[0], "42", 2) == 0)
  {
    printf("42 is the answer to life the universe and everything\n");
    return 1; /* funcionalidade embutida */
  }

  if (0 == strcmp(args[0], "obterinfo"))
  {
    printf("SoShell 2022 versão 1.0\n");
    return 1; // comando embutido
  }

  if (strlen(args[0]) > 4 && 0 == strncmp(args[0], "PS1=", 4))
  {
    strcpy(prompt, args[0] + 4);
    return 1; // comando embutido
  }

  if (0 == strcmp(args[0], "quemsoueu"))
  {
    system("id");
    return 1; // comando embutido
  }

  if (0 == strcmp(args[0], "cd"))
  {
    int err;
    if (NULL == args[1] || strcmp(args[1], "~") == 0)
      err = chdir(getenv("HOME"));
    else
      err = chdir(args[1]);
    if (err < 0)
      perror(args[1]);
    return 1; // comando embutido
  }

  if (0 == strcmp(args[0], "socp") && numargs == 3)
  {
    socp(args[1], args[2]);
    return 1; // comando embutido
  }

  if (0 == strcmp(args[0], "calc") && numargs == 4)
  {
    calc(args[1], args[2], args[3]);
    return 1; // comando embutido
  }

  if (0 == strcmp(args[0], "bits") && (numargs == 4 || numargs == 2))
  {
    bits(args[1], args[2], args[3]);
    return 1; // commando embutido
  }

  if (0 == strcmp(args[0], "isjpg") && numargs == 2)
  {
    int fd = open(args[1], O_RDONLY);
    if (fd < 0)
      printf("Erro ao abrir o ficheiro %s.\n", args[1]);
    else
    {
      isjpg(fd) ? printf("%s é um JPEG.\n", args[1]) : printf("%s não é um JPEG.\n", args[1]);
      close(fd);
    }
    return 1; // commando embutido
  }

  if (0 == strcmp(args[0], "aviso") && numargs == 3)
  {
    pthread_t th;
    aviso_t *ptr = (aviso_t *)malloc(sizeof(aviso_t));
    strcpy(ptr->msg, args[1]);
    ptr->tempo = atoi(args[2]);
    pthread_create(&th, NULL, avisowrapper, (void *)ptr);
    return 1; // commando embutido
  }

  if (0 == strcmp(args[0], "socpth") && numargs == 3)
  {
    pthread_t th;
    copiar_t *ptr = (copiar_t *)malloc(sizeof(copiar_t));
    strcpy(ptr->fonte, args[1]);
    strcpy(ptr->destino, args[2]);
    pthread_create(&th, NULL, socpwrapper, (void *)ptr);
    return 1; // commando embutido
  }

  if (0 == strcmp(args[0], "maior") && numargs == 3)
  {
    off_t fileOne = getFileSize(args[1]);
    off_t fileTwo = getFileSize(args[2]);
    if (fileOne != -1 && fileTwo != -1)
      fileOne == fileTwo
          ? printf("Ambos os ficheiros tem o mesmo tamanho: %Lf KB.\n", (long double)fileOne * 0.001)
      : fileOne > fileTwo
          ? printf("Tamanho do ficheiro %s: %Lf KB.\n", args[1], (long double)fileOne * 0.001)
          : printf("Tamanho do ficheiro %s: %Lf KB.\n", args[2], (long double)fileTwo * 0.001);
    return 1; // commando embutido
  }

  if (0 == strcmp(args[0], "setx") && numargs == 2)
  {
    changePermitions(args[1], 1, S_IXUSR);
    return 1; // commando embutido
  }

  if (0 == strcmp(args[0], "removerl") && numargs == 2)
  {
    changePermitions(args[1], 0, ~(S_IRGRP | S_IROTH));
    return 1; // commando embutido
  }

  if (0 == strcmp(args[0], "sols"))
  {
    listar(args[1]);
    return 1; // commando embutido
  }
  
  if (0 == strcmp(args[0], "tipo"))
  {
    showType(args[1]);
    return 1; // commando embutido
  }
  
  /* IMPORTANTE:
   * Devolver 0 para indicar que não existe comando embutido e que
   * será executado usando exec() na função execute.c
   */
  return 0;
}
