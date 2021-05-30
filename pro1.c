#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void ler(int fd, int filho)
{
  char c;
  int first = 1;

  do {
    if (!read(fd, &c, 1))
      break;
    if (first) {
      printf("%s recebe:", (filho) ? "Filho" : "Pai");
      first = 0;
    }
    putchar(c);
  } while (c != '\n');
}


void escrever(int fd, const char * msg, int filho)
{
  write(fd, msg, strlen(msg));
  printf("%s envia:%s", (filho) ? "Filho" : "Pai", msg);
}


int main(void)
{
    int status, id, j;
    
    int filho_to_pai[2];
    int pai_to_filho[2];

    pipe(filho_to_pai);
    pipe(pai_to_filho);
    
    // Insira um comando para pegar o PID do processo corrente e mostre na tela da console.
    
    // variável para armazenar o id do processo da função de chamada 
	pid_t process_id ; 
	// variável para armazenar o id do processo da função pai 
	pid_t p_process_id ;

	// getpid () - retornará a id do processo de chamada da função 
	process_id = getpid(); 
	// getppid () - retornará o id do processo da função pai 
//	p_process_id = getppid();

	// imprimindo o id do processo  
	printf("MAIN: O pid do processo corrente: % d \n" , process_id ); 
	
    //if (*** insira um comando para criar um subprocesso) {
    status = fork();
    if (status != 0){
        // ***** Faça com que o processo pai execute este trecho de código
        // ***** Mostre na console o PID do processo pai e do processo filho
        printf("PAI:  O pid do processo pai: % d \nPAI: O pid do processo filho: % d \n" , process_id, status );
        
        // ***** Monte uma mensagem e a envie para o processo filho

        // ***** Mostre na tela o texto da mensagem enviada

        // ***** Aguarde a resposta do processo filho

        // ***** Mostre na tela o texto recebido do processo filho

        // ***** Aguarde mensagem do filho e mostre o texto recebido

        //  ***** Aguarde o término do processo filho

        // ***** Informe na tela que o filho terminou e que o processo pai também vai encerrar
        close(pai_to_filho[0]);
        close(filho_to_pai[1]);

        escrever(pai_to_filho[1], "hello\n", 0);
        ler(filho_to_pai[0], 0);
        pid_t childPid = wait(NULL);
        printf("Filho terminou [%d], vou terminar também [%d]\n",childPid,process_id);
    }
    else{        
        // ***** Faça com que o processo filho execute este trecho de código

        // ***** Mostre na tela o PID do processo corrente e do processo pai
        process_id = getpid();
        p_process_id = getppid();
        printf("FILHO: O pid do processo corrente: % d \nFILHO:  O pid do processo pai: % d \n" , process_id, p_process_id ); 
        
        // ***** Aguarde a mensagem do processo pai e ao receber mostre o texto na tela
        // ***** Envie uma mensagem resposta ao pai
        close(pai_to_filho[1]);
        close(filho_to_pai[0]);
        ler(pai_to_filho[0], 1);
        escrever(filho_to_pai[1], "hi\n", 1);

        // ***** Execute o comando “for” abaixo
        for (j = 0; j <= 10000; j++);
            // ***** Envie mensagem ao processo pai com o valor final de “j”
            char snum[5];
            sprintf(snum, "%d", j);
            strcat(snum,"\n");
            escrever(filho_to_pai[1], snum, 1);
            
            // ***** Execute o comando abaixo e responda às perguntas
             execl("/bin/ls", "ls", NULL);
            
            // ***** O que acontece após este comando?
            // ***** O que pode acontecer se o comando “execl” falhar?

    }

    exit(0);
}
