#include "dclient.h"

int main(int argc, char* argv[]){

    if ( argc < 2 )
    {
        printf("Erro: argumentos insuficientes\n");
        printf("Uso:\n");
        printf("Adicionar documento: ./dclient -a [titulo] [autores] [ano] [path]\n");
        printf("Consultar Documento: ./dclient -c  [registo]\n");
        printf("Remover Documento: ./dclient -d [registo]\n");
        printf("Contar linhas: ./dclient -l [registo] [nome]\n");
        printf("Listar IDs: ./dclient -s [nome]\n");
        printf("Persistência: ./dclient -f\n");
        return 1;
    }

    int fd_mainFIFO = open("server_pipe", O_RDONLY);
    if (fd_mainFIFO == -1)
    {
        perror("ERRO");
    }
    write(fd_mainFIFO, "Pedido Server", 14);
    
    char str[512];
    build_message(argc, argv, str, 512);
    
    int bytesRead = 0;
    char fifoName[32];
    while ((bytesRead = read(fd_mainFIFO, &fifoName, 32)) > 0);
    if (strcmp("Pedido Inválido", fifoName) == 0)
    {
        perror("Erro no Pedido");
    }
    
    close(fd_mainFIFO);

    int fdFIFO = open(fifoName, O_WRONLY, 0666);
    write(fdFIFO, str, strlen(str));
    close(fdFIFO);

    char serverResponse[512];
    fdFIFO = open(fifoName, O_RDONLY, 0666);
    read(fdFIFO, &serverResponse, 512);
    printf("%s\n", serverResponse);
    close(fdFIFO);
}