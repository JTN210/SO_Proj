// "Pedido Server"

#include "dserver.h"
// gcc -o dserver dserver.c -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lglib-2.0

int ID;

int main(int argc, char* argv[]){
    ID = 1;
    int fd;

    char *main_fifo = "server_pipe";

    mkfifo(main_fifo,0666);
    printf("Criei fifo inicial!\n");
    char inBuff[512];
    int counter = 1;
    GHashTable *tabela = g_hash_table_new(g_int_hash, g_int_equal);

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
            printf("Recebemos pedido de criação de fifo\n");
            char fifoName[32];
            int bytes = sprintf(fifoName, "client_response%d", counter);
            mkfifo(fifoName, 0666);
            counter++;

            fd = open(main_fifo,O_WRONLY);
            write(fd,fifoName,bytes);

            pid_t pid = fork();
            if (pid == 0) { // Filho
                printf("Filho criado\n");
                close(fd);
                char **strs = parsing(&(fifoName[0]));
                int codeSaida = choose_option(&(fifoName[0]),strs,tabela);
                for (int i = 0; strs[i]; i++)
                    free(strs[i]);
                free(strs);
                _exit(codeSaida); // escolhe a opçao e manda executar
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
    close(main_fifo);
    return 0;
}



int choose_option(char *fifo, char** s, GHashTable *tabela) {
    printf("Option:%s\n",s[0]);
    int exitCode;
    if ( strcmp(s[0],"-a") == 0 )
    {
        exitCode = indexaDoc(tabela,s[1], s[2], atoi(s[3]), s[4], fifo);
    }
    
    if ( strcmp(s[0],"-c") == 0 )
    {
       exitCode = procuraID(fifo, atoi(s[1]), tabela);
    }

    if ( strcmp(s[0],"-d") == 0 )
    {
        exitCode = removeDoc (tabela, atoi(s[1]));
    }

    if ( strcmp(s[0],"-l") == 0 )
    {
       exitCode = numeroLinhas(fifo, tabela, atoi(s[1]),(s[2]));
    }
    if ( strcmp(s[0],"-s") == 0 )
    {
        //exitCode = listaIdDocs(s[1], tabela, fifo);
    }

    unlink(fifo);
    return exitCode;
}