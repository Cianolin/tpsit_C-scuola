#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define DIM_ARRAY 2

typedef struct
{
    char titolo[100];
    char autore[100];
    double prezzo;
}libro;

int main(int argc, char argv[]){
    //libro libro1[DIM_ARRAY];
    int p, status;
    int fd[2];

    if(pipe(fd)==-1){
        printf("errore nella creazione della pipe");
        exit(-1);
    }
    p=fork();
    if(p<0){
        printf("errore nella generazione del figlio");
        exit(-1);
    }
    if(p>0)//padre
    {
        libro libro1[DIM_ARRAY];
        strcpy(libro1[0].titolo,"Valevo nascere vento");
        strcpy(libro1[0].autore,"Andrea Gentile");
        libro1[0].prezzo=9.50;
        strcpy(libro1[1].titolo,"Il segreto del Bosco Vecchio");
        strcpy(libro1[1].autore,"Dino Buzzati");
        libro1[1].prezzo=10;
        close(fd[0]);
        for(int i=0;i<DIM_ARRAY;i++){
            write(fd[1],libro1[i].titolo,sizeof(libro1[i].titolo));
            write(fd[1],libro1[i].autore,sizeof(libro1[i].autore));
            write(fd[1],&libro1[i].prezzo,sizeof(libro1[i].prezzo));
        }
        close(fd[1]);
        wait(&status);
    }
    else//figlio
    {
        libro libro2[DIM_ARRAY];
        close(fd[1]);
        for(int i=0;i<DIM_ARRAY;i++){
          read(fd[0],libro2[i].titolo,sizeof(libro2[i].titolo));
            read(fd[0],libro2[i].autore,sizeof(libro2[i].autore));
            read(fd[0],&libro2[i].prezzo,sizeof(libro2[i].prezzo));
        }
        close(fd[0]);
        for(int i;i<DIM_ARRAY;i++){
            printf("\nTitolo: %s\n",libro2[i].titolo);
            printf("\nAutore: %s\n",libro2[i].autore);
            printf("\nPrezzo: %.2lf\n",libro2[i].prezzo);
        }
    }
    return 0;
}