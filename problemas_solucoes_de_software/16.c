/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 16
Soluções de Software – Segundo Algoritmo Soluções de Software – Segundo Algoritmo
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
//------------------------------------------------------------------------------------------
int count = 0;
bool CA, CB;
//------------------------------------------------------------------------------------------
long long unsigned int fatorial(int n){
	long long unsigned int fat = 0;
	if(n == 0 || n == 1)
		return 1;
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
void *processamentoPrimeiro(char *nome){
	while(count < 20){
		while(CB);
		CA = true;
		regiaoCritica(nome);
		CA = false;
		processamento();
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void *processamentoSegundo(char *nome){
	while(count < 20){
		while(CA);
		CB = true;
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
	pthread_create(&thread_1, NULL, (void*)processamentoPrimeiro, "thread_1");
	pthread_create(&thread_2, NULL, (void*)processamentoSegundo, "thread_2");
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}
//------------------------------------------------------------------------------------------