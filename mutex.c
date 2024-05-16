#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SLICE_DIM 64
#define NUM_SLICES 16

typedef struct
{
    unsigned char bufferInStruct[SLICE_DIM];
    int n;
} bufferStruct;
bufferStruct buffer[NUM_SLICES];
int read_index, write_index, n_slices;
pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;

void *writeFile(void *arg)
{
    pthread_mutex_lock(&mutex);
    if (n_slices > 0)
    {
        fwrite(buffer[read_index].bufferInStruct, 1, buffer[read_index].n, (FILE *)arg);
        read_index = (read_index + 1) % NUM_SLICES;
        n_slices--;
    }
    else
    {
        pthread_cond_wait(&not_empty,&mutex);
    }
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);
}
void *readFile(void *arg)
{
    int n;
    pthread_mutex_lock(&mutex);
    if (n_slices >= NUM_SLICES)
        pthread_cond_wait(&not_full, &mutex);
    n = fread(buffer[write_index].bufferInStruct, 1, SLICE_DIM, (FILE *)arg);
    if (n > 0)
    {
        buffer[write_index].n = n;
        read_index = (write_index + 1) % NUM_SLICES;
        n_slices++;
        pthread_cond_signal(&not_empty);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t threadRead, threadWrite;
    FILE *fr, *fw;
    fr = fopen("origine", "rb");
    fw = fopen("destinazione", "wb");
    pthread_create(&threadWrite, NULL, &writeFile, fw);
    pthread_create(&threadRead, NULL, &readFile, fr);
}