#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>



int main(){
    int fd = open("cona", O_WRONLY);
    if (fd == -1) {
        perror("Erro ao abrir FIFO");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) 
    {
        ssize_t bytesWritten = write(fd, buffer, bytesRead);
        if (bytesWritten == -1) 
        {
            perror("Erro ao escrever na FIFO");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    if (bytesRead == -1)
    {
        perror("Erro ao ler do stdin");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    unlink("cona");
    return EXIT_SUCCESS;
}