#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 

/*
Robson de Arruda Silva - 2019013624
Sistemas Operacionais - 05/09/2020

Processo Pai: Recebe dois parâmetros na inicialização. O processo pai cria dois processos filhos e
envia o primeiro parâmetro para o filho 1 e o segundo para o filho 2 atravéz de mensagens (pipe).
Quando os processos filhos retornam os resultados, o pai então soma e apresenta o resultado final na tela.
Processo Filho 1: Recebe como mensagem (pipe) um número e retorna o quadrado deste número, também através de mensagem.
Processo Filho 2: Recebe como mensagem (pipe) um número e retorna o fatorial do mesmo, também atravéz de mensagem.
*/

int fatorial(int n);
int exponencial(int n);

int main(int argc, char *argv[])
{
    int fd_um[2], fd_dois[2], fd_tres[2], fd_quatro[2];
	
	pid_t pid; 
	
	int v1, v2;
	
	printf("PAI de fora - recebendo os valores para enviar para os filhos como parametros \n\nDigite um valor para fazer o fatorial do mesmo: \n");
	scanf("%d", &v1);
    printf("Digite outro valor para o filho 2 fazer a exponenciação do mesmo: \n");
	scanf("%d", &v2);
	printf("\n\n--------------------------------------------------------------------------------\n\n");
    
	if(pipe(fd_um) < 0 || pipe(fd_dois) < 0 ||  pipe(fd_tres) < 0 || pipe(fd_quatro) < 0) {
		perror("pipe");
		return -1;
	}
	
	if(fork() != 0){ //processo pai
		
		close(fd_um[0]);
        write(fd_um[1], &v1, sizeof(v1));
		
		close(fd_dois[1]);
		read(fd_dois[0], &v1, sizeof(v1));
		
		printf("PAI (%d) - valor recebido pelo filho 1 = %d\n\n", getpid(), v1);

		if(fork() != 0){ //processo pai
			
			close(fd_tres[0]); 
			write(fd_tres[1], &v2, sizeof(v2)); 
			
			close(fd_quatro[1]);
			read(fd_quatro[0], &v2, sizeof(v2));

			printf("PAI (%d) - valor recebido pelo filho 2 = %d\n\n", getpid(), (v2));
			printf("PAI (%d) - a soma do filho 1 com o filho 2 tem como resultado = %d\n\n FIM DO PROGRAMA :D", getpid(), (v2+v1));
			
		} else { //processo filho
            
			close(fd_tres[1]);
			read(fd_tres[0], &v2, sizeof(v2));
        
			printf("FILHO (%d) - Valor recebido pelo filho 2 antes da operação: %d\n", getpid(), v2);
			v2 = exponencial(v2);
			printf("FILHO (%d) - Valor recebido do filho 2 depois da operação: %d\n\n", getpid(), v2);

			close(fd_quatro[0]);
			write(fd_quatro[1], &v2, sizeof(v2));

		}
	} else { //processo filho
	
		close(fd_um[1]);
		read(fd_um[0], &v1, sizeof(v1));
        
		printf("FILHO (%d) - Valor recebido pelo filho 1 antes da operação: %d\n", getpid(), v1);
		v1 = fatorial(v1);
		printf("FILHO (%d) - Valor recebido do filho 1 depois da operação: %d\n\n", getpid(), v1);

		close(fd_dois[0]);
        write(fd_dois[1], &v1, sizeof(v1));
		
	}
}

int fatorial(int n) {
	int vfat;
	if ( n <= 1 ){
		return 1;
	} else {
	vfat = n * fatorial(n - 1);
    return vfat;
	}
}

int exponencial(int n) {
	int vexp;
	if ( n < 1 ){
		return 1;
	} else {
	vexp = n * n;
    return vexp;
	}
}	