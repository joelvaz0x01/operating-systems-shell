#include "shell.h"

/**
 * Mosta um aviso durante um determinado tempo
 * @param mesg - Mensagem a mostrar
 * @param tempo - Tempo em segundos
 */
void aviso(char *mesg, int tempo)
{
    while (tempo > 0)
    {
        sleep(1);
        tempo--;
    }
    fprintf(stderr, "Aviso : %s\n", mesg);
}

/**
 * Mosta um aviso durante um determinado tempo (wrapper)
 * @param args - Argumentos
 */
void *avisowrapper(void *args)
{
    aviso_t *ptr = (aviso_t *)args;
    aviso(ptr->msg, ptr->tempo);
    free(ptr);
    return NULL;
}
