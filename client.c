#include "dclient.h"

void build_message(int argc, char *argv[],char *message, size_t message_size){
    size_t k = 0;
    for (int i = 1; i < argc && i < 6; i++) {
        char *p = argv[i];

        while (*p && k + 1 < message_size) 
        {
            message[k++] = *p++;
        }   

        if (i < 5 && k + 1 < message_size) 
        {
            message[k++] = '|';
        }
    }

    if (message_size > 0) 
    {
        message[k < message_size ? k : message_size - 1] = '\0';
    }
}
int indexaDoc(char *titulo, char *autores, int ano, char *path)
{
}

int consultaDoc(int reg)
{
}

int removeDoc(int reg)
{
}       
int numeroLinhas(int reg, char *nome)
{
}
int listaIdDocs(char *nome)
{
}