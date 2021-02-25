/*
Faça um programa em C que lê um valor para x e calcule o valor de Sen(x) 
utilizando duas threads para dividir os cálculos, uma para os termos com soma 
e outra para os com subtração. O valor deve ser calculado até ser próximo do seno.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define N 9

double termo_soma = 0, termo_subtracao = 0;

// Calculo do fatorial de maneira recursiva
unsigned long long int fatorial(int valor){
    unsigned long long int fat; 
    if (valor == 0 || valor == 1){
        return 1;
    }else{
        fat = valor * fatorial(valor - 1);
        return fat;
    }
}

void *soma_taylor(void *ard){
    int *x = (int *) ard;

    int cont = 0; double termos, numerador;
    unsigned long long int denominador;

    while (cont < N){
        numerador = pow( -1, cont ) * pow( (*x), (2*cont+1) );
        denominador = fatorial( 2*cont + 1 );
        termos = numerador/denominador;

        termo_soma += termos;

        cont += 2;
    }
    //printf("%f\n", termo_soma);
}

void *subtracao_taylor(void *ard){
    int *x = (int *) ard;

    int cont = 1; double termos, numerador;
    unsigned long long int denominador;

    while (cont < N){
        numerador = pow( -1, cont ) * pow( (*x), (2*cont+1) );
        denominador = fatorial( 2*cont + 1 );
        termos = numerador/denominador;

        termo_subtracao += termos;

        cont += 2;
    }
    //printf("%f\n", termo_subtracao);
    
}

int main(int argc, char argv[]){
    int x;
    pthread_t thread1, thread2;

    printf("Digite um valor para x: ");
    scanf("%d", &x);

    pthread_create(&thread1, NULL, soma_taylor, &x);
    pthread_create(&thread2, NULL, subtracao_taylor, &x);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("%f\n", (termo_subtracao + termo_soma));
    
    return 0;
}

//printf("%llu\n", fatorial(valor));