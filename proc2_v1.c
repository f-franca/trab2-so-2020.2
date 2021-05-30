// Program to illustrate the getopt()
// function in C

#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*	ME DELETE !!!!
*	PARA TESTAR: ./proc2_v1 -i -f file.txt -lr -x 'hero' -a -b -f
*/
int main(int argc, char *argv[])
{
	int opt;
	
	// put ':' in the starting of the
	// string so that program can
	//distinguish between '?' and ':'
	while((opt = getopt(argc, argv, ":f:ilrx")) != -1)
	{
		switch(opt)
		{
			case 'i':
			case 'l':
			case 'r':
				printf("option: %c\n", opt);
				break;
			case 'f':
				printf("filename: %s\n", optarg);
				break;
			case ':':
				printf("option -%c needs a value\n",optopt);
				break;
			case '?':
				printf("unknown option: -%c\n", optopt);
				break;
		}
	}
	
	// optind is for the extra arguments
	// which are not parsed
	for(; optind < argc; optind++){	
		printf("extra arguments: %s\n", argv[optind]);
	}
	
	return 0;
}

