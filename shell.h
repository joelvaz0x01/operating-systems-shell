#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#define BUFFSIZE 128

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int ultimo(int *numargs, char **args);

int builtin(int numargs, char **args);

void socp(char *fonte, char *destino);

void ioCopy(int IN, int OUT);

/* constantes que podem tornar uteis */

#define BG 0
#define FG 1
