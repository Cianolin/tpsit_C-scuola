#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define DIM 1000
#define BUFFER 250
int *nTronvare;


void *NumeriA(void *par)
{
    int *numeriA = (int *)par;
    for (int i = 0; i < 250; i++)
    {
        if (numeriA[i] == nTronvare)
        {
            printf("posizone[%d], numero=%d", i, numeriA[i]);

        }
    }
    pthread_exit(NULL);
}
void *NumeriB(void *par)
{
    int *numeriB = (int *)par;
    for (int i = 0; i < 250; i++)
    {
        if (numeriB[i] == nTronvare)
        {
            printf("posizone[%d], numero=%d", i+250, numeriB[i]);
        }
    }
    pthread_exit(NULL);
}
void *NumeriC(void *par)
{
    int *numeriC = (int *)par;

    for (int i = 0; i < 250; i++)
    {
        if (numeriC[i] == nTronvare)
        {
            printf("posizone[%d], numero=%d", i+500, numeriC[i]);
            
        }
        printf("ciao %d", i);
    }
    pthread_exit(NULL);
}
void *NumeriD(void *par)
{
    int *numeriD = (int *)par;
    for (int i = 0; i < 250; i++)
    {
        if (numeriD[i] == nTronvare)
        {
            printf("posizone[%d], numero=%d", i+750, numeriD[i]);
        }
    }
    pthread_exit(NULL);
}
int main(int argc, char argv[])
{
    int numeri[DIM];
    int num, posizione;
    pthread_t threadA, threadB, threadC, threadD;

    FILE *filedestinazione;
    filedestinazione=fopen("n.txt","w");

    for (int i = 0; i < DIM; i++)
    {
        numeri[i] = rand() % 501;
        fprintf(filedestinazione, "[%d]%d\n",i, numeri[i]);
    }
    fclose(filedestinazione);
    int *numeriA = numeri;
    int *numeriB = numeri + 250;
    int *numeriC = numeri + 500;
    int *numeriD = numeri + 750;
    numeriA= malloc(sizeof (BUFFER));
    printf("Inserisci il numero da trovare\n");
    scanf("%d",nTronvare);
    pthread_create(&threadA, NULL, &NumeriA, numeriA);
    pthread_create(&threadB, NULL, &NumeriB, numeriB);
    pthread_create(&threadC, NULL, &NumeriB, numeriC);
    pthread_create(&threadD, NULL, &NumeriD, numeriD);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
    pthread_join(threadD, NULL);
    return 1;
}