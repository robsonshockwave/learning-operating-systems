#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 12/09/2020

PROGRAMA LINEAR, SEM A CRIAÇÃO DE PROCESSOS
*/
double seno_f(float x, int n);
double cosseno_f(float x, int n);

int main () {
    double soma_cosseno, soma_seno, soma_tangente;
    float x;
    int n;
    clock_t t1, t2, t1_2, t2_2, t1_3, t2_3;

    printf ("Digite o valor de x: ");
    scanf("%f",&x);
    printf("Digite um valor para o n da serie: ");
    scanf("%d", &n);
    printf("\n");

    t1 = clock();
    soma_cosseno = cosseno_f(x, n);;
    t2 = clock();
    float diff = (((float)t2 - (float)t1) / 1000000.0F ); // milissegundos
    printf("O tempo da operação cosseno foi de %f milissegundos\n", diff);
    printf ("\n A soma cosseno eh de = %f\n\n", soma_cosseno);

    t1_2 = clock();
    soma_seno = seno_f(x, n);
    t2_2 = clock();
    diff = (((float)t2_2 - (float)t1_2) / 1000000.0F ); // milissegundos
    printf("O tempo da operação seno foi de %f milissegundos\n", diff);
    printf ("\n A soma seno eh de = %f\n\n", soma_seno);
    
    t1_3 = clock();
    if (soma_cosseno != 0){
        soma_tangente = soma_seno/soma_cosseno;
        t2_3 = clock();
        diff = (((float)t2_3 - (float)t1_3) / 1000000.0F ); // milissegundos
        printf("O tempo da operação tangente foi de %f milissegundos\n", diff);
        printf ("\nA soma tagente eh de = %.8f\n\n", soma_tangente);
    }else{
        t2_3 = clock();
        diff = (((float)t2_3 - (float)t1_3) / 1000000.0F ); // milissegundos
        printf("O tempo da operação tangente foi de %f milissegundos\n", diff);
        printf ("\n\nA soma cosseno deu zero, erro de calculo para a tangente!\n");
    }

    return 0;
}

double seno_f(float x, int n){
    int fat, i, expo=3, fatorial;
    float sen=x;

    if (n>=2){
        for (i=2; i<=n; i++){
            fat=1;
            for(fatorial=expo; fatorial>=1; fatorial--)
                fat=fatorial*fat;
            if (i%2==0)
                sen= sen-((pow(x,expo))/(float)fat);
            else
                sen= sen+((pow(x,expo))/(float)fat);
            expo=expo+2;
        }
    }
    return sen;
}

double cosseno_f(float x, int n){
    int fat, i, expo=2, fatorial;
    float cos=1;

    if (n>=2){
        for (i=2; i<=n; i++){
            fat=1;
            for(fatorial=expo; fatorial>=1; fatorial--)
                fat=fatorial*fat;
                if (i%2==0)
                    cos= cos-((pow(x,expo))/(float)fat);
                else
                    cos= cos+((pow(x,expo))/(float)fat);
                expo=expo+2;
        }
    }
    return cos;
}