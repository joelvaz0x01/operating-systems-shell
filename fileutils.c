#include "shell.h"

off_t getFileSize(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o ficheiro");
        return -1;
    }
    // lseek retorna valores off_t, mais tarde fazer casting
    off_t fileSize = lseek(fd, 0, SEEK_END);

    if (fileSize == -1)
    {
        perror("Ocorreu um erro");
        close(fd);
        return -1;
    }
    close(fd);
    return fileSize;
}

void changePermitions(char *filename, int incr_permissions, int permissions)
{
    /* View more about `struct stat` on section `The stat structure` or `man 2 stat`:
     * https://www.man7.org/linux/man-pages/man2/stat.2.html
     */
    struct stat st;
    if (stat(filename, &st) == -1)
    {
        perror("Erro ao obter as permissões");
        return;
    }

    if (incr_permissions)
        st.st_mode |= permissions; // Adiciona permissões
    else
        st.st_mode &= permissions; // Remove permissões

    if (chmod(filename, st.st_mode) == -1)
    {
        perror("Erro ao alterar as permissões");
        return;
    }
    return;
}

char *getLastModified(char *path, char *filename)
{
    struct stat st;
    char filenamePath[1024];

    sprintf(filenamePath, "%s/%s", path, filename);

    if (stat(filenamePath, &st) == -1)
    {
        perror("Erro ao obter as permissões");
        return NULL;
    }
    return ctime(&st.st_ctime);
}

void listar(char *pasta)
{
    /* View more about `struct dirent` or `man 3 readdir`:
     * https://www.man7.org/linux/man-pages/man3/readdir.3.html
     *
     * View more about `struct stat` on section `The stat structure` or `man 2 stat`:
     * https://www.man7.org/linux/man-pages/man2/stat.2.html
     */
    if (NULL == pasta)
        pasta = ".";

    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(pasta)) == NULL)
    {
        fprintf(stderr, "Impossivel abrir %s\n", pasta);
        return;
    }

    while ((dirp = readdir(dp)) != NULL)
        // Nome, inode, tamanho dos ficheiro, última modificação do ficheiro
        printf("%20s\t%10li\t%5d\t%s", dirp->d_name, dirp->d_ino, dirp->d_reclen, getLastModified(pasta, dirp->d_name));

    closedir(dp);
}

void showType(char *filename)
{
    /* View more about `struct stat` on section `The stat structure` or `man 2 stat`:
     * https://www.man7.org/linux/man-pages/man2/stat.2.html
     */
    struct stat st;
    if (stat(filename, &st) == -1)
    {
        perror("Erro ao obter as permissões");
        return;
    }

    if (S_ISREG(st.st_mode))
        printf("%s é um ficheiro regular\n", filename);
    else if (S_ISDIR(st.st_mode))
        printf("%s é um diretório\n", filename);
    else if (S_ISCHR(st.st_mode))
        printf("%s é um ficheiro de caracteres\n", filename);
    else if (S_ISBLK(st.st_mode))
        printf("%s é um ficheiro de blocos\n", filename);
    else if (S_ISFIFO(st.st_mode))
        printf("%s é um FIFO\n", filename);
    else if (S_ISLNK(st.st_mode))
        printf("%s é um link simbólico\n", filename);
    else if (S_ISSOCK(st.st_mode))
        printf("%s é um socket\n", filename);
    else
        printf("%s é um tipo de ficheiro desconhecido\n", filename);
    return;
}
