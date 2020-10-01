/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 15
Soluções de Software – Primeiro Algoritmo
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int count = 0;
char vez;
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
	printf("THREAD %s, FEZ FATORIAL DE %d QUE DEU %lld\n", nome, count, fatorial(count));
}
//------------------------------------------------------------------------------------------
void processamento(){
	sleep(1);
}
//------------------------------------------------------------------------------------------
void *processoPrimeiro(char *nome){
	while(count < 20){
		while(vez == 'B');
		regiaoCritica(nome);
		vez = 'B';
		processamento();
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void *processoSegundo(char *nome){
	while(count < 20){
		while(vez == 'A');
		regiaoCritica(nome);
		vez = 'A';
		processamento();
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	pthread_t thread_1, thread_2;
	vez = 'A';
	pthread_create(&thread_1, NULL, (void*)processoPrimeiro, "thread_1");
	pthread_create(&thread_2, NULL, (void*)processoSegundo, "thread_2");
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}
//------------------------------------------------------------------------------------------