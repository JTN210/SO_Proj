// "Pedido Server"

#include <dserver.h>

int main(){
    int fd;

    char *main_fifo = "server_pipe";

    mkfifo(main_fifo,0666);
    char inBuff[512];
    int counter = 1;

    while (1){
        int fd = open(main_fifo, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            continue;
        }

        ssize_t n = read(fd, inBuff, sizeof(inBuff));
        if (n > 0) {
            if (!strcmp("Pedido Server", inBuff)) {
                char fifoName[32];
                int bytes = sprintf(fifoName, "client_response%d", counter);
                mkfifo(fifoName, 0666);
                counter++;

                fd = open(main,O_WRONLY);
                write(fd,fifoName,bytes);

                pid_t pid = fork();
                if (pid == 0) { // Filho
                    close(fd);
                    char **strs = parsing(fifoName);
                    execute(strs);
                    _exit(0);
                }
            }
            else{
                fd = open(main,O_WRONLY);
                perror("Pedido Inválido");
                write(fd,"Pedido Inválido",17);
            }
            
        }

        close(fd);
    }

    return 0;
}

int parsing(char fifo[],char** s) {
    
    int fd = open(fifo,O_RDONLY);

    if ( strcmp(argv[1],"-a") == 0 )
    {
        return indexaDoc(argv[2], argv[3], argv[4]), argv[5]); //atoi passa de string para inteiro, quando escreves no terminal para executar um ficheiro, aquilo é uma string,
    }
    
    if ( strcmp(argv[1],"-c") == 0 )
    {
       return consultaDoc((argv[2]));
    }

    if ( strcmp(argv[1],"-d") == 0 )
    {
        return removeDoc (atoi(argv[2]));
    }

    if ( strcmp(argv[1],"-l") == 0 )
    {
       // return numeroLinhas(atoi(argv[2]),(argv[3]));
    }
    if ( strcmp(argv[1],"-s") == 0 )
    {
        //return listaIdDocs(argv[2]);
    }
    return 0;
}