#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    int pid;

    for(int i=1; i<argc; i++){
        pid = atoi(argv[i]);
        if(kill(pid, SIGKILL)==-1)
            printf("Process %d not found.\n", pid);
        else
            printf("Process %d killed.\n", pid);
    }

    return 0;
}