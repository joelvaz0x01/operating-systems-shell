#include "shell.h"

void socp(char *fonte, char *destino)
{
    int f_fonte = open(fonte, O_RDONLY);
    if (f_fonte == -1)
    {
        perror("Erro ao abrir arquivo de origem");
        return;
    }

    int f_destino = creat(destino, S_IRUSR | S_IWUSR);

    if (f_destino == -1)
    {
        perror("Erro ao criar arquivo de destino");
        return;
    }

    ioCopy(f_fonte, f_destino);
}

void ioCopy(int IN, int OUT)
{
    int n;
    char buf[BUFFSIZE];
    while ((n = read(IN, buf, BUFFSIZE)) > 0)
    {
        if (write(OUT, buf, n) != n)
            perror("Erro de escrita!\n");
    }
    if (n < 0)
        perror("Erro de leitura!\n");
}