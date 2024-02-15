#include <stdio.h>
#include <unistd.h>

int global1= 130;
int global2;
int main(){
    int a;
    while(1){
        printf("%d\n", getpid());
        printf("%p\n",&a);
        sleep(1);
    }
    return 0;
}