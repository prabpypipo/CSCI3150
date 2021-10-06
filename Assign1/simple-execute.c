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

	//printf("aargc == %d\n" , argc) ;

	int i ;
	int count = 0 ;

	char ** argset[100] ;
	pid_t pid ;

	argset[count] = & args[0] ;
	count ++ ;

	for(i = 0 ; i < argc - 1 ; i ++){
		if(strcmp(args[i] , "|") == 0){
			args[i] = NULL ;
			argset[count] = & args[i + 1] ;
			count ++ ;
		}
	}


	int fd[100][2] ;
	int ret, re ;

	//printf("count = %d\n" , count) ;

	if(count == 1){
		if((ret = fork()) == 0){
			execvp(argset[0][0], argset[0]) ; 
		}
		else{
			pid = wait(&status);
			return 0 ;
		}
	}
	if((re = fork()) == 0){
		for(i = 0 ; i < count - 1 ; i ++){
			//printf("i = %d\n" , i) ;
			pipe(fd[i]) ;
			if((ret = fork()) == 0){

				if(i == 0){
					close(1) ;
					dup(fd[i][1]) ;
				}
				else{
					close(0) ;
					dup(fd[i - 1][0]) ;

					close(1) ;
					dup(fd[i][1]) ;
				}

				int j ;
				for(j = 0 ; j <= i ; j ++){
					close(fd[j][0]) ;
					close(fd[j][1]) ;
				}

				execvp(argset[i][0], argset[i]) ;
			}
		}

		//for i == count - 1
		close(0) ;
		dup(fd[count - 2][0]) ;
		int j ;
		for(j = 0 ; j < count - 1 ; j ++){
			close(fd[j][0]) ;
			close(fd[j][1]) ;
		}

		execvp(argset[count - 1][0], argset[count - 1]) ;
	}
	else{
		pid = wait(&status) ;
	}

	return 0 ;
}
