#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>//serve per aprire la Fifo

int main(){
    int fd;
    int x;
    //creazione fifo
    if(mkfifo("myfifo1",0777)==-1)
    {
        printf("Errore nella creazione della FIFO");
        return 1;
    }
    fd=open("myfifo1", 0_WRONLY);
    printf("\nHo aperto la fifo");

    x=90;

    if(write(fd,&x,sizeof(x)==-1)){//fd=1 significa che la fifo è aperto in scrittura
        printf("errore in scrittura nella fifo");
        return 2;
    }
    close(fd);
    return 0;
}//SHA256:vQMVrIBotwR2xuGbJFyT+JNXaUsqM0oRG4G445aepZs luciano.lin@iisviolamarchesini.edu.it