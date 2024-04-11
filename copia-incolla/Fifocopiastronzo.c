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
    FILE *origine;
    unsigned char buffer[DIM];
    int fd;

    if (argc != 2)
    {
        printf("errore argomenti");
        exit(-1);
    }
    origine = fopen(argv[1], "r"); // r define read file
    //origine = fopen("ciao.txt", "r");
    if (origine == NULL)
    {
        printf("Errore apertura file");
        exit(-1);
    }
    if (mkfifo("fifo1", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Errore fifp");
        }
    }
    fd = open("fifo1", O_WRONLY);
    while (!feof(origine))
    {
        fread(buffer, 1, DIM, origine);
        write(fd, buffer, sizeof(buffer));
    }
    close(fd);
    fclose(origine);
    printf("scrittura finita");
    return 0;
}