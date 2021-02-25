/*
Faça um programa que leia um número “n” informado pelo usuário e diga
quantos números primos há entre 0 e “n”. Esse seu programa deve rodar em 2 threads,
de forma que o esforço computacional seja uniformemente dividido entre os threads
*/

/*Bibliotecas necessárias*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int total_primos = 0; //Vai armazenar o numero de primos(nossa região crítica hehehe)

int retorna_primo(int n){ //Verifica se um numero é primo. retorna 1 caso verdade e 0 caso falso.
    int num = n;
    int cont, primo = 1;
    
    for(cont=2; primo && (cont <= sqrt(num)); cont++){
        if( (num % cont) == 0 )
            primo = 0;
    }
    if (primo)
        return 1;
    else
        return 0;
}

void *calcula_primo1(void *ard){ //Primeira função executada
    int *n = (int *) ard; //cast para inteiro

    int cont=2, quantidade_primos=0;

    while (cont <= (*n/2)){ //anda até a metade do valor        
        if(retorna_primo(cont) != 0) //Se for primo incrementa o total de primos
            quantidade_primos++;
        cont++;
    }

    //printf("Total1: %d\n", quantidade_primos);
    total_primos += quantidade_primos; //acrescenta a região crítica o numero de primos existentes até a metade do n
}

void *calcula_primo2(void *ard){ //Segue a mesma lógica da função acima
    int *n = (int *) ard;

    int cont = (*n/2)+1, quantidade_primos=0; //O contador começa da metade superiro do valor passado e vai até o fim de n

    while (cont <= *n){
        if(retorna_primo(cont) != 0)
            quantidade_primos++;
        cont++;
    }

    //printf("Total2: %d\n", quantidade_primos);
    total_primos += quantidade_primos;
}

int main(int argc, char *argv[]){
    int n;
    pthread_t thread1, thread2; // Handle para pthread, isto é, um valor que permite identificar o thread
    printf("Digite um numero inteiro: ");
    scanf("%d", &n); 

    pthread_create(&thread1, NULL, calcula_primo1, &n); // inicializar a thread1 passando endereço de n como parametro para a função
    pthread_create(&thread2, NULL, calcula_primo2, &n);//  inicializar a thread2 passando endereço de n como parametro para a função
    pthread_join(thread1, NULL); //espera a thread1 terminar
    pthread_join(thread2, NULL); //espera a thread2 terminar
    
    printf("Total de primos = %d\n", total_primos); //mostra o total de primos no  intervalo de n

    return 0;
}
