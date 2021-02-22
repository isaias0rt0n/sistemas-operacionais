#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int id;

    id = fork();
    if(id != 0){
        printf("Eu sou o PAI e espero o FILHO %d\n", id);
        wait(0);
        printf("O filho acabou\n");
        printf("Continua PAI\n");
        for(int cont=(argc/2)+1; cont < argc; cont++){
            printf("%s -> ", argv[cont]);
        }
        
        printf("FIM\nO Pai acabou\n");
    }else{
        printf("Sou FILHO %d\n", getpid());
        //sleep(2);

        for(int cont2=1; cont2<=(argc/2); cont2++){
            printf("%s -> ", argv[cont2]);
        }

        printf("FIM FILHO\nTerminei, agora vou embora...\n");
    }

    return 0;
}