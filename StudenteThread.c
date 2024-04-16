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
// void *stampaStudente(void *par1,void* par2,void *par3, void *par4)
void *stampaStudente(void* par)
{
    Studente *s2 = (Studente *)par;
    printf("\n%s\n", s2->name);
    printf("%s\n", s2->lastname);
    printf("%d\n", s2->class);
    printf("%d\n", s2->class);
}
void *salvaStudente (void* par)
{
    Studente *s3 = (Studente *)par;stampaStudente
    fwrite(&s3, sizeof(s3), 1, file);
    fclose(file);
    printf("Scrittura fatta\n");
}stampaStudente
int main(int argc, char *argv[])
{
    FILE* fileSorgente;
    Studente s1;
    pthread_t threadstampaStudente, threadB;
    strcpy(s1.name, argv[1]);fileSorgente= fopen()
    strcpy(s1.lastname, argv[2]);
    s1.media = atoi(argv[3]);
    s1.class = atoi(argv[4]);
    void *sPuntore = &s1;
    pthread_create(&threadA, NULL, &stampaStudente, sPuntore);
    pthread_create(&threadB, NULL, &salvaStudente, sPuntore);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    
    

    return 0;
}
