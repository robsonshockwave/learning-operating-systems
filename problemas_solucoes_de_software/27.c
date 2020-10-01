/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 27
Produtor/Consumidor Produtor/Consumidor
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------------
#define  FALSE 0
#define  TRUE  1
pthread_mutex_t  mutex;
#define  BUFFERVAZIO 0
#define  BUFFERCHEIO 1
int buffer;
int estado = BUFFERVAZIO;
//------------------------------------------------------------------------------------------
void produtor(int id){
	int i=0;
	int item;
        int aguardar;

	printf("INICIA PRODUTOR %d \n",id);
	while (i < 10){
            
	    item = i + (id*1000);

        do{
            pthread_mutex_lock(&mutex);
        	aguardar = FALSE;
        	if (estado == BUFFERCHEIO){
	    		aguardar = TRUE;
            	pthread_mutex_unlock(&mutex);
	    	}
		} while (aguardar == TRUE);

        printf("PRODUTOR %d INSERE ITEM %d\n", id, item); 
        buffer = item;
	    estado = BUFFERCHEIO;
	    
	    pthread_mutex_unlock(&mutex);
	    i++;
	    sleep(2);
	}
	printf("PRODUTOR %d ACABOU\n", id); 
}
//------------------------------------------------------------------------------------------
void consumidor(int id){
	int item;
	int aguardar;

	printf("INICIA CONSUMIDOR %d \n",id);
	while (1){
        do{
                pthread_mutex_lock(&mutex);
	        	aguardar = FALSE;
	        if (estado == BUFFERVAZIO){
	            aguardar = TRUE;
		    	pthread_mutex_unlock(&mutex);
		    }
        } while (aguardar == TRUE);

	    item = buffer;
	    estado = BUFFERVAZIO;
	    pthread_mutex_unlock(&mutex);

	    // processar item
        printf("CONSUMIDOR %d PEGOU ITEM %d\n", id, item); 

		sleep(3);
    }
	printf("CONSUMIDOR %d ACABOU \n", id); 
}
//------------------------------------------------------------------------------------------
int main()
{ 
	pthread_t prod1;
	pthread_t prod2;
	pthread_t prod3;
	pthread_t cons1;
	pthread_t cons2;

	pthread_mutex_init(&mutex,NULL);
	pthread_create(&prod1, NULL, (void*) produtor,1);
	pthread_create(&prod2, NULL, (void*) produtor,2);
	pthread_create(&prod3, NULL, (void*) produtor,3);
	pthread_create(&cons1, NULL, (void*) consumidor,1);
	pthread_create(&cons2, NULL, (void*) consumidor,2);
	pthread_join(prod1,NULL);
	pthread_join(prod2,NULL);
	pthread_join(prod3,NULL);
	pthread_join(cons1,NULL);
	pthread_join(cons2,NULL);
	return(0);
}
//------------------------------------------------------------------------------------------