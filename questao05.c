/*
Crie um programa em C que apresente duas funções para threads (produtor econsumidor), 
nesse devem ser criadas a quantidade de threads definidas por umavariável global QTD eutilizar 
outra variável global chamada “valor”. O produtor sópode produzir um número se essa variável 
tiver sido consumida (valor=0), quando elefor produzir é atribuído um número aleatório avariável 
“valor”.O consumido só podeconsumir um número, se elejá tiver sido produzido (valor≠0),quando ele 
consome éatribuído valor=0. O programa deve seguir as seguintes especificações:

- A função produtor e consumidor devem receber o id da thread como parâmetro nomomento de sua criação.
- O produtor deve produzir um número aleatório menor que 100 e armazenar navariável“valor”.Após produzir 
esse número deve apresentar a mensagem "produtor%d: produziu %d", onde o primeiro campo é o id da thread 
e o segundo é o valor aleatório que foi obtido.
- Essa mensagem e o processo de obtenção do valor devem estar dentro do loop doprodutor, logo a verificação 
da variável "valor" deve ser dentro do loop. Utilize umvalor alto para o número de iterações nesse laço de repetição.
- Ao sair do loop, seja do produtor ou consumido, finalize a thread.
- O consumidor deve apresentar a mensagem "consumidor %d: consumiu %d", ondeo primeiro campo é o numero do processo e 
o segundo é o valor da variávelcompartilhada "valor", que foi produzido aleatoriamente pelo processo produtor.
- Essa mensagem deve está dentro do loop do consumidor, logo a verificação davariável "valor" deve ser dentro do loop.
-  Caso a variável "valor" seja diferente de zero, então ele apresenta essa mensagem, edeve alterar o valor da variável 
"valor" para zero (valor=0).
- Crie 4 pares de threads com esses processos (4 threads para consumidores e 4 threadspara produtores).
- Execute os threads algumas vezes, observe as saídas e responda as observações:
*/

//Includes de Bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Diretivas*/
#define QTD 4
#define CONT 100000
int valor = 0;

void *produtor(void *ard){ //recebe o id da thread produtor como parâmetro 
    int *id = (int *) ard; //Cast do valor recebido para inteiro
    int cont = 0;

    while(cont < CONT){ //processo de obtenção do valor deve estar dentro do loop do produtor
        if(valor == 0){ //O produtor só pode produzir um número se essa variável tiver sido consumida (valor=0)
            valor = ( rand() % 100 ); //Valor recebe um numero onde: 0 < valor < 100
            printf("Produtor %d produziu %d\n", *id, valor); //Após produzir esse número deve apresentar a mensagem
        }
        cont++;
    }
}

void *consumidor(void *ard){ //recebe o id da thread consumidor como parâmetro
    int *id = (int *) ard; //Cast do valor recebido para inteiro

    int cont = 0; 

    while(cont < CONT){ //processo de obtenção do valor deve estar dentro do loop do produtor
        if(valor != 0){ //Caso a variável "valor" seja diferente de zero, então apresenta a mensagem
            printf("Consumidor %d consumiu %d\n", *id, valor);
            valor = 0; //alterar o valor da variável "valor" para zero 
        }
        cont++;
    }
}

int main(int argc, char* argv[]){
    /*Definindo os vetores de threads*/
    pthread_t pro[QTD]; //4 threads para produtores
    pthread_t con[QTD]; //4 threads para consumidores

    int id; //id das threads

    for(id = 0; id < QTD; id++){
        // criando 4 threads e passando id como parametro para a função produtor
        pthread_create(&pro[id], NULL, produtor, &id); 
    }

    for(id = 0; id < QTD; id++){
        // criando 4 threads e passando id como parametro para a função consumidor
        pthread_create(&con[id], NULL, consumidor, &id); 
    }

    //Laço para aguardas as threads executarem
    for(int i=0; i<QTD; i++){
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }

    printf("\nFIM\n"); /*Para saber o FIM do main*/

    return 0;
}

/*---------------------------------------------- Respostas ----------------------------------------------*/

//Por que alguns consumidores consumiram mais de uma vez em seguida o mesmo número?
    /*===Como não há um controle de processos em execução e controle de acesso a região crítica, 
        o escalonador troca de processos ocasionando incosistência nos valores va variável valor.===*/

//Por que o consumidor consumiu um determinado número, mas o produtor só oproduziu depois?
    /*===Novamente o problema da região crítica. O produtor recebeu o escalonador, produziu e pôs
        o valor na variável de região crítica. Antes dele encerrar seu processo ele perde o escalonador
        que é ganho pelo consumidor. Ele consome o valor da variável e monstra em tela. Depois o
        escalonador volta para o produtor que mostra o valor em tela e so repois encerra seu processo ===*/

//Tirando o fato de ser gerado números aleatórios, por que a execução sempre ocorre em ordem diferente?
    /*=== Não há um controle de flxo entre os processos. Uma solução para esse problema é a ultilização
        de semáfaros, para ter um controle da ordem de execução dos processos. ===*/
