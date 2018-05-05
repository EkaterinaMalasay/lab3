#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 1024

pid_t new_pid;

void sighndlr(int sig) {
	kill(new_pid, SIGTERM);
}

void main(void)
{
	int i = 0;
	char com[N] = {0};
	char *argv[N] = {0};
	char *pch = " ";
	int sw = 0;

	while (1) {
		write(1, ">>> ", 5);
		read(0, com, N);
		if (strcmp(com, "\n") != 0) {
			i = strcspn(com, "\n");
			com[i] = 0;
			if (strcmp(com, "exit") == 0)
				break;

			for (i = 0, pch = strtok(com, " "); pch != NULL; i++) {
				if (strcmp(pch, "&") == 0)
					sw = 1;
				else
					argv[i] = pch;
				pch = strtok(NULL, " ");
			}
			argv[N-1] = (char *) 0;

			new_pid = fork();
			if (new_pid == -1) {
				fprintf(stderr, "fork failure");
				exit(EXIT_FAILURE);
			}
			if (new_pid == 0) {
				execvp(argv[0], argv);
				exit(0);
			} else {
				int stat_val;
				(void) signal(SIGINT, sighndlr);
				if (sw == 0)
					new_pid = wait(&stat_val);
				sw = 0;
			}
		}
		memset(com, 0, N);
		memset(argv, 0, N);
	}
	exit(0);
}