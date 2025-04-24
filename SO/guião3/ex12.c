#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc,char**argv){
    __pid_t pid = fork();
    int status;
    int ret = 0;
    if (pid == 0)
    {
        ret = execlp("ls", "ls","-l", NULL);  
        perror ("Bateste");
        _exit(100); 
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("O Valor de retorno é %d\n", WEXITSTATUS(status));            
        }
            
    }
    return 0;
}