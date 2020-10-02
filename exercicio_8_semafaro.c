/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 01/10/2020

Existem n passageiros, que repetidamente aguardam para entrar em um carrinho da montanha
russa, fazem o passeio, e voltam a aguardar. Vários passageiros podem entrar no carrinho ao mesmo
tempo, pois este tem várias portas. A montanha russa tem somente um carrinho, onde cabem C
passageiros ( C < n ). O carrinho só começa seu percurso se estiver lotado. Sincronize as ações dos
processos Passageiro e Carrinho usando semáforos.
Tente implementar este algoritmo utilizando Threads, Semáforos e Mutex.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 9 //MAX seria o C do enunciado
//---------------------------------------------------------------------------
sem_t passageiro;
sem_t carrinho;
sem_t andando;
sem_t mutex;
//---------------------------------------------------------------------------
int numero_passageiros = 0;
//---------------------------------------------------------------------------
void passeia(){
    sem_wait(&andando);
    sem_post(&carrinho);
    sem_wait(&passageiro);
}
//---------------------------------------------------------------------------
void *Passageiro(){
  while(1){
    sem_wait(&passageiro); //fechamento do semaforo passageiro
    sem_wait(&mutex); //fechamento do semaforo passageiro

    numero_passageiros++;

    if (numero_passageiros == MAX){
        sem_post(&carrinho); //chegou no maximo de passageiro o semáfaro do carrinho será liberado
        sem_wait(&andando); //fecha o o semafaro do carrinho quando ele estiver andando
        sem_post(&mutex); //libera o semafaro no mutex
    }else{
        sem_wait(&andando); //fecha o semaforo quando estiver andando
        sem_post(&mutex); //libera semaforo mutex
    }
  }
}
//---------------------------------------------------------------------------
void *Carrinho(){
    while(1){
        sem_wait(&carrinho);
        passeia();
        numero_passageiros = 0;
        for(int i = 0; i<MAX; i++){
            sem_post(&andando);
            sem_post(&passageiro);
         }
    }
}
//---------------------------------------------------------------------------
int main(void){
    sem_init(&passageiro, 0, MAX);
    sem_init(&carrinho, 0, 0);
    sem_init(&andando, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t td1, td2; //td1 é thread do carrinho e td2 do passageiro
    int thread_id[2];
    pthread_create(&td1, NULL, Carrinho, (void *)&thread_id[0]);
    pthread_create(&td2, NULL, Passageiro, (void *)&thread_id[1]);
}
//---------------------------------------------------------------------------