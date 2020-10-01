/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 18
Soluções de Software - Quarto Algoritmo
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
//------------------------------------------------------------------------------------------
#define MAX 20
int count = 0;
bool CA, CB;
//------------------------------------------------------------------------------------------
long long unsigned int fatorial(int n){
	long long unsigned int fat = 0;
	if(n == 0 || n == 1){
		return 1;
	}
	fat = n * fatorial(n - 1);
	return fat;
}
//------------------------------------------------------------------------------------------
void regiaoCritica(char *nome){
	count++;
	printf("THREAD %s, FEZ O FATORIAL DE %d QUE DEU %lld\n", nome, count, fatorial(count));
}
//------------------------------------------------------------------------------------------
void processamento(){
	sleep(3);
}
//------------------------------------------------------------------------------------------
void *primeiroProcessamento(char *nome){
	while(count < MAX){
		CA = true;
		while(CB){
			CA = false;
			sleep(2);
			CA = true;
		}
		regiaoCritica(nome);
		CA = false;
		processamento();
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void *segundoProcessamento(char *nome){
	while(count < MAX){
		CB = true;
		while(CA){
			CB = false;
			sleep(2);
			CB = true;
		}
		regiaoCritica(nome);
		CB = false;
		processamento();
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	pthread_t thread_1, thread_2;
	CA = false;
	CB = false;
	pthread_create(&thread_1, NULL, (void*)primeiroProcessamento, "thread_1");
	pthread_create(&thread_2, NULL, (void*)segundoProcessamento, "thread_2");
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}
//------------------------------------------------------------------------------------------