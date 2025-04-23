#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define bd "docs"
#define ld "listaDocs"

typedef struct docs
{
    char titulo[100];
    char autores[100];
    int ano;
    char path[100];
} Doc;

typedef struct docId
{
    Doc docs[100];
    
    int id;
} DocId;

int insereDoc(char *titulo, char *autores, int ano, char *path);

int consultaDoc(int reg);

int removeDoc(int reg);

int numeroLinhas(int reg, char *nome);

int listaIdDocs(char *nome);
