#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*

Under the same folder, file input.txt.
Each line contains a positive integer number and we guarantee the number is smaller than 1000.
You need to read the number in each line, add it by one, and write them line by line to another file called output.txt

NOTE: Please don't hardcode the results in your program because we change the content in input.txt when grading.

TIP: You can use sscanf to convert char array to int and sprintf to convert int to char array. 

*/
int main(){
    FILE* fd ;
    FILE* fd_1;
    char str[1000] ;

    fd = fopen("/input.txt" , "r") ;
    fd_1 = fopen("/output.txt" , "w+") ;

    for(int i = 0 ; i < 10 ; i ++){
        fscanf(fd, "%s", str) ;
        int num ;
        sscanf(str, "%d", &num) ;
        num ++ ;
        sprintf(str, "%d" , num) ;

        fprintf(fd_1, "%s", str) ;
        fprintf(fd_1, "\n") ;

    }
}