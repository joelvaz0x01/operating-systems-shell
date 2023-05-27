#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <math.h>
#include <dirent.h>
#include <time.h>

#define BUFFSIZE 128
#define FILE_MODE (S_IRUSR | S_IWUSR)

/**
 * Estrutura para o comando aviso
 * @param msg - Mensagem a mostrar
 * @param tempo - Tempo em segundos
*/
typedef struct
{
    char msg[100];
    int tempo;
} aviso_t;

/**
 * Estrutura para o comando copiar
 * @param fonte - Ficheiro de origem
 * @param destino - Ficheiro de destino
*/
typedef struct
{
    char fonte[100];
    char destino[100];
} copiar_t;

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int ultimo(int *numargs, char **args);

int builtin(int numargs, char **args);

void socp(char *fonte, char *destino);

void ioCopy(int IN, int OUT);

void calc(char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int isjpg(int fileDescriptor);

int redirects(int numargs, char *args[]);

void execommand(int *numargs, char **args);

int containsPipe(int numArgs, char **args);

void aviso(char *mesg, int tempo);

void *avisowrapper(void *args);

void *socpwrapper(void *args);

off_t getFileSize(char *filename);

void changePermitions(char *filename, int incr_permissions, int permissions);

char *getLastModified(char *path, char *filename);

void listar(char *pasta);

/* constantes que podem tornar uteis */

#define BG 0
#define FG 1
