#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    int status;
    pid_t pid;
    int res = fork();
    if((res) == 0) //codigo filho
    {
        printf("PID filho: %d --- PID Pai: %d \n", getpid(), getppid());
        sleep(1);
        _exit(0);
    
    }
    else
    {
        printf("PID Pai: %d --- PID Avô: %d \n", getpid(), getppid());
        pid_t terminated = wait(&status);

        if(WIFEXITED(status))
        {
        printf("Processo %d terminou com codigo de saida %d\n",terminated, WEXITSTATUS(status));

        }
    }
    printf("Fim\n");
    return 0;
}