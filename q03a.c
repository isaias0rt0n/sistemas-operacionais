/*
Crie um programa em C que demonstre uma hierarquia de processos com o comando fork( ) -> Pai -> Filho ->Filho1.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
main(int argc, char *argv[]){
    int pid;
    int i;
    pid = fork();
    if (pid < 0) {
        printf("Fork error\n");
        exit(1);
    }else{
        if (pid == 0) {
            int pid2;
            //Filho gera Filho1
            pid2 = fork();
            if (pid2 < 0) {
                printf("Fork error\n");
                return(1);
            }else{
                if (pid2 == 0) {
                    //sleep(1);
                    write(1, "-> Filho1 ", 10);
                    return(0);
                }else{
                    write(1, "-> Filho ", 9);
                    wait(NULL);
                    return(0);
                }
            }
        }else {
            write(1, "Pai ", 4);
            wait(NULL);
            return(0);
        }
    }
}
