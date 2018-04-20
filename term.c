#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N 1024

char **environ;

void main(void)
{
    int i = 0, k = 3;
    char com[N] = {0};
    char com2[N] = "/bin/";
    char* argv[2];
    pid_t new_pid;

while(k>0)
{
    write(1, ">>> ", 5);
    read(0, com, N);
    i = strcspn(com, "\n");
    com[i] = 0;
    strcat(com2, com);
    argv[0] = com2;
    argv[1] = (char*) 0;
    new_pid = 1;
    new_pid = fork();
    if (new_pid == 0){
        execv(argv[0], argv);
        exit(0);
    }
    else{
        sleep(1);
    }
    memset(com, 0, N);
    memset(com2, 0, N);
    memset(argv, 0, N);
    strcat(com2, "/bin/");
    k--;
}
    exit(0);
}