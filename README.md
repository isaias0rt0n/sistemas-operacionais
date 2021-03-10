<h1 align="center">Sistemas Operacionais</h1>

## :label: About
Trabalho realizado na disciplina de sistemas Operacionais, visando abordar conceitos como:
- Threads
- Processos
- Produtor e Consumidor
- Algoritmos de escalonamento SJF e Round Robin

> - Faça um programa que leia um número “n” informado pelo usuário e diga quantos números primos há entre 0 e “n”. Esse seu programa deve rodar em 2 threads, de forma que o esforço computacional seja uniformemente dividido entre os threads.<br>

> - Podemos calcular o seno de um número segundo a série de Taylor-Maclaurin como na imagem abaixo.
> Faça um programa em C que lê um valor para x e calcule o valor de Sen(x) utilizando duas threads para dividir os cálculos, uma para os termos com soma e outra para os com subtração. O valor deve ser calculado até ser próximo do seno
> <p align="center"><img  src="https://github.com/isaias0rt0n/sistemas-operacionais/blob/main/imgs/sin.PNG"></p>

> - Crie um programa em C que demonstre uma hierarquia de processos com o comando fork( ) -> Pai -> Filho ->Filho1
> - Crie um programa que receba parâmetros na chamada do main e mostre na saída metade dos parâmetros pelo processo pai e a outra metade pelo processo filho

> - Crie um programa em C que apresente duas funções para threads (produtor e consumidor), nesse devem ser criadas a quantidade de threads definidas por uma variável global QTD e utilizar outra variável global chamada “valor”. O produtor só pode produzir um número se essa variável tiver sido consumida (valor=0), quando ele for produzir é atribuído um número aleatório a variável “valor”. O consumido só pode consumir um número, se ele já tiver sido produzido (valor≠0), quando ele consome é atribuído valor=0. O programa deve seguir as seguintes especificações: (comentário do código)

> - Implemente uma simulação para os algoritmos de escalonamento SJF e Round Robin em C. Em sua implementação o usuário deve fornecer a quantidade de processos que estão na fila para serem executados, a ordem de chegada e o tempo de execução de cada processo. Durante a execução deve ser informado ao usuário qual o processo que está executando e esperado o tempo de cada processo por segundo. Por exemplo, se um processo A demora 5 segundos, deve ser informado que ele está sendo trabalhado e esperado o tempo de execução deste para poder iniciar o próximo, para isso utilize um temporizador em seu algoritmo.
