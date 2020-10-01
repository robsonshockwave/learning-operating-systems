/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 28/09/2020

Slide 19
Algoritmo de Dekker
*/

  #include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>
//------------------------------------------------------------------------------------------
  #define TRUE 1
  #define FALSE 0
  int flag[2], turn;
//------------------------------------------------------------------------------------------
  void dekker_th0( void ){
    int i, j, k;
    for( i=0; i<5; i++ ) {
      flag[0] = TRUE;
      while( flag[1] )  {
        if( turn == 1 ) {
          flag[0] = FALSE;
          while( turn == 1 ) ;
          flag[0] = TRUE;
        }
      }
      printf("  Thread 0: DENTRO DA REGIAO CRITICA \n");
      turn = 1;  flag[0] = FALSE;
      for( j=0; j<16384; j++ )
        for( k=0; k<8192; k++) ;
    }
  }
//------------------------------------------------------------------------------------------
  void dekker_th1( void ){
    int i, j, k;

    for( i=0; i<8; i++ ) {
      flag[1] = TRUE;
      while( flag[0] )  {
        if( turn == 0 ) {
          flag[1] = FALSE;
          while( turn == 0 ) ;
          flag[1] = TRUE;
        }
      }
      printf("    Thread 1: DENTRO DA REGIAO CRITICA \n");
      turn = 0;   flag[1] = FALSE;

      for( j=0; j<8192; j++ )
        for( k=0; k<4096; k++) ;
    }
  }
//------------------------------------------------------------------------------------------
  int main( int argc, char* argv[] ){
    pthread_t th0, th1;
    int r_th0, r_th1;
    turn = 0;
    flag[0] = flag[1] = FALSE;
    printf("Thread \"Main\": Algoritmo de \"Dekker\" \n");
    if( pthread_create( &th0, NULL, (void *) dekker_th0, NULL ) != 0 ) {
      printf("Error \"pthread_create\" p/ Thread 0.\n");
      exit(1);
    }
    if( pthread_create( &th1, NULL, (void *) dekker_th1, NULL ) != 0 ) {
      printf("Error \"pthread_create\" p/ Thread 1.\n");
      exit(1);
    }
    printf("Thread \"Main\": Sincroniza termino com Threads 0 e 1.\n");
    pthread_join( th0, (void *) &r_th0 );
    pthread_join( th1, (void *) &r_th1 );
    printf("Thread \"Main\": Termina.\n");
    exit(0);
  }