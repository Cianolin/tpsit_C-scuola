#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#define DIM_ARRAY 5
//Consumatore
int main(int argc, char *argv[])
{
    int fd, somma = 0;
    int numeri[DIM_ARRAY];
    if(mkfifo("myfifo1",0777)==-1){
        if(errno!=EEXIST){
            printf("\nErrore nella creazione della fifo");
            return 1;
        }
    }
    fd = open("myfifo1", O_RDONLY);

    read(fd, numeri, sizeof(numeri));
    for (int i = 0; i < DIM_ARRAY; i++)
    {
        somma += numeri[i];
    }
    printf("Somma dei numeri -> %d\n", somma);
    close(fd);
    return 0;
}