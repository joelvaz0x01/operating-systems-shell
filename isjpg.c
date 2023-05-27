#include "shell.h"

/**
 * Retorna se o ficheiro é jpg
 * @param filename - Nome do ficheiro
 * @return - 1 se for jpg, 0 se não for
 */
int isjpg(int fileDescriptor)
{
    unsigned char b[4];
    int n = read(fileDescriptor, b, 4);
    if (n)
    {
        lseek(fileDescriptor, 0, SEEK_SET);
        if (b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && b[3] == 0xe0)
            return 1;
    }
    return 0;
}
