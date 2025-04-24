#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void filho_to_pai(){

    int fd[2];
    int res = pipe (fd);
    pid_t pid = fork();
    int status;
    if(res == -1)
    {
        perror ("Erro na criação do pipe!");
    }

    if (pid == 0) //Processo Filho
    {
        close(fd[0]);
        int value = 10;
        //sleep(3);
        for (int i = 0; i < 10; i++)
        {
            res = write(fd[1],&value, sizeof(int));
            printf("%d: Processo-Filho escreveu %d bytes para o pipe\n",i, res);
        }
        close(fd[1]);
        _exit(0);

    }
    else //Processo Pai
    {
        close(fd[1]);
        int value_to_read;
        sleep(3);
        while ((res =read(fd[0],&value_to_read, sizeof(int))) > 0)
        {
            printf("Processo-Pai leu %d bytes do filho\n", res);
        }
        close(fd[0]);
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("O Filho terminou com o codigo de saida %d\n",WEXITSTATUS(status));
        }
    }
}

int main(){

    filho_to_pai();
    return 0;
}