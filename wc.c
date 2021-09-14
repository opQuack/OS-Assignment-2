#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINE_MAX 100

int main(int argc, char** argv){
    char c, str[100];
    FILE *fptr, *fptrout;

    for(int i=1; i<argc; i++){
        fptr = fopen(argv[1], "r");
        if(fptr==NULL){
            printf("File not found.\n");
        }
        else{
            int characters, words, lines, byte_count;
            characters = words = lines = byte_count = 0;
            while((c=fgetc(fptr))!=EOF){
                if(c=='\n'){
                    lines++;
                }
                else if(c==' '){
                    words++;
                    byte_count++;
                }
                else{
                    characters++;
                    byte_count++;
                }
            }
            printf("%d %d %d %d\n", characters, words, lines, byte_count);
        }
    }
    fclose(fptr);
    return 0;
}