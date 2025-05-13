#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <glib.h>

#define META_FILENAME "Ficheirotemp"

extern int ID;

typedef struct Livro {
    char *title;
    char *author;
    int year;
    char *path;
    int id; // identificador único
} Livro;

int indexaDoc(GHashTable *tabela, char* title, char* authors, int year, char* path, char *fifo);

//int consultaDoc(GHashTable *tabela);

int removeDoc(GHashTable *tabela, int id);

int numeroLinhas(const char *fifo, GHashTable *tabela, int id, const char *keyword);

int choose_option(char *fifo, char** s, GHashTable *tabela);

int procuraID(char *fifo, int id, GHashTable *tabela);

int nGivenSigns(char *str, char c);

char** parsing(char* fifoName);

int persistencia(GHashTable *tabela);