/*
Robson de Arruda Silva - 2019013624
Sistema Operacional - 17/09/2020

Escreva um programa em linguagem C/C++ com múltiplos threads que calcule diversos valores estatísticos para uma lista de valores. Esse programa receberá a quantidade de valores na linha de
comandos e deverá gerar os valores randômicamente e, então, criará três threads de trabalho separados. Um dos threads determinará a média dos valores, o segundo thread determinará o maior
valor e o terceiro determinará o menor valor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

float media = 0;
int maior = 0;
int menor = 0;
int n;

void *media_f(void *arg){
  int *vetor = (int*) arg;
  int valor = 0;
  for(int i=0; i<n; i++) {
    valor += vetor[i];
  }
    
  media = (float)(valor/n)*1.0;
    
  return NULL;
}

void *maior_f(void *arg){
  int *vetor = (int*) arg;
  for(int i=0; i<n; i++){
    if(vetor[i] > maior){
      maior = vetor[i];
    }
  }

  return NULL;
}

void *menor_f(void *arg){
  int *vetor = (int*) arg;
  menor = vetor[0];
  for(int i=0; i<n; i++){
    if(vetor[i] < menor){
      menor = vetor[i];
    }
  }

  return NULL;
}

int main() {

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    int v[n];
    srand(time(NULL));
    for (int i=0; i<n; i++){
        v[i] = rand() % 100;
    }
    printf("Os valores do vetor são: \n");
    for (int i=0; i<n; i++){
        printf("%d ", v[i]);
    }
    
    pthread_t thread_media;
    pthread_create(&thread_media, NULL, media_f, (void*)&v);
    pthread_join(thread_media, NULL);
    
    printf("\n A media dos numeros do vetor eh = %.2f", media);

    pthread_t thread_maior;
    pthread_create(&thread_maior, NULL, maior_f, (void*)&v);
    pthread_join(thread_maior, NULL);

    printf("\n O maior numero do vetor eh = %d", maior);

    pthread_t thread_menor;
    pthread_create(&thread_menor, NULL, menor_f, (void*)&v);
    pthread_join(thread_menor, NULL);

    printf("\n O menor numero do vetor eh = %d", menor);
}