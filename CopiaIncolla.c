#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#define Dim 1024
unsigned char Buffer;
bool eof = false;
void *Leggi(FILE *origine)
{
    pthread_exit(NULL);
}
void *Scrivi(FILE *destinazione)
{
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    FILE *ogine, *destinazione;
    pthread_t threadA, threadB;
    if (argc != 3)
    {
        printf("Errore numeri parametri");
        return 1;
    }
    ogine = fopen(argv[1], "rb");
    destinazione = fopen(argv[2], "wb");
}