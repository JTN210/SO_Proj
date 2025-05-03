#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

#define META_FILENAME "Ficheirotemp"

typedef struct Livro {
    char *title;
    char *author;
    int year;
    char *path;
    int id; // identificador único
} Livro;

int indexaDoc(char *titulo, char *autores, int ano, char *path);

int consultaDoc(GHashTable *tabela);

int removeDoc(int reg);

int numeroLinhas(int reg, char *nome);

int choose_option(char fifo[],char** s);

void procuraID();

int nGivenSigns(char *str, char c);

char** parsing(char* fifoName);