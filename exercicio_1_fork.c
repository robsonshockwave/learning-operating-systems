/*
Robson de Arruda Silva - 2019013624
Sistema Operacional 03/09/2020

Exercício 1
Crie um programa em C que cria um processo filho através do fork(). O processo original deve
exibir na tela a frase “Sou o processo pai” 30 vezes, enquanto o processo filho deve exibir a frase:
“Sou o processo filho” 1000 vezes na tela.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    int pid=0;
    int pidpai, pidfilho;
    pidpai = getpid();
    pid=fork();
    
    if (pid != 0){
		for(int i=0; i<30; i++){
        printf( "Sou processo pai!\n");
		}
    }else{
        pidfilho = getpid();
		for(int i=0; i<1000; i++){
        printf("Sou processo filho!\n");
		}
    }
    
    return 0;
}