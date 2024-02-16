#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
int global1= 130;
int global2;
int main()
{
    int a,numero;
   // int *b;
    int *b = malloc(4096);
    //numero=10;
    //b=(int*)malloc(sizeof(int)*numero);
    while(1){
        printf("%d\n", getpid());
        printf("%p\n",&a);
        printf("%p\n",&b);
        sleep(1);
    }
    //free(b);
    return 0;
}
/*
7ffe20ea4000-7ffe20ec6000
l'inizio 7ffe20ea4000
7ffe20ec6000 fine 
sono dello  stack

7ffd019fd000 
7ffd01a1cc24
7ffd01a1f000
*/