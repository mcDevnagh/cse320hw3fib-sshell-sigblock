#include "error_checking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	if (argc != 2){
		fprintf(stderr, "Invalid Arguments\n");
		exit(EXIT_FAILURE);
	}

	int fib[60] = 
	{0, 1, 1, 2, 3, 5, 8, 3, 1, 4, 5, 9, 4, 3, 7, 0, 7, 7, 4, 1, 5, 6, 1, 7, 8, 5, 3, 8, 1, 9, 0, 
		9, 9, 8, 7, 5, 2, 7, 9, 6, 5, 1, 6, 7, 3, 0, 3, 3, 6, 9, 5, 4, 9, 3, 2, 5, 7, 2, 9, 1};

	long long n = atoll(*++argv);
	if (n == 9223372036854775807 && strcmp(*argv, "9223372036854775807")){
		fprintf(stderr, "Error: Number too large (n > 9223372036854775807)\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	if ((pid = Fork()) == 0)
		exit(fib[n % 60]);
	
	int status;	
	if (waitpid(pid, &status, 0) < 0){
		fprintf(stderr, "Error reaping child\n");
	}
	if (WIFEXITED(status))
		printf("%d\n", WEXITSTATUS(status));
	else
		fprintf(stderr, "Error: Child did not exit properly\n");

	exit(0);
}
