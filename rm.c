#include <stdio.h>

int main(int argc, char **argv){
    for(int i=1; i<argc; i++){
        char *cur_file = argv[i];
        if(remove(cur_file)==0){
            printf("\nFile %s has been deleted.\n", cur_file);
        } else{
            printf("\nFile %s does not exist.\n", cur_file);
        }
    }
    return 0;
}