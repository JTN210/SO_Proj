#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char** argv){
    int fdin = open("/etc/passwd", O_RDONLY);
    int fdout = open ("saida.txt", O_CREAT | O_TRUNC | O_WRONLY , 0666);
    int fderr = open ("erros.txt", O_CREAT | O_TRUNC | O_WRONLY , 0666);
    int original_fdin = dup(0);
    int original_fdout = dup(1);
    int original_fderr = dup(2);
    
    dup2(fdin , 0); close(fdin);
    dup2(fdout, 1); close(fdout);
    dup2 (fderr, 2); close(fderr);
    
    ssize_t bytes_read = 0;
    char buffer[1024];

    while ((bytes_read = read(0, buffer, sizeof(buffer))) > 0) {
        write(1, &buffer, bytes_read);
        write(2, &buffer, bytes_read);
    }
    dup2(original_fdin, 0); close(original_fdin);
    dup2(original_fdout, 1); close(original_fdout);
    dup2(original_fderr, 2); close(original_fderr);

    printf("Terminei \n");

    return 0;
}