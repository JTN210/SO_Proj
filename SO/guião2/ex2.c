#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(){
    int status;
    pid_t pid = fork();
    if((pid) == 0) //codigo filho
    {
        printf("PID filho: %d --- PID Pai: %d \n", getpid(), getppid());
        sleep(1);
        _exit(0);
    
    }
    else //codigo do pai
    {
        pid_t terminated = wait(&status);
        printf("PID Pai: %d --- PID Avô: %d --- PID Filho: %d\n", getpid(), getppid(),terminated);
        if(WIFEXITED(status))
        {
        printf("Processo %d terminou com codigo de saida %d\n",terminated, WEXITSTATUS(status));

        }
    }
    printf("Fim\n");
    return 0;
}