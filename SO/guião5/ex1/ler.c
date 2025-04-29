#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int fd = open("cona", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir FIFO");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        ssize_t bytesWritten = write(STDOUT_FILENO, buffer, bytesRead);
        if (bytesWritten == -1) 
        {
            perror("Erro ao escrever na FIFO");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    if (bytesRead == -1)
    {
        perror("Erro ao ler da FIFO");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return EXIT_SUCCESS;
}