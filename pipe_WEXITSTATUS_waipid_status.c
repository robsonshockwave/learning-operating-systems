#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 

/*
Processo Pai: Recebe dois parâmetros na inicialização. O processo pai cria dois processos filhos e envia o primeiro parâmetro para o filho 1 e o segundo para o filho 2 atravéz de mensagens (pipe).
Quando o processo filho1 retorna o resultado, o pai então soma e apresenta o resultado finalna tela.
Processo Filho 1: Recebe como mensagem (pipe) um número e faz o quadrado deste número, também através de mensagem.
Processo Filho 2: Recebe como mensagem (pipe) um número e retorna o fatorial do mesmo, também atravéz de mensagem.
*/

int fatorial(int n);
int exponencial(int n);

int main(int argc, char *argv[])
{
    int fd[2]; //File descriptors para o pipe , ele é um indicador abstrato para acessar um arquivo
	pid_t pid; //numero que o so vai retornar será armazenado aqui, se ele for negativo ocorrerá um erro
	int childStatus;
	
	int v1, v2;
	
	printf("PAI de fora - recebendo um valor para enviar pro filho 1 como parametro \nDigite um valor para fazer o fatorial do mesmo: \n");
	scanf("%d", &v1);
    printf("PAI de fora - Digite outro valor para o filho 2 fazer a exponenciação do mesmo: \n");
	scanf("%d", &v2);
	printf("\n\n--------------------------------------------------------------------------------\n\n");
    
    pipe(fd);
	
	if(fork() != 0){ //processo pai
		
		//sobre esse close: //se o pai quiser receber dados do filho, ele deve fechar fd1, e o filho deve fechar fd0. Se o pai quiser enviar dados para o filho, ele deve fechar fd0, e o filho deve fechar fd1.
		
		close(fd[0]);
        write(fd[1], &v1, sizeof(v1));
		
		waitpid(pid, &childStatus, 0); //Onde pid deve ser o PID do processo que desejamos esperar. Após a execução desta função o inteiro childStatus irá armazenar o estado do processo que estávamos esperando.
		int status;
        wait(&status); //suspende a execução do processo até a morte de seu filho. Se o filho já estiver morto no instante da chamada da primitiva (caso de um processo zumbi), a função retorna imediatamente.
		v1 = WEXITSTATUS(status); //retorna o status de saída do filho. CASO NO IF TIVER MAIS IF, ele só funcionará no primeiro IF ou no primeiro ELSE desse IF que está retornando algo
		printf("PAI  (%d) - valor recebido pelo filho 1 = %d\n\n", getpid(), v1);

		if(fork() != 0){ //processo pai
			
			close(fd[0]); //se o pai quiser receber dados do filho, ele deve fechar fd1, e a criança deve fechar fd0. Se o pai quiser enviar dados para a criança, ele deve fechar fd0, e a criança deve fechar fd1.
			write(fd[2], &v2, sizeof(v2)); // escrevendo a inteiro no pipe --- lembrando, que se fosse string não precisaria do & (e comercial)
			
			waitpid(pid, &childStatus, 0);
			printf("PAI  (%d) - valor recebido pelo filho 2 = %d\n\n", getpid(), (v2*v2));
			
		} else { //processo filho
            
			close(fd[2]);
			read(fd[0], &v2, sizeof(v2)); // lendo o inteiro no pipe
        
			printf("FILHO (%d) - Valor recebido pelo filho 2 antes da operação: %d\n", getpid(), v2);
			v2 = exponencial(v2);
			printf("FILHO (%d) - Valor recebido do filho 2 depois da operação: %d\n\n", getpid(), v2);
            
			return v2;
			exit(0);
		}
	} else { //processo filho
		close(fd[1]);
		read(fd[0], &v1, sizeof(v1));
        
		printf("FILHO (%d) - Valor recebido pelo filho 1 antes da operação: %d\n", getpid(), v1);
		v1 = fatorial(v1);
		printf("FILHO (%d) - Valor recebido do filho 1 depois da operação: %d\n\n", getpid(), v1);
        
		return v1;
		exit(0);
	}
    
    printf("PAI - a soma do filho 1 com o filho 2 tem como resultado = %d\n\n", ((v2*v2)+v1)); //xd
    return 0;
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