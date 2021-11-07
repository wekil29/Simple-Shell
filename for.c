
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
# include <string.h>

int main(int argd, char* argv[]){

  // print welcome prompt
    
    printf("++++++++++++++ Welcome to My shell!    +++++++++++++++++\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++!\n");
    fork();
    printf("%s ", getuid() == 0 ? "#" :"$");
 
    int pip[2];
    if(pipe(pip)==-1){
        return 1;    
    }
    pid_t pid1=fork();
    if(pid1<0)
        return 2;
       
    char* arg[]={"ls","-l",NULL}; 
 
   char* cmd1[]={"grep","^d", NULL};
   // char* cmd1[]={"sort","-r", NULL};
  //  char* cmd1[]={">","out.f", NULL};

    
//    char *word[3];
//  
//    for(int i=0;i<2;i++)
//    {
//        scanf("%s",word[i]);
//    }
//    word[3]=NULL;    
    
    if(pid1==0){
        //child proces
        dup2(pip[1],STDOUT_FILENO);
        close(pip[0]);
        close(pip[1]);
        execvp(arg[0],arg);
            
    }
    pid_t pid2=fork();
    if(pid2<0){
          return 3;  
    }
     if(pid2==0){
          dup2(pip[0],STDIN_FILENO);
          close(pip[0]);
          close(pip[1]);
          execvp(cmd1[0],cmd1);
       }
        // built-in: exit
        if (strcmp("exit", cmd1[0]) == 0) 
            return 0;

    
    close(pip[0]);
    close(pip[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
     
}

