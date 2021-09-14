#include<stdio.h>
#include<dirent.h>

int main(int argc, char **argv){
  DIR *p; // directory to be searched.
  struct dirent *files;

  for(int i=1; i<argc; i++){
    p=opendir(argv[i]);
    // directory doesn't exist.
    if(p==NULL){
      printf("Directory doe not exist.\n");
      return 0;
    }
    // print output to console
    while((files=readdir(p))!=NULL)
      printf("%s\n", files->d_name);
    printf("\n\n");
  }
  return 0;
}