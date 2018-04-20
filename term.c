#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N 1024

void main(void)
{
    int i = 0;
    char com[N] = {0};
    char com2[N] = "/bin/";
    char* argv[N] = {0};
    char *pch = " ";
    pid_t new_pid;

    while(1)
    {
        write(1, ">>> ", 5);
        read(0, com, N);
        i = strcspn(com, "\n");
        com[i] = 0;
        if(strcmp(com, "exit") == 0) break;
        strcat(com2, com);

        for(i=0, pch = strtok(com2," ");pch != NULL;i++){
            argv[i] = pch;
            pch = strtok(NULL, " ");
        }
        argv[N] = (char*) 0;

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
    }
    exit(0);
}