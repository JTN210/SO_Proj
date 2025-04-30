#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    // Primeiro filho: ls /etc
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {
        close(fd[0]);              // não lê do pipe
        dup2(fd[1],1);             // stdout -> pipe write
        close(fd[1]);
        execlp("ls", "ls", "/etc", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    // Segundo filho: wc -l
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        _exit(0);
    }
    if (pid2 == 0) {
        close(fd[1]);               // não escreve no pipe
        dup2(fd[0], 0);             // stdin <- pipe read
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        _exit(0);
    }

    // Pai fecha ambos os lados do pipe e espera
    close(fd[0]);
    close(fd[1]);
    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }
    return 0;
}
