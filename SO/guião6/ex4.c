#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    pid_t pid = fork();
    int fd [2];
    pipe(fd);
    int status;
    if (pid == 0)
    {
        close(fd[1]);

        dup2(fd[0], 0);
        close(fd[0]);

        execlp("wc", "wc", NULL); 
        _exit(0);
    }
    else
    {
        close(fd[0]);
        ssize_t bytes_read;
        char buffer[1024];
        while ((bytes_read = read(0, &buffer, 1024)) > 0) {
            write(fd[1], &buffer, bytes_read);
        }
        close(fd[1]);
    }
    pid_t terminated_pid = wait(&status);
    if (WIFEXITED(status)) 
    {
        printf("O filho %d terminou com codigo de saida %d\n", terminated_pid, WEXITSTATUS(status));
    }
    return 0;
} 