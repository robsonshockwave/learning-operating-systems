#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<math.h>
#include<time.h>

/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 12/09/2020

Escreva um programa para calcular tan x, sendo x um ângulo em radianos. Sabemos que tan x = sen x/ cos x, e sen x e cos x podem ser calculados utilizando as seguintes séries:
Os valores de sen x e cos x deverão ser calculados em processos separados e o processo pai deverá calcular e imprimir tan x com uma precisão de 10-8, ou seja os valores de seno 
e cosseno deverão ter o último termo com valor menor que 10-8. O valor de x deverá ser lido pelo processo pai e enviado para os processos filhos.
Sugestão: utilize 1 pipe para cada processo filho para que o processo pai envie o valor de x e 1 pipe de cada processo filho para o pai receber os valores calculados.
Verifique qual é o tempo de execução do cálculo em caso de um programa totalmente linear onde se calcular o seno e depois o cosseno e compare com o tempo de execução com a 
utilização dos processos. Utilize variáveis double para atingir a precisão desejada.
PROGRAMA NÃO LINEAR, COM A CRIAÇÃO DE PROCESSOS
*/

double seno_f(float x, int n);
double cosseno_f(float x, int n);

int main(int argc, char *argv[]){
    int fd_um[2], fd_dois[2], fd_tres[2], fd_quatro[2];
	
	pid_t pid; 
	
	float x;
    double seno, cosseno, tangente;
    int n;

    clock_t t1, t2; // duas variáveis para guardar o registro clock

	printf("PAI de fora - recebendo o valor de x para enviar para os filhos como parametro \n\nDigite um valor de x: \n");
	scanf("%f", &x);
	printf("PAI de fora - digite um valor para o n da serie: \n");
	scanf("%d", &n);
	printf("\n\n--------------------------------------------------------------------------------\n\n");
    
	if(pipe(fd_um) < 0 || pipe(fd_dois) < 0 ||  pipe(fd_tres) < 0 || pipe(fd_quatro) < 0) {
		perror("pipe");
		return -1;
	}
	
	if(fork() != 0){ //processo pai
		
		close(fd_um[0]);
        write(fd_um[1], &x, sizeof(x));
        close(fd_um[0]);
        write(fd_um[1], &n, sizeof(n));
		
		close(fd_dois[1]);
		read(fd_dois[0], &cosseno, sizeof(cosseno));
		
		printf("PAI (%d) - valor recebido pelo filho 1, cujo eh o valor de cosseno = %f\n\n", getpid(), cosseno);

		if(fork() != 0){ //processo pai
			
			close(fd_tres[0]); 
			write(fd_tres[1], &x, sizeof(x));
			close(fd_tres[0]); 
			write(fd_tres[1], &n, sizeof(n));
			
			close(fd_quatro[1]);
			read(fd_quatro[0], &seno, sizeof(seno));

			printf("PAI (%d) - valor recebido pelo filho 2, cujo eh o valor de seno = %f\n\n", getpid(), seno);

            t1 = clock();
            if(cos != 0){
                tangente = seno/cosseno;
                t2 = clock();
                float diff = (((float)t2 - (float)t1) / 1000000.0F ); // milissegundos
            printf("O tempo da operação tangente no processo pai foi de %f milissegundos\n\n",diff);
            }else{
                t2 = clock();
                float diff = (((float)t2 - (float)t1) / 1000000.0F ); // milissegundos
                printf("O tempo da operação tangente no processo pai foi de %f milissegundos\n\n",diff);
                printf ("ERRO NA TANGENTE - SOMA DO COSSENO = 0");
                printf("\n");
                return 0;
            }
			
            printf("PAI (%d) - valor da tangente eh = %.8f\n\n", getpid(), tangente);
			
		} else { //processo filho
            
            clock_t t1_1, t2_1;
			close(fd_tres[1]);
			read(fd_tres[0], &x, sizeof(x));
			close(fd_tres[1]);
			read(fd_tres[0], &n, sizeof(n));
        
			printf("FILHO (%d) - Valor recebido pelo filho 2 antes da operação de seno: %f\n", getpid(), x);
            t1_1 = clock();
			seno = seno_f(x, n);
            t2_1 = clock();
            float diff = (((float)t2_1 - (float)t1_1) / 1000000.0F ); // milissegundos
            printf("O tempo da operação seno no processo filho 2 foi de %f milissegundos\n\n",diff);
			printf("FILHO (%d) - Valor recebido do filho 2 depois da operação de seno: %f\n\n", getpid(), seno);

			close(fd_quatro[0]);
			write(fd_quatro[1], &seno, sizeof(seno));

		}
	} else { //processo filho

        clock_t t1_2, t2_2;
		close(fd_um[1]);
		read(fd_um[0], &x, sizeof(x));
		close(fd_um[1]);
		read(fd_um[0], &n, sizeof(n));
        
		printf("FILHO (%d) - Valor recebido pelo filho 1 antes da operação de cosseno: %f\n", getpid(), x);
		t1_2 = clock();
        cosseno = cosseno_f(x, n);
        t2_2 = clock();
        float diff = (((float)t2_2 - (float)t1_2) / 1000000.0F ); // milissegundos
        printf("O tempo da operação cosseno no processo filho 1 foi de %f milissegundos\n\n",diff);
		printf("FILHO (%d) - Valor recebido do filho 1 depois da operação de cosseno: %f\n\n", getpid(), cosseno);

		close(fd_dois[0]);
        write(fd_dois[1], &cosseno, sizeof(cosseno));
		
	}
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