// Program to illustrate the getopt()
// function in C

#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*	
*	PARA TESTAR: ./proc2_v1 ls pwd whoami hostname 
*/
int main(int argc, char *argv[])
{
	int opt;
	pid_t status;
	char command;
	
	// optind is for the extra arguments
	// which are not parsed
	for(; optind < argc; optind++){	
		status = fork();
		if(status == 0){ // será executado pelo filho
			printf("Command: %s\n", argv[optind]);
			char binaryPath[100] = "/bin/";
			strcat(binaryPath,argv[optind]);

			execl(binaryPath , argv[optind] , NULL);
		} else{ // será executado pelo pai

			int exitCodeFromChild;
			if ( waitpid(status, &exitCodeFromChild, 0) == -1 ) {
				perror("waitpid failed");
				return EXIT_FAILURE;
			}

			if ( WIFEXITED(exitCodeFromChild) ) {
				const int es = WEXITSTATUS(exitCodeFromChild);
				if (es == 0)
					printf("Executado com  sucesso.\n\n");
				else
					printf("Código de retorno = %d\n\n", es);
			}
		}
	}	
 	
	return 0;
}