#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int shell_execute(char ** args, int argc)
{
	int child_pid, wait_return, status;

	if ( strcmp(args[0], "EXIT") == 0 )
		return -1; 

	printf("argc = %d\n", argc) ;
	
	/*
	if(argc == 2){
		if(strcmp(args[0], "ls") == 0){
			char *cmd = "ls";
        	char *argv[5];
        	argv[0] = "ls";
			argv[1] = NULL ;
			execvp(cmd, argv);
		}
		else if(strcmp(args[0], "ps") == 0){
			char *cmd = "ps";
        	char *argv[5];
        	argv[0] = "ps";
			argv[1] = NULL ;
			execvp(cmd, argv);
		}
	}
	*/

	int i ;
	int count = 0 ;

	char ***argset ;

	argset[count ++] = args ;

	for(i = 0 ; i < argc ; i ++){
		if(strcmp(args[i] , "|") == 0){
			args[i] == NULL ;
			argset[count ++] = args + (i + 1) ;
		}
	}

	int fd[100][2] ;
	int ret ;

	for(i = 0 ; i < count ; i ++){
		if((ret = fork()) == 0){
			pipe(fd[i]) ;

			if(i == 0){
				close(1) ;
				dup(fd[i][1]) ;
				close(fd[i][0]) ;
				close(fd[i][1]) ; 
			}
			else if(i == count - 1){
				close(0);
				dup(fd[i][0]) ;
				close(fd[i][0]) ;
			}
			else{
				close(0) ;
				dup(fd[i][0]) ;
				close(1) ;
				dup(fd[i][1]) ;
			}

			char *cmd ;
			strcpy(cmd , argset[i][0]) ;
			execvp(cmd, argset[i]) ; 
		}
		else break ;	
	}
			
	return 0;

}
