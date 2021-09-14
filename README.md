# OS-Assignment-2


#### interpreter.c
```
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
```


#### login.c
```
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
```


#### exit.c
```
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINE_MAX 100


int main(){
    printf("\n\n--------------------\nThank you for using Command Line Interpreter using C\n--------------------\n\n");
    return 0;
}
```

---

### Existing Programs

#### ls.c

```
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
```


#### kill.c
```
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
```


#### wc.c
```
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
```


#### rm.c
```
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
```


#### cat.c
```
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
```
