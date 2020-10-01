/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 29
Problema dos Filósofos
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
//------------------------------------------------------------------------------------------
#define N        5             
#define LEFT     (i+N-1)%N     
#define RIGHT    (i+1)%N      
#define THINKING 0           
#define HUNGRY   1          
#define EATING   2          
#define TRUE 1
#define TEMPO_PENSANDO 6       
#define TEMPO_COMENDO 15       
//------------------------------------------------------------------------------------------
typedef pthread_mutex_t semaphore;       
int state[N];                            
pthread_mutex_t mutex;                   
pthread_mutex_t s[N];                    
struct{
	int id_gulosos[2];       
	int cont;               
}typedef chekin_t;  
chekin_t c;
int chungry;                
clock_t clk;               
//------------------------------------------------------------------------------------------
void think();
void eat();
void * philosopher(void * args);
void take_forks(int i);
void put_forks(int i);
void test(int i);
//------------------------------------------------------------------------------------------
void think(){
	sleep(TEMPO_PENSANDO); 
}
//------------------------------------------------------------------------------------------
void eat()
{
	sleep(TEMPO_COMENDO);
}
//------------------------------------------------------------------------------------------
void * philosopher(void * args)        
{
	int i = (long) args;
	while(TRUE){              
		think();              
		take_forks(i);        
		eat();                
		put_forks(i);         
	}
}
//------------------------------------------------------------------------------------------
void take_forks(int i)         
{
	pthread_mutex_lock(&mutex);              
	state[i] = HUNGRY;                     
	test(i);                                 
	pthread_mutex_unlock(&mutex);          
	pthread_mutex_lock(&s[i]);        
}
//------------------------------------------------------------------------------------------
void put_forks(int i)                      
{
	pthread_mutex_lock(&mutex);             
	clk = clock();                           
	if (state[i]==EATING){
		printf("%ld - FILOSOFO %d LARGOU OS GARFOS\n", clk, i);
		c.cont--;
		}
	state[i] = THINKING;       
	test(LEFT);                
	test(RIGHT);             
	pthread_mutex_unlock(&mutex);                
}
//------------------------------------------------------------------------------------------
void test(int i)                      
{
	if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
		state[i] = EATING;
		clk = clock();            
		printf("%ld - FILOSFO %d PEGOU OS GARFOS\n", clk, i);
		c.cont++;             
		switch(c.cont){
			case 1: c.id_gulosos[c.cont-1] = i; break;   
			case 2: c.id_gulosos [c.cont-1] = i;         
			        clk = clock();                       
			        printf("%ld - OS FILOSOFOS %d E %d ESTAO COMENDO JUNTOS.\n\n---------------------------------\n\n", clk, c.id_gulosos[0], c.id_gulosos[1]); 
					break;     
			default:
			    break;
		}
		pthread_mutex_unlock(&s[i]);
	}else if(state[i]==HUNGRY){        
		chungry++;                    
		clk = clock();             
		printf("%ld - FILOSOFO %d ESTA FAMINTO, ESPERANDO POR GARFOS.\n", clk, i);
		if(chungry==3){               
			clk = clock();           
			printf("%ld - %d FILOSOFOS NA FILA ESPERANDO POR GARFOS.\n", clk, chungry);
			chungry = 0;
		}
	}
}
//------------------------------------------------------------------------------------------
int main(int arg, char * args[], char * envp[]){
	pthread_t philosophers[N];        
	int rc;                         
	c.cont = 0;                  
	chungry = 0;                      
	pthread_mutex_init(&mutex, 0);    
	printf("\nDIGITE O NUMERO 0 PARA ENCERRAR O PROGRAMA\n\n\n");
	for(long i = 0; i < N; i++){
		pthread_mutex_init(&s[i],0);  
		rc = pthread_create(&philosophers[i], NULL, philosopher, (void *) i); 
		if (rc){ 
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			return -1;
    	}
	}
	char flag[100];
	while(TRUE){ 
		fgets(flag,100, stdin);
		if ( strcmp(flag, "0\n")== 0)
		    break;
	}; 

	for (int i = 0; i < N; i++)
    	pthread_mutex_destroy(&s[i]); 
	pthread_mutex_destroy(&mutex);
	return 0;
}
//------------------------------------------------------------------------------------------