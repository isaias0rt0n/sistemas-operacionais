/*Simulador de Escalonamento de Processos*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

/*Estrutura do processo*/
struct processos {
    char id; //identifica processo
    int duracao; //tempo de duração do processo
    int ordem; //Prioridade do processo
    struct processos* prox;
};

typedef struct processos Processos; //

//Funçãp de criação: retorna processo vazio
Processos* proc_cria(void){
    return NULL;
}

/*Função para liberar o processo*/
void proc_libera(Processos* proc){
    Processos* p = proc; //auxiliar para percorrer a lista de procesos
    while(p != NULL){
        Processos* tmp = p->prox;
        free(p);
        p = tmp;
    }
}

/*Função para imprimir os processo da lista*/
void proc_imprime(Processos* proc){
    Processos* tmp;
    printf("Ordem dos processos por prioridade:\n");
    for(tmp = proc; tmp != NULL; tmp=tmp->prox){
        printf("%c -> ", tmp->id);
    }
    printf("FIM\n\n");
}

/*Insere um novo processo na ordem crescente(prioridade)*/
Processos* proc_insere(Processos* proc, int id, int duracao, int ordem){
    Processos* ant = NULL;  //Aponta para o processo anterior
    Processos* aux = proc;  //aux para percorrer os processos

    //Procura a ordem certa de chegada
    while(aux != NULL && aux->ordem < ordem){ //Enquanto não achar avança na lista de processos
        ant = aux;
        aux = aux->prox;
    }

    /*Cria o novo processo*/
    Processos* novo = (Processos*) malloc(sizeof(Processos));

    if (novo == NULL){
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->id = id; //Atribui os valores
    novo->duracao = duracao;
    novo->ordem = ordem;

    if(ant == NULL){
        novo->prox = proc; //Insere no inicio
        proc = novo;
    }else{ //Insere na ordem apropriada
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return proc;
};

/*Insere um processo numa lista de maneira ordenada pelo tempo(mesma lógica da função acima)*/
Processos* insere_menor_tempo(Processos *proc, int id, int duracao, int ordem){
    Processos* ant = NULL;
    Processos* aux = proc;

    while(aux != NULL && aux->duracao < duracao){
        ant = aux;
        aux = aux->prox;
    }
    Processos* novo = (Processos*) malloc(sizeof(Processos));
    if (novo == NULL){printf("Erro ao alocar memória.\n"); exit(1);}
    novo->id = id;
    novo->duracao = duracao;
    novo->ordem = ordem;

    if(ant == NULL){
        novo->prox = proc; //Insere no inicio
        proc = novo;
    }else{ //Insere na ordem apropriada
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return proc;
}


/*Função para transformar uma lista em lista circular*/
Processos* insere_circular(Processos* proc){
    Processos *ini = proc;
    Processos *atual = proc;

    while(atual->prox != NULL){
        atual = atual->prox;
    }
    atual->prox = ini; //Aponta para o inicio(circular)
    return ini;
}

 /*Função que simula o SJF*/
void sfj(Processos* proc){
    Processos *aux=proc; //Variável aux que recebe o ponteiro para lista de processos
    Processos *menor_job, *tmp;
    menor_job = proc_cria(); //Cria uma lista de processos vazia

    while(aux != NULL){ //Vai inserir os processos na lista criada de maneira ordenada pelo tempo(menor->maior)
        menor_job = insere_menor_tempo(menor_job, aux->id, aux->duracao, aux->ordem);
        aux=aux->prox;
    }
    printf("INICIO SJF\n");
    for(tmp = menor_job; tmp != NULL; tmp=tmp->prox){ //Percorre a lista de processos
        printf("Processo %c executando...(%ds)\n", tmp->id, tmp->duracao);//Printa qual processo está no "escalonador"
        Sleep((tmp->duracao)*1000); //Temporizador
    }
    proc_libera(menor_job); //Libera a memoria com a lista de processos ordenados por tempo
    printf("FIM SJF\n");
}

/*Função que simula o Round Robin*/
void round_robin(Processos* proc, int quantum){
    Processos *aux = insere_circular(proc); //Cria uma lista de processo auxiliar que é circular
    int contem_proc;

    while(aux != NULL){ //Percorre a lista circular de processo: Fica em Loop. :(
        if(aux->duracao <= quantum && aux->duracao != 0){ //Verifica se o processo é menor que o quantum e o processo ainda precisa ser executado(!=0)
            printf("id: %c executando...(%ds)\n",aux->id,aux->duracao); //Mostra que está executando um determinado processo
            Sleep((aux->duracao)*1000); //Simula o time-slice
            aux->duracao = 0; //Como o quantum é maior, executa o tempo do processo e atribui a ele 0 para não ser executado novamente
        }else if(aux->duracao > quantum){ //Caso quantum seja maior, é onde ficará a parte mais interessante para o "escalonador"
            printf("id: %c executando...(%ds)\n",aux->id,aux->duracao); //Mostra qual processo está executando e seu tempo
            Sleep((quantum)*1000); //Simula o time-slice -> Executa o a parcela de tempo equivalente ao quantum
            aux->duracao = aux->duracao - quantum; //Diminuimos do tempo do processo o seu tempo executado
        }
        /*else{ //Tentativa de sair, como é uma lista circular a função fica em loop.
            exit(1); // Parte comentada por que estava apresentando erros. Logo a função fica em loop. Foi mal :(
        }*/
        aux = aux->prox; //Avança para o próximo processo
    }
}

/*Programa Principal*/
int main(int arg, char* argv[]){
    setlocale(LC_ALL, "Portuguese");

    /*Inicialização de variáveis*/
    Processos* proc;
    char id;
    int num, op, quantum, ordem, duracao;

    proc = proc_cria(); //Cria uma lista de processos vazia

    /*proc = proc_insere(proc,'A',3,1);
    proc = proc_insere(proc,'B',5,8);
    proc = proc_insere(proc,'C',3,7);
    proc = proc_insere(proc,'D',2,5);*/

    printf("Quantos processos estao na fila: ");
    scanf("%d",&num);printf("\n"); //quantos processos estão na fila(lista no nosso caso ;))

    for(int i = 1; i <= num; i++){ //Laço para ler os valores
        printf("Digite um identificador para o %dº processo(char): ", i);
        scanf(" %c",&id);//ERROR no codeblocks -> não executa o scanf
        printf("Digite a ordem de chegada do processo(int): ");
        scanf("%d",&ordem);
        printf("Digite o tempo de execucao do processo(int): ");
        scanf("%d",&duracao);

        proc = proc_insere(proc, id, duracao, ordem); //Vai inserindo os processo na lista de processos
        printf("\n");
    }

    /*Menu para ultilização*/
    printf("[1] - SFJ\n");
    printf("[2] - Round Robin\n");
    printf("Qual algoritmo de escalonamento deseja: "); scanf("%d",&op);

    if(op == 1){
        proc_imprime(proc);
        sfj(proc);
    }else if(op == 2){
        printf("quantum: "); scanf("%d",&quantum);
        round_robin(proc, quantum);
    }else{
        printf("Opção inválida"); exit(1);
    }
    proc_libera(proc);

    printf("\n");
    return 0;
}
