#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#define Dim 2
int main(int argc, char *argv[])
{
    typedef struct
    {
        char nome[40];
        float num;
        

    } Stronz;
    int fd[2], p;
    int status;
    if (pipe(fd) < 0)
    {
        printf("errore nella pipe");
    }
    p = fork();
    if (p < 0)
    {
        printf("errore fork");
    }
    if (p > 0)
    {
        Stronz stronzi[Dim];
        close(fd[0]);
        for (int i = 0; i < Dim; i++)
        {
            printf("nome\n");
            scanf("%s\n", stronzi[i].nome);
            printf("numero\n");
            scanf("%f\n", &stronzi[i].num);
            printf("fine\n");
        }
        write(fd[1], stronzi, sizeof(stronzi));
        close(fd[1]);
        wait(&status);
    }
    else
    {
        Stronz stronz[Dim];
        close(fd[1]);
        read(fd[0], stronz, sizeof(stronz));
        for (int i = 0; i < Dim; i++)
        {
            printf("nome: %s\n", stronz[i].nome);
            printf("numero: %f\n", stronz[i].num);
        }
        close(fd[0]);
        
    }
    return 0;
}