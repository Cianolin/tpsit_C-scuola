/*la consegna è la seguente=in
linguaggio c creare 2 thread, il primo genera una sequenza di N numeri
casuali, con N fornito come argomento della riga di comando, e li
inserisce singolarmente in un ring-buffer, il secondo preleva i numeri
dal ring-buffer condiviso e li visualizza.
la codifica dovrà prevedere la necessaria sincronizzazione fra thread consumatore e thread produttore.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER 8
#define RING_BUFFER 4

int index_write, index_read, N_block = 0;
bool end = false;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full, not_empty;
typedef struct
{
    int n;
} RingNum;
RingNum Num[BUFFER];

void *Genera(void *arg)
{
    for (int i = 0; i < *(int *)arg; i++)
    {
        pthread_mutex_lock(&mutex);
        if (N_block >= RING_BUFFER)
        {
            pthread_cond_wait(&not_full, &mutex);
        }
        Num[index_write].n = (rand() % (500) + (1));
        index_write = (index_write + 1) % RING_BUFFER;
        N_block++;
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
    end = true;
    pthread_exit(NULL);
}
void *Consumatore(void *arg)
{
    while (!end || N_block>0)
    {
        pthread_mutex_lock(&mutex);
        if (N_block > 0)
        {
            printf("%d\n", Num[index_read].n);
            index_read = (index_read+1)% RING_BUFFER;
            N_block--;
            pthread_cond_signal(&not_full);
        }
        else
        {
            pthread_cond_wait(&not_empty, &mutex);
        }
        pthread_mutex_unlock(&mutex);
        
    }
    /*while (1)
    {
        pthread_mutex_lock(&mutex);
        if (N_block == 0)
        {
            pthread_cond_wait(&not_empty, &mutex);
        }
        printf("%d\n", Num[index_read].n);
        index_read = (index_read + 1) % RING_BUFFER;
        N_block--;
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        if (N_block == 0 && end)
        {
            break;
        }
    }*/
    pthread_exit(NULL);
}


int main(int argv, char *argc[])
{
    pthread_t threadA, threadB;
    srand(getpid());
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);
    int n = atoi(argc[1]);
    pthread_create(&threadA, NULL, &Genera, &n);
    pthread_create(&threadB, NULL, &Consumatore, &n);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);
    pthread_mutex_destroy(&mutex);
    return 1;
}