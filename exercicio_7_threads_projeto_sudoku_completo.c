/* 
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 27/09/2020

Um quebra-cabeça Sudoku usa um grid de 9 x 9 em que cada coluna e cada linha, assim assim como
cada um dos subgrids 3 x 3, devem conter todos os dígitos 1 … 9. A figura abaixo apresenta um
exemplo de quebra-cabeça Sudoku válido. Esse projeto consiste na elaboração de uma aplicação
com múltiplos threads que determine se a solução para um quebra-cabeça Sudoku é válida.
Existem várias maneiras diferentes de tornar essa aplicação multithread. Uma estratégia sugerida é
criar threads que verifiquem os critérios a seguir:
• Um thread para verificar se cada coluna contém os dígitos de 1 a 9.
• Um thread para verificar se cada linha contém os dígitos de 1 a 9.
• Nove threads para verificar se cada um dos subgrids 3 x 3 contém os dígitos de 1 a 9.
Isso resultaria em um total de 11 threads separados para a validação de um quebra-cabeça Sudoku.
No entanto, você é incentivado a criar ainda mais threads para esse projeto. Por exemplo, em vez de
criar um thread para verificar todas as nove colunas, você poderia criar nove threads e fazer cada
um verificar uma coluna.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//--------------------------------------------------------------------
typedef struct {
    int linha; //linha inicial
    int coluna; //colunauna inicial
    int (* tabela)[9]; //ponteiro para o tabuleiro
} parameters;
//--------------------------------------------------------------------
void * indoLinhas(void * params);
void * indoColunas(void * params);
void * verificaQuadrado(void * params);
//--------------------------------------------------------------------
int main(void) {

    int tabela[9][9] = {  
            {1,8,4,9,5,2,7,6,3},
            {7,2,3,6,1,8,5,9,4},
            {9,5,6,7,4,3,2,1,8},
            {2,3,8,1,7,9,6,4,5},
            {4,7,9,5,8,6,1,3,2},
            {5,6,1,3,2,4,8,7,9},
            {6,4,7,8,3,5,9,2,1},
            {3,1,5,2,9,7,4,8,6},
            {8,9,2,4,6,1,3,5,7}
        };
    
    printf("\n\nBEM VINDO AO JODO SUDOKU (=^^=)\n\n");
    printf("SUDOKU DE ENTRADA!! (ERRADO)\n_____________________________\n");
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            printf(" %d ", tabela[i][j]);
            if(j == 2 || j == 5){
            printf("|");
            }
        }
        if(i==2 || i==5){
            printf("\n_____________________________");
        }
        printf("\n");
    }
    printf("_____________________________\n\n\n");   
    
    // Cria o parâmetro para verificar as colunas e as linhas 
    parameters * param0 = (parameters *) malloc(sizeof(parameters));
    param0->linha = 0;
    param0->coluna = 0;
    param0->tabela = tabela;
    // Crie os parâmetros para os threads 3x3
    // Primeiro quadrado
    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1->linha = 0;
    param1->coluna = 0;
    param1->tabela = tabela;
    // Segundo quadrado
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2->linha = 0;
    param2->coluna = 3;
    param2->tabela = tabela;
    // Terceiro quadrado
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3->linha = 0;
    param3->coluna = 6;
    param3->tabela = tabela;
    // Quarto quadrado
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4->linha = 3;
    param4->coluna = 0;
    param4->tabela = tabela;
    // Quinto quadrado
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5->linha = 3;
    param5->coluna = 3;
    param5->tabela = tabela;
    // Sexto quadrado
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6->linha = 3;
    param6->coluna = 6;
    param6->tabela = tabela;
    // Sétimo quadrado
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7->linha = 6;
    param7->coluna = 0;
    param7->tabela = tabela;
    // Oitavo quadrado
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->linha = 6;
    param8->coluna = 3;
    param8->tabela = tabela;
    // Nono quadrado
    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->linha = 6;
    param9->coluna = 6;
    param9->tabela = tabela;
    // Criação das threads
    pthread_t thread_linhas, thread_colunas, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
    // Criação dos valores de retorno para os threads
    void * all_linhas;
    void * all_colunas;
    void * quadrado1;
    void * quadrado2;
    void * quadrado3;
    void * quadrado4;
    void * quadrado5;
    void * quadrado6;
    void * quadrado7;
    void * quadrado8;
    void * quadrado9;
    // Iniciando as threads
    pthread_create(&thread_linhas, NULL, indoLinhas, (void *) param0);
    pthread_create(&thread_colunas, NULL, indoColunas, (void *) param0);
    pthread_create(&thread1, NULL, verificaQuadrado, (void *) param1);
    pthread_create(&thread2, NULL, verificaQuadrado, (void *) param2);
    pthread_create(&thread3, NULL, verificaQuadrado, (void *) param3);
    pthread_create(&thread4, NULL, verificaQuadrado, (void *) param4);
    pthread_create(&thread5, NULL, verificaQuadrado, (void *) param5);
    pthread_create(&thread6, NULL, verificaQuadrado, (void *) param6);
    pthread_create(&thread7, NULL, verificaQuadrado, (void *) param7);
    pthread_create(&thread8, NULL, verificaQuadrado, (void *) param8);
    pthread_create(&thread9, NULL, verificaQuadrado, (void *) param9);
    // Esperando que todas as threads terminem suas tarefas
    pthread_join(thread_linhas, &all_linhas);
    pthread_join(thread_colunas, &all_colunas);
    pthread_join(thread1, &quadrado1);
    pthread_join(thread2, &quadrado2);
    pthread_join(thread3, &quadrado3);
    pthread_join(thread4, &quadrado4);
    pthread_join(thread5, &quadrado5);
    pthread_join(thread6, &quadrado6);
    pthread_join(thread7, &quadrado7);
    pthread_join(thread8, &quadrado8);
    pthread_join(thread9, &quadrado9);

    printf("SUDOKU DE SAIDA!! (RESULTADO)\n_____________________________\n");
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            printf(" %d ", tabela[i][j]);
            if(j == 2 || j == 5){
            printf("|");
            }
        }
        if(i==2 || i==5){
            printf("\n_____________________________");
        }
        printf("\n");
    }
    printf("_____________________________\n\n\n");
    printf("... Verificando se seu sudoku esta certo: \n");
    //Verificando se o sudoku foi resolvido
    if (    (int) all_linhas == 1 &&
            (int) all_colunas == 1 &&
            (int) quadrado1 == 1 &&
            (int) quadrado2 == 1 &&
            (int) quadrado3 == 1 &&
            (int) quadrado4 == 1 &&
            (int) quadrado5 == 1 &&
            (int) quadrado6 == 1 &&
            (int) quadrado7 == 1 &&
            (int) quadrado8 == 1 &&
            (int) quadrado9 == 1 ) {
        printf("O SUDOKU ESTÁ CERTO, PARABENS!!! ^^\n");
    }
    else {
        printf("O SUDOKU ESTA ERRADO, ARRUME O(S) NUMERO(S) NA MATRIZ!\n");
    }
    
    return 0;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void * indoLinhas(void * params) {
    parameters * data = (parameters *) params;
    int startlinha = data->linha;
    int startcoluna = data->coluna;
    for (int i = startlinha; i < 9; ++i) {
        int linha[10] = {0};
        for (int j = startcoluna; j < 9; ++j) {
            int val = data->tabela[i][j];
            if (linha[val] != 0) {
                return (void *) 0;
            }
            else{
                linha[val] = 1;
            }
        }
    }
    return (void *) 1;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void * indoColunas(void * params) {
    parameters * data = (parameters *) params;
    int startlinha = data->linha;
    int startcoluna = data->coluna;
    for (int i = startcoluna; i < 9; ++i) {
        int coluna[10] = {0};
        for (int j = startlinha; j < 9; ++j) {
            int val = data->tabela[j][i];
            if (coluna[val] != 0) {
                return (void *) 0;
            }
            else{
                coluna[val] = 1;
            }
        }
    }
    return (void *) 1;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void * verificaQuadrado(void * params) {
    parameters * data = (parameters *) params;
    int startlinha = data->linha;
    int startcoluna = data->coluna;
    int saved[10] = {0};
    for (int i = startlinha; i < startlinha + 3; ++i) {
        for (int j = startcoluna; j < startcoluna + 3; ++j) {
            int val = data->tabela[i][j];
            if (saved[val] != 0) {
                return (void *) 0;
            }
            else{
                saved[val] = 1;
            }
        }
    }
    return (void *) 1;
}
//--------------------------------------------------------------------