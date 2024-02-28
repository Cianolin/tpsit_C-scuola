#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#define DIM 2048

int main(int argc, char *argv[])
{
    int fd, n;
    FILE *destinazione;
    unsigned char buffer[DIM];

    destinazione = fopen("destinazione.txt", "w");
    if (destinazione == NULL)
    {
        printf("errore file");
        exit(-1);
    }
    fd = open("fifo1", O_RDONLY);
    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        fwrite(buffer, 1, sizeof(buffer), destinazione);
    }
}