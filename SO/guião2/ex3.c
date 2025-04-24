#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char** argv){
    int status;
    pid_t pid;
   
   for (int i = 0; i < 10; i++)
   {
    int res = fork();
    if((res) == 0) //codigo filho
    {
        printf("Processo:%d PID filho: %d --- PID Pai: %d \n",i+1, getpid(), getppid());
        sleep(1);
        _exit(i+1);
    
    }
    else
    { 
        pid_t terminated = wait(&status);

        if(WIFEXITED(status))
        {
        printf("Processo %d terminou com codigo de saida %d\n",terminated, WEXITSTATUS(status));

        }
    }
}
    printf("Fim\n");
    return 0;
}
