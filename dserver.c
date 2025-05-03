// "Pedido Server"

#include "dserver.h"
// gcc -o dserver dserver.c -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lglib-2.0

int main(int argc, char* argv[]){
    ID = 1;
    int fd;

    char *main_fifo = "server_pipe";

    mkfifo(main_fifo,0666);
    char inBuff[512];
    int counter = 1;
    GHashTable *tabela = g_hash_table_new(g_str_hash, g_str_equal);

    char docFolder = argv[1];
    char cache_size = argv[2];
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
                    choose_option(fifoName,strs); // escolhe a opçao e manda executar
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
/* ISTO É A PARA METER O PERSISTENCIA A CORRER MAS PRIMEIRO O GAJO TEM DE EXECUTAR O ./dclient -f
if (!persistencia(tabela))
    g_printerr("Erro ao gravar Ficheirotemp\n");
else
    g_print("Meta-informação gravada com sucesso em “%s”\n", META_FILENAME);
 */
    return 0;
}



int choose_option(char *fifo[],char** s, GHashTable *tabela) {

    int exitCode;
    if ( strcmp(s[1],"-a") == 0 )
    {
        exitCode = indexaDoc(s[2], s[3], atoi(s[4]), s[5]);
    }
    
    if ( strcmp(s[1],"-c") == 0 )
    {
       exitCode = procuraID(fifo, atoi(s[2]), tabela);
    }

    if ( strcmp(s[1],"-d") == 0 )
    {
        exitCode = removeDoc (tabela, atoi(s[2]));
    }

    if ( strcmp(s[1],"-l") == 0 )
    {
       exitCode = numeroLinhas(fifo, tabela, atoi(s[2]),(s[3]));
    }
    if ( strcmp(s[1],"-s") == 0 )
    {
        //return listaIdDocs(s[2]);
    }

    // falta dar unlink ao fifo
    return exitCode;
}