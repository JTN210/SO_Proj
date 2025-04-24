#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void pai_to_filho(){

    int fd[2];
    int res = pipe (fd);
    pid_t pid = fork();
    int status;
    if(res == -1)
    {
        perror ("Erro na criação do pipe!");
    }

    if (pid == 0) //  Processo filho
    {
        close(fd[1]);
        int value_to_read = 0;
        sleep(3);

        while((res = read(fd[0],&value_to_read, sizeof(int))) > 0) 
        {
        printf("Processo-Filho leu %d bytes do pai\n",res);
        }
        close(fd[0]);
        _exit(0);
    }
    else // Processo Pai
    {
        close(fd[0]);
        int value = 10;
        for (int i = 0; i < 1000; i++)
        {
        
        res = write(fd[1],&value,sizeof(int));
        printf("%d: Processo-Pai escreveu %d bytes para o pipe\n",i, res);
        }
        close(fd[1]);

        wait(&status);
        if (WIFEXITED(status))
        {
            printf("O Filho terminou com o codigo de saida %d\n",WEXITSTATUS(status));
        }      
    }
}


int main(){

    pai_to_filho();

    return 0;
}