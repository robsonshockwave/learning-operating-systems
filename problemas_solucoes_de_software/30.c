/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 30
Problema do Barbeiro
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N_CLIENTES 20
//------------------------------------------------------------------------------------------
sem_t mutex;
sem_t cabelo;
sem_t cabelo_cortado;
sem_t barba;
sem_t barba_feita;
sem_t cor;
sem_t cabelo_pintado;
int fila = 0;
//------------------------------------------------------------------------------------------
void* funcaoBarbeiroCabeleireiro(void *v){
	while(1){
		sem_wait(&cabelo);		
		sem_wait(&mutex);	
		fila--;			
		sem_post(&mutex);
		sem_post(&cabelo_cortado);
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void* funcaoClienteCabelo(void *v){
	int id = *(int*) v;
	sleep(id %5);	
	printf("CLIENTE %d CHEGANDO NA BARBEARIA PARA CORTAR O CABELO.\n", id);	
	sem_wait(&mutex); 						
	if(fila < 5){						
		fila++;							
		sem_post(&cabelo);					
		sem_post(&mutex);					
		sem_wait(&cabelo_cortado);			
		printf("CLIENTE %d SAINDO COM O CABELO CORTADO.\n", id);	
	}
	else{						
		sem_post(&mutex);				
		printf("CLIENTE %d SAINDO BRAVO.\n", id); 
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void* funcaoBarbeiroBarbeiro(void *v){	
	while(1){
		sem_wait(&barba);
		sem_wait(&mutex);
		fila--;
		sem_post(&mutex);
		sem_post(&barba_feita);
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void* funcaoClienteBarba(void *v){
	int id = *(int*) v;
	sleep(id % 5);
	printf("CLIENTE %d CHEGANDO NA BARBEARIA PARA BARBEAR.\n", id);
	sem_wait(&mutex);
	if(fila < 5){
		fila++;
		sem_post(&barba);
		sem_post(&mutex);
		sem_wait(&barba_feita);
		printf("CLIENTE %d SAINDO COM A BARBA FEITA.\n", id);
	}
	else{
		sem_post(&mutex);
		printf("CLIENTE %d SAINDO NERVOSO.\n", id);
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void* funcaoBarbeiroPintor(void *v){
	while(1){
		sem_wait(&cor);
		sem_wait(&mutex);
		fila--;
		sem_post(&mutex);
		sem_post(&cabelo_pintado);
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
void* funcaoClienteCor(void *v){
	int id = *(int*) v;
	sleep(id % 5);
	printf("CLIENTE %d CHEGANDO NA BARBEARIA PARA PINTAR O CABELO.\n", id);
	sem_wait(&mutex);
	if(fila < 5){
		fila++;
		sem_post(&mutex);
		sem_post(&cor);
		sem_wait(&cabelo_pintado);
		printf("CLIENTE %d SAINDO COM CABELO PINTADO.\n", id);
	}
	else{
		sem_post(&mutex);
		printf("CLIENTE %d SAINDO IRRITADO.\n", id);
	}
	return NULL;
}
//------------------------------------------------------------------------------------------
int main() {
	pthread_t thr_clientes[N_CLIENTES * 3], thr_barbeiro_1, thr_barbeiro_2, thr_barbeiro_3; 
	int i, id[N_CLIENTES * 3];    		
	sem_init(&mutex, 0, 1); 			
	sem_init(&cabelo, 0, 0);				
	sem_init(&cabelo_cortado, 0, 0);
	sem_init(&barba, 0, 0);
	sem_init(&barba_feita, 0, 0);
	sem_init(&cor, 0, 0);
	sem_init(&cabelo_pintado, 0, 0);
	for (i = 0; i < N_CLIENTES; i++) {			
		id[i] = i;
		pthread_create(&thr_clientes[i], NULL, funcaoClienteCabelo, (void*) &id[i]);
	}
  	for (i = N_CLIENTES; i < 2 * N_CLIENTES; i++) {	
		id[i] = i;
		pthread_create(&thr_clientes[i], NULL, funcaoClienteBarba, (void*) &id[i]);
	}
	for (i = 2 * N_CLIENTES; i < 3 * N_CLIENTES; i++) {	
		id[i] = i;
		pthread_create(&thr_clientes[i], NULL, funcaoClienteCor, (void*) &id[i]);
	}
	pthread_create(&thr_barbeiro_1, NULL, funcaoBarbeiroCabeleireiro, NULL);	
	pthread_create(&thr_barbeiro_2, NULL, funcaoBarbeiroBarbeiro, NULL);
	pthread_create(&thr_barbeiro_3, NULL, funcaoBarbeiroPintor, NULL);
	for (i = 0; i < N_CLIENTES * 3; i++){
		pthread_join(thr_clientes[i], NULL);
	} 
	return 0;
}
//------------------------------------------------------------------------------------------