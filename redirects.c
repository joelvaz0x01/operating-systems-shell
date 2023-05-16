#include "shell.h"

//  redirects.c
//  redirects tratamento dos simbolos por ordem inversa:  i) 2>  ii) > OU  >  iii) <

int redirects(int numargs, char *args[])
{
    if (numargs < 3)
        return numargs; // Guard the following section

    // i) Tratar do redirect do 2>      --> creat : FILE_MODE
    if (0 == strcmp(args[numargs - 2], "2>"))
    {
        int fd = creat(args[numargs - 1], FILE_MODE);
        if (fd < 0)
        {
            perror(NULL);
            exit(1); /*indicar um erro*/
        }
        dup2(fd, STDERR_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }
    if (numargs < 3)
        return numargs; // Guard the following section

    // ii.a) Tratar do redirect do >      --> creat : FILE_MODE
    if (0 == strcmp(args[numargs - 2], ">"))
    {
        int fd = creat(args[numargs - 1], FILE_MODE);
        if (fd < 0)
        {
            perror(NULL);
            exit(1); /*indicar um erro*/
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }
    else
    {
        // ii.b) Tratar do redirect do >>      --> open : O_WRONLY | O_APPEND
        if (0 == strcmp(args[numargs - 2], ">>"))
        {
            int fd = open(args[numargs - 1], (O_WRONLY | O_APPEND));
            if (fd < 0)
            {
                perror(NULL);
                exit(1); /*indicar um erro*/
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[numargs - 2] = NULL;
            numargs = numargs - 2;
        }
    }

    if (numargs < 3)
        return numargs; // Guard the following section

    // iii) Tratar do redirect do <      --> open : O_RDONLY
    if (0 == strcmp(args[numargs - 2], "<"))
    {
        int fd = open(args[numargs - 1], O_RDONLY);
        if (fd < 0)
        {
            perror(NULL);
            exit(1); /*indicar um erro*/
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }

    return numargs; // devolver o numero de argumentos a passar para execvp
}
