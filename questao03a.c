/*
Crie um programa em C que demonstre uma hierarquia de processos com o comando fork( ) -> Pai -> Filho ->Filho1.
*/

/*Bibliotecas necessárias*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
    int pid; //Inicializa variáveis
    int i;
    pid = fork(); //Cria um processo Filho
    if (pid < 0) { //Verifica se ocorreu tudo certo com a criação
        printf("Vishh! Deu ruim\n");
        exit(1);
    }else{
        if (pid == 0) { //código filho
            int pid2;
            pid2 = fork(); //Filho gera Filho1
            if (pid2 < 0) {
                printf("Vishh! Deu ruim\n");
                return(1);
            }else{
                if (pid2 == 0) {
                    write(1, "-> Filho1", 10); //Mostra na tela. write(int fildes, const void *buf, size_t nbyte);
                    return(0);
                }else{
                    write(1, "-> Filho ", 9); //Escreve em tela
                    wait(NULL); //Filho espera Filho1
                    return(0);
                }
            }
        }else{
            write(1, "Pai ", 4); //Escreve em tela 4 caracteres
            wait(NULL); //Pai espera Filho
            printf(" -> FIM\n");
            return(0);
        }
    }
    
}
