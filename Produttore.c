#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#define DIM_ARRAY 5
//Produttorore
int main(int argc, char *argv[])
{
    int fd;
    if(mkfifo("myfifo1",0777)==-1){
        if(errno!=EEXIST){
            printf("\nErrore nella creazione della fifo");
            return 1;
        }
    }
    srand(time(NULL));
    int numeri[DIM_ARRAY];
    for (int i = 0; i < DIM_ARRAY; i++)
    {
        numeri[i] = rand() % 100;
    }
    fd = open("myfifo1", O_WRONLY);
    write(fd, numeri, sizeof(numeri));
    close(fd);
    return 0;
}