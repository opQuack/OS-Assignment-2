#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINE_MAX 100

// execute commands
void execCommand(char *str){
    // check for exit code.
    if(strcmp(str, "exit")==0) { char *args[] = {"./exit", NULL}; execv(args[0], args); }
    // tokenize the command string.
    int i=0;
    char *args[LINE_MAX];
    char *ch;
    ch = strtok(str, " ");
    while (ch != NULL) {
        args[i++] = ch;
        ch = strtok(NULL, " ,");
    }
    args[i++] = NULL;

    // select the function
    // 1. cat
    // 2. ls
    // 3. rm
    // 4. wc
    // 5. kill
    if(strcmp(args[0],"cat")==0){
        args[0] = "./cat";
    } else if(strcmp(args[0],"ls")==0){
        args[0] = "./ls";
    } else if(strcmp(args[0],"rm")==0){
        args[0] = "./rm";
    } else if(strcmp(args[0],"wc")==0){
        args[0] = "./wc";
    } else if(strcmp(args[0],"kill")==0){
        args[0] = "./kill";
    }
    // the child process calls the execv function
    int pt = fork();
    // execute the command
    if(pt==0){
        if(execv(args[0], args)==-1)
            printf("Command doesn't exist.");
    }
    // parent goes on hold
    if(pt>0)
        wait(NULL);
    
}

// login function
void login(){
    char *args[] = {"./login", NULL};
    int pt = fork();
    if(pt==0)
        execv(args[0], args);
    if(pt>0)
        wait(NULL);
}

// print the current working directory
void printDir(){
    char pwd[LINE_MAX];
    getcwd(pwd, sizeof(pwd));
	printf("\n$ %s ", pwd);
}

// Console code
int main(){
    printf("\n\n--------------------\nEnter login credentials\n--------------------\n\n");
    // Login
    login(); 
    // welcome text
    printf("\n\n--------------------\nWelcome to Command Interpreter using C.\n--------------------\n\n");
    // loop to simulate interpreter
    while(1){
        // print the current working directory
        printDir();
        char str[LINE_MAX];
        gets(str);
        execCommand(str);
    }
    return 0;
}