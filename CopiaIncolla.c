#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#define Dim 1024
unsigned char Buffer[Dim];
int n=0;
bool eof = false;
void *Leggi(FILE *origine)
{
    while (!feof(origine))
    {
        n=fread(Buffer, 1, Dim,origine);
    }
    eof=true;
    pthread_exit(NULL);
}
void *Scrivi(FILE *destinazione)
{
    while (!eof)
    {
        if(n>0){
            fwrite(Buffer,1,n,destinazione);
        }
    }
    
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    FILE *origine, *destinazione;
    pthread_t threadA, threadB;
    if (argc != 3)
    {
        printf("Errore numeri parametri");
        return 1;
    }
    origine = fopen(argv[1], "rb");
    destinazione = fopen(argv[2], "wb");
    pthread_create(&threadA,NULL, &Leggi, origine);
    pthread_create(&threadB,NULL, &Scrivi, destinazione);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    fclose(origine);
    fclose(destinazione);
}