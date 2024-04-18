#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct
{
    char name[40];
    char lastname[40];
    int class;
    int media;
} Studente;
void *stampaStudente(void *par)
{
    //Studente *s2 = (Studente *)par; // converte il void in studente puntatore
    Studente s2= *(Studente*)par;
    printf("\n%s\n%s\n%d\n%d\n", s2.name,s2.lastname,s2.media,s2.class);
    pthread_exit(NULL);
}
void *salvaStudente(void *par)
{
    FILE *file = fopen("studente.txt", "w");
    Studente *s3 = (Studente *)par;
    // fwrite(&s3, sizeof(s3), 1, file);//scrive nel file la struct studente
    fprintf(file, "%s\n%s\n%d\n%d", s3->name, s3->lastname, s3->class, s3->media);
    fclose(file); // chiude il file
    printf("Scrittura fatta\n");
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    Studente s1;
    pthread_t threadA, threadB;
    strcpy(s1.name, argv[1]);
    strcpy(s1.lastname, argv[2]);
    s1.media = atoi(argv[3]);
    s1.class = atoi(argv[4]);
    void *sPuntore = &s1;                                      // converto la strct studente in void puntatore
    //pthread_create(&threadA, NULL, &stampaStudente, sPuntore); // crea threadA viene assegnato la stampa dei dati dello stundete
     pthread_create(&threadA, NULL, &stampaStudente, s1); 
    pthread_create(&threadB, NULL, &salvaStudente, sPuntore);  // crea threadB salva la struct dello studente salva i dati
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    return 0;
}
