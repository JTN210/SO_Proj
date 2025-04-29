#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    mkfifo("cona", 0666);
    printf("FIFO criada\n");
    return 0;
}