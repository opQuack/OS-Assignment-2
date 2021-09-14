#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINE_MAX 100

int main(int argc, char **argv){
    int i;
    char c;
    FILE *fptr1;
    if(argc<2){
        printf("Usage of command is wrong. Refer to documentation.\n\n");
        return 0;
    }
    for(i=1; i<argc; i++){
        fptr1 = fopen(argv[i], "r");
        if(fptr1==NULL){
            printf("File does not exist.");
            break;
        }
        while((c=fgetc(fptr1))!=EOF){
            printf("%c", c);
        }
        printf("\n\n");
    }
    return 0;
}