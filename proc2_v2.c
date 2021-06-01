#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *ltrim(char *s) {
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s) {
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s) {
    return rtrim(ltrim(s)); 
}

void printCommandLine(char* binaryPath, char* command, char* option, char* argument) {
	printf("Binary path: [%s] cmd: [%s] opt: [%s] arg: [%s]\n", trim(binaryPath), command, option, argument );
}

/*	
*	PARA TESTAR: ./proc2_v2 + comandos
*	Exemplos de comandos: ls | ls -l | df | df -B 512MB | hostname
*/
int main(int argc, char *argv[])
{
	int opt;
	pid_t status;
	
	if (optind > 0) {
		status = fork();

		if(status == 0){ // será executado pelo filho
			char *command = argv[optind];

			printf("Command: [%s]\n", command);

			char binaryPath[50] = "/bin/";
			strcat(binaryPath,argv[optind]);

			char option[50] = "-";
			char optionInput[50];

			while((opt = getopt(argc, argv, "B:")) != -1)
			{
				switch(opt)
				{
					case 'B':	// df -B 512MB
						sprintf(optionInput, "%c ", opt);
						printf("option: -%c: %s\n", opt, optarg);
						strcat(optionInput,optarg);
						strcat(option,optionInput);

						printCommandLine(binaryPath, command, option, "");
						execl(trim(binaryPath) , command , option , NULL);
						break;
					case '?':
						printf("option: -%c\n", optopt);
						// char option[50] = "-";
						// char optionInput[50];
						sprintf(optionInput, "%c", optopt);
						strcat(option,optionInput);

						printCommandLine(binaryPath, command, option, "");
						execl(trim(binaryPath) , command , option , NULL);
						break;
					default:
						printf("default [%c] [%c]\n",optopt, opt);
				}
			}
			
			printCommandLine(binaryPath, command, "", "");
			execl(binaryPath , command ,NULL);
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