#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
void *PrimaMeta(void *par)
{
  int *firstHalf = (int *)par;
  for (int i = 0; i < 5; i++)
  {
    if(firstHalf[i]==8){
      printf("posizione %d\n", i);
    }
  }
}
void *SecondaMeta(void *par)
{
  int *secondHalf = (int *)par;
  for (int i = 0; i < 5; i++)
  {
    if(secondHalf[i]==8){
      printf("posizione %d\n", i+5);
    }
  }
}
int main()
{
  pthread_t threadA, threadB;
  int array[10] = {8, 2, 3, 4, 5, 6, 7, 8, 9, 8};
  int *firstHalf = array;
  int *secondHalf = array + 5;
  pthread_create(&threadA, NULL, &PrimaMeta, (void *)firstHalf);
  pthread_create(&threadB, NULL, &SecondaMeta, (void *)secondHalf);
  pthread_join(threadB, NULL);
  pthread_join(threadA, NULL);
  return 0;
}
