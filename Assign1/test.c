#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


int goforking(){
    int ret ;
    if((ret = fork()) > 0){
        sleep(2) ;
        return 10 ;
    }
    else{
        return -10 ;
    }
}

int main(){
    char *cmd;
    char *argv[3];
	int fd1;

    while(1){
        scanf("%d" , &fd1) ;
        if(fd1 == 0) break ;
        cmd = "ls";
        argv[0] = "ls";    
	    argv[1] = "-l";     
	    argv[2] = NULL;
	    execvp(cmd, argv);
    } 

	return 1;
}