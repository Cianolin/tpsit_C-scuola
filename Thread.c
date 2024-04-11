#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>



//POSIX 
void* stampaBuongionrno(void* par)
{
    printf("Buongiorno\n");
    return NULL;
}
void* stampaBuongsera(void* par)
{
    printf("Buonasera\n");
    return NULL;
}
void* stampaBuonanotte(void* par)
{
    printf("Buonanotte\n");
    return NULL;
}
int main()
{
    pthread_t threadA, threadB, threadC;
    printf("Ciao\n");
    pthread_create(&threadA, NULL, &stampaBuongionrno, NULL);
    pthread_create(&threadB, NULL, &stampaBuongsera, NULL);
    pthread_create(&threadC, NULL, &stampaBuonanotte, NULL);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);


    return 0;
}