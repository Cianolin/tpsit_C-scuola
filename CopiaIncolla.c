#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#define BUFFER_Dim 1024
#define BUFFER_SIZE 64
typedef struct
{
    unsigned char Buffer[BUFFER_Dim];
    int n;
} Buffer;
Buffer ring_buffer[BUFFER_SIZE];
bool eof = false;
int read_index=0;
int write_index=0;
int N_block=0;
void *Leggi(void *origine)
{
    FILE*file=(FILE*)origine;
    while (!feof(origine))
    {
        while (N_block>= BUFFER_SIZE)
        {
            int n=fread(ring_buffer[write_index].Buffer,1, BUFFER_Dim, file);
            if (n>0)
            {
                ring_buffer[write_index].n=n;
                write_index= (write_index+1)% BUFFER_SIZE;
                N_block++;
            }
            
        }
    }
    eof = true;
    pthread_exit(NULL);
}
void *Scrivi(FILE *destinazione)
{
    FILE*file=(FILE*)destinazione;
    while (!eof || N_block>0)
    {
        if (N_block>0)
        {
            fwrite(ring_buffer[read_index].Buffer, 1, ring_buffer[read_index].n, file);
            read_index=(read_index+1)% BUFFER_SIZE;
            N_block--;
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
    pthread_create(&threadA, NULL, &Leggi, origine);
    pthread_create(&threadB, NULL, &Scrivi, destinazione);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    fclose(origine);
    fclose(destinazione);
}