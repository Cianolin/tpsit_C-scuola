#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int p;
    int fd[2];
    if (pipe(fd) == -1)//errore nella crezione della pipe restituisce -1
    {    
        printf("errore creazione pipe\n");
        exit(-1);
    }
    p = fork();
    if (p < 0)
    {      
        printf("errore generazione figlio\n");
    }
    if (p > 0)
    {
        close(fd[0]);
        char c[255];
        FILE*file=fopen("memoryProcess.txt","r");
        if(file==NULL){
            printf("errore nell'apertura del file");
            exit(-1);
        }
        while(fgets(c,sizeof(c),file)!=NULL)
        {
            write(fd[1],c,sizeof(c));
        }
        
        close(fd[1]);
        fclose(file);
        
    }else{
        
        char copiaC[255];
        close(fd[1]);
        FILE*copiaFile=fopen("fileDestinazione.txt","w");
        if(copiaFile==NULL){
            printf("Errore di creazione copia");
            exit(-1);
        }
        while(read(fd[0],copiaC,sizeof(copiaC))>0){
            fprintf(copiaFile,copiaC);
        }
        fclose(copiaFile);
        close(fd[0]);
    }
    return 0;
}