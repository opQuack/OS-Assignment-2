#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINE_MAX 100

char *creds[2] = {"root_user", "root"};

int main(int argc, char **argv){
    int i = 0;
    char username[LINE_MAX], password[LINE_MAX];
    do{
        if(i>0)
            printf("\n\nWrong Details!!\n\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        i++;
    } while(strcmp(username, creds[0])!=0 || strcmp(password, creds[1])!=0);
    return 0;    
}