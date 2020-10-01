/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 28
Problema dos Filósofos
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//------------------------------------------------------------------------------------------
#define QUANT      (5)                     
#define ESQUERDA   (id_filosofo + QUANT - 1) % QUANT   
#define DIREITA   (id_filosofo + 1) % QUANT              
#define PENSANDO   (0)                     
#define FAMINTO   (1)                      
#define COMENDO   (2)                     
//------------------------------------------------------------------------------------------
int estado [QUANT];                     
pthread_mutex_t mutex;                    
pthread_mutex_t mux_filo [QUANT];                 
pthread_t jantar[QUANT];                         
void * filosofo ( void * param );
void pegar_hashi ( int id_filosofo );
void devolver_hashi ( int id_filosofo );
void intencao ( int id_filosofo );
void comer ( int id_filosofo );
void pensar ( int id_filosofo );
//------------------------------------------------------------------------------------------
void * filosofo ( void * vparam ){
   int * id = (int *) (vparam);   
   printf("Filosofo %d foi criado com sucesso\n", *(id) );
   while ( 1 ){
      pensar( *(id) );         
      pegar_hashi( *(id) );      
      comer( *(id) );       
      devolver_hashi( *(id) );  
   }
   pthread_exit( (void*) 0 );    
}
//------------------------------------------------------------------------------------------
void pegar_hashi ( int id_filosofo ){
   pthread_mutex_lock( &(mutex) );       
   printf("Filosofo %d esta faminto\n", id_filosofo);
   estado[ id_filosofo ] = FAMINTO;          
   intencao( id_filosofo );              
   pthread_mutex_unlock( &(mutex) );      
   pthread_mutex_lock( &(mux_filo[id_filosofo]) );  
}
//------------------------------------------------------------------------------------------
void devolver_hashi ( int id_filosofo ){
   pthread_mutex_lock ( &(mutex) );  
   printf("Filosofo %d esta pensando\n", id_filosofo);
   estado[ id_filosofo ] = PENSANDO;   
   intencao( ESQUERDA );       
   intencao( DIREITA );           
   pthread_mutex_unlock ( &(mutex) );   
}
//------------------------------------------------------------------------------------------
void intencao ( int id_filosofo ){
   printf("Filosofo %d esta com intencao de comer\n", id_filosofo);
   if( (estado[id_filosofo] == FAMINTO) &&          
      (estado[ESQUERDA] != COMENDO) &&     
      (estado[DIREITA] != COMENDO ) )      
   {
      printf("Filosofo %d ganhou a vez de comer\n", id_filosofo);
      estado[ id_filosofo ] = COMENDO;          
      pthread_mutex_unlock( &(mux_filo[id_filosofo]) );   
   }
}
//------------------------------------------------------------------------------------------
void pensar ( int id_filosofo ){
   int r = (rand() % 10 + 1);
   
   printf("Filosofo %d pensa por %d segundos\n", id_filosofo, r );
   sleep( r );   
}
//------------------------------------------------------------------------------------------
void comer ( int id_filosofo ){
   int r = (rand() % 10 + 1);
   printf("Filosofo %d come por %d segundos\n", id_filosofo, r);
   sleep( r ); 

}
//------------------------------------------------------------------------------------------
int main ( void ){
   int cont; 
   int status;  
   pthread_mutex_init( &(mutex), NULL);
   for( cont = 0 ; cont < QUANT ; cont++ ){
      pthread_mutex_init( &(mux_filo[cont]), NULL );
   }

   for( cont = 0 ; cont < QUANT ; cont++ ){
      status = pthread_create( &(jantar[cont]), NULL, filosofo, (void *) &(cont) );
      if ( status ){
         printf("Erro criando thread %d, retornou codigo %d\n", cont, status );
         return EXIT_FAILURE;
      }
   }

   pthread_mutex_destroy( &(mutex) );
   for( cont = 0 ; cont < QUANT ; cont++ ){
      pthread_mutex_destroy( &(mux_filo[cont]) );
   }
   pthread_exit( NULL );

   return EXIT_SUCCESS;
}
//------------------------------------------------------------------------------------------