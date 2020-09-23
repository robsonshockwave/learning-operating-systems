/*
Robson de Arruda Silva - 2019013624
Sistema Operacional 03/09/2020

Exercício 2
Modifique o exercício 1 para que o processo pai espere o processo filho terminar de executar antes
de começar a exibir a frase “Sou o processo pai” na tela. Para isso, você pode utilizar a função
waidpid definida no cabeçalho #include <unistd.h>. Exemplo de uso da função waitpid:
int childStatus;
waitpid(pid, &childStatus, 0);
Onde pid deve ser o PID do processo que desejamos esperar. Após a execução desta função o inteiro
childStatus irá armazenar o estado do processo que estávamos esperando. Obs.:
Antes do childStatus existe um “e comercial”.
Observação: inclua #include <sys/wait.h> para evitar warnings de declaração da função waitpid.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    
    int pid=0;
    int pidpai, pidfilho;
    int childStatus;
    pidpai = getpid();
    pid=fork();
    
    if (pid != 0){
        waitpid(pid, &childStatus, 0);
		for(int i=0; i<30; i++){
        printf( "Sou processo pai\n");
		}
    }else{
        pidfilho = getpid();
		for(int i=0; i<1000; i++){
        printf("Sou processo filho\n");
		}
    }
    
    return 0;
}