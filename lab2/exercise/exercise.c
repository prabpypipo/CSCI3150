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
    int fd_1 , fd_2 ;
    char str[1000] ;

    fd_1 = open("input.txt", O_RDONLY, S_IRUSR | S_IWUSR ) ;
    fd_2 = open("output.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR ) ;

    read(fd_1, str, 100) ;
    int a[15] ;

    sscanf(str, "%d %d %d %d %d %d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8], &a[9]) ;
    sprintf(str, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d", a[0] + 1, a[1] + 1, a[2] + 1, a[3] + 1, a[4] + 1, a[5] + 1, a[6] + 1, a[7] + 1, a[8] + 1, a[9] + 1) ;

    write(fd_2, str, strlen(str)) ;

    close(fd_1) ;
    close(fd_2) ;
}