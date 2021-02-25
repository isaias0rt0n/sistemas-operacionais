/* Crie um programa que receba parâmetros na chamada do main e mostre na saída
metade dos parâmetros pelo processo pai e a outra metade pelo processo filho*/

//Bibliotecas necessárias
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int id;

    id = fork(); //Cria processo filho
    if(id != 0){ //Verifica se é o pai
        printf("Eu sou o PAI e espero o FILHO %d\n", id);
        wait(0); //Espera Filho
        printf("O filho acabou\n");
        printf("Continua PAI\n");
        for(int cont=(argc/2)+1; cont < argc; cont++){ //Percorre os argumentos da metade até o fim
            printf("%s -> ", argv[cont]);
        }
        
        printf("FIM\nO Pai acabou\n");
    }else{ //Código do filho
        printf("Sou FILHO %d\n", getpid());
        //sleep(2);

        for(int cont2=1; cont2<=(argc/2); cont2++){ //Percorre do primeiro argumento(sem ser o programa) até a metade
            printf("%s -> ", argv[cont2]);
        }

        printf("FIM FILHO\nTerminei, agora vou embora...\n"); //Para sinalizar fim código do filho
    }

    return 0;
}