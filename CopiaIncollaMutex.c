
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define DIM 64
#define N 16

struct BUFFER
{
  unsigned char buffer[DIM];
  int n;
};

struct BUFFER ring_buffer[N];
// sono indici
int read_index = 0, write_index = 0, N_block = 0;

bool end = false;
pthread_mutex_t critical, mutex;
pthread_cond_t not_full, not_empty;
FILE *origine, *destinazione;

void *leggi(void *par)
{
  int n;

  while (!feof(origine))
  {
    pthread_mutex_lock(&critical);
    // sospensione nel caso ring sia pieno
    if (N_block >= N)
      pthread_cond_wait(&not_full, &critical);
    // lettura di un blocco dati dal file nel ring
    n = fread(ring_buffer[write_index].buffer, 1, DIM, origine);
    if (n > 0)//in caso di lettura
    {
      // aggiornamento numero di byte del blocco
      ring_buffer[write_index].n = n;
      // incremento indice di scrittura blocchi dati
      write_index = (write_index + 1) % N;
      //blocca il mutex
      //che sospende l'altro thread che l'ha invocato
      //così che altri thread non possano aquisirlo
      pthread_mutex_lock(&mutex);
      //incrementa il contatore
      N_block++;
      //sblocca il mutex
      //così che altri thread possano aquisirlo
      pthread_mutex_unlock(&mutex);
      // notifica consumatore del ring non vuoto
      pthread_cond_signal(&not_empty);
    }
    //sblocca la sezione critica
    pthread_mutex_unlock(&critical);
  }
  end = true;
  // notifica al consumatore che il ring non è vuoto
  pthread_cond_signal(&not_empty);
  pthread_exit(NULL);
}

void *scrivi(void *par)
{
  while (1)
  {
    if (end && N_block == 0)
      break;
    pthread_mutex_lock(&critical);
    if (N_block > 0)
    {
      // scrittura su file di un blocco dati del ring-buffer
      fwrite(ring_buffer[read_index].buffer, 1, ring_buffer[read_index].n, destinazione);
      // incremento indice di lettura blocchi ring
      read_index = (read_index + 1) % N;
      //blocca il mutex
      
      pthread_mutex_lock(&mutex);
      // decremento contatore numero di blocchi ring
      N_block--;
      //sblocca il mutex
      pthread_mutex_unlock(&mutex);
      // notifica che il ring non pieno al produttore
      pthread_cond_signal(&not_full);
    }
    else
    {
      // sospensione se il ring è vuoto
      pthread_cond_wait(&not_empty, &critical);
    }
    //sblocca la sezione critica
    pthread_mutex_unlock(&critical);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t thread_scrittura, thread_lettura;

  if (argc != 3)
  {
    printf("Uso: %s file-origine file-destinazione\r\n", argv[0]);
    return 0;
  }
  //file lettura
  origine = fopen(argv[1], "rb");
  if (origine == NULL)
  {
    printf("Errore apertura file %s\r\n", argv[1]);
    return 0;
  }
  //file destinazione
  destinazione = fopen(argv[2], "wb");
  if (destinazione == NULL)
  {
    printf("Errore apertura file %s\r\n", argv[2]);
    fclose(origine);
    return -1;
  }
  // creazione mutex e variabili di condizione
  pthread_mutex_init(&critical, NULL);
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&not_full, NULL);
  pthread_cond_init(&not_empty, NULL);
  // creazione thread dei lettura e scrittura
  pthread_create(&thread_lettura, NULL, &leggi, NULL);
  pthread_create(&thread_scrittura, NULL, &scrivi, NULL);
  // attesa termine thread
  pthread_join(thread_lettura, NULL);
  pthread_join(thread_scrittura, NULL);
  // distruzione mutex e variabili di condizione
  pthread_mutex_destroy(&critical);
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&not_full);
  pthread_cond_destroy(&not_empty);
  // chiusura file
  fclose(origine);
  fclose(destinazione);
  return 1;
}
