// "Pedido Server"

#include "dserver.h"

int ID;

int main(int argc, char* argv[]){
    int ID = 1;
    int fd;

    char *main_fifo = "server_pipe";

    mkfifo(main_fifo,0666);
    printf("Criei fifo inicial!\n");
    char inBuff[512];
    int counter = 1;
    GHashTable *tabela = g_hash_table_new(g_int_hash, g_int_equal);

    //char docFolder = argv[1];
    //char cache_size = argv[2];
    while (1){
        printf("ID = %d\n", ID);
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
                int codeSaida = choose_option(&(fifoName[0]),strs,&tabela, &ID); //GHash **tabela
                printf("Voltou ao loop\n");
                for (int i = 0; strs[i]; i++)
                    free(strs[i]);
                free(strs);
                _exit(codeSaida); // escolhe a opçao e manda executar
            }
        }
        close(fd);
    }
    for (int i = 1; i <= ID; i++)
    {
        wait(NULL);
        char buffer[32];
        sprintf(buffer, "client_response%d", i);
        unlink(buffer);
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



int choose_option(char *fifo, char** s, GHashTable **tabela, int *ID) {
    printf("Option:%s\n",s[0]);
    int exitCode;
    if((sizeof(s[0]) == (sizeof('-')*2))){
        switch (s[0][1])
        {
            case 'a':
                exitCode = indexaDoc(tabela, s[1], s[2], atoi(s[3]), s[4], fifo, ID);
                printf("Dentro do choose_option o ID = %d\n", *ID);
                break;
            
            case 'c':
                exitCode = procuraID(fifo, atoi(s[1]), tabela);
                break;
            
            case 'd':
                exitCode = removeDoc(tabela, atoi(s[1]));
                break;
            
            case 'l':
                exitCode = numeroLinhas(fifo, tabela, atoi(s[1]), s[2]);
                break;
            
            case 's':
                // exitCode = listaIdDocs(s[1], tabela, fifo);
                break;
            
            default:
                //Inválido
                break;
        }
    }

    unlink(fifo);
    return exitCode;
}