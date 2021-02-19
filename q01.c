/*
Faça um programa que leia um número “n” informado pelo usuário e diga
quantos números primos há entre 0 e “n”. Esse seu programa deve rodar em 2 threads,
de forma que o esforço computacional seja uniformemente dividido entre os threads
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int total_primos = 0;

int retorna_primo(int n){
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

void *calcula_primo1(void *ard){
    int *n = (int *) ard;

    int cont=2, quantidade_primos=0;

    while (cont <= (*n/2)){        
        if(retorna_primo(cont) != 0)
            quantidade_primos++;
        cont++;
    }

    //printf("Total1: %d\n", quantidade_primos);
    total_primos += quantidade_primos;
}

void *calcula_primo2(void *ard){
    int *n = (int *) ard;

    int cont = (*n/2)+1, quantidade_primos=0;

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
    pthread_t thread1, thread2;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    pthread_create(&thread1, NULL, calcula_primo1, &n);
    pthread_create(&thread2, NULL, calcula_primo2, &n);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Total de primos = %d\n", total_primos);

    return 0;
}