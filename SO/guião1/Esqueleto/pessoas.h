#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define bd "lista_pessoas"

typedef struct pessoas
{
    char nome[100];
    int idade;

} Pessoa;

int inserePessoa(char *nome, int idade);

int listaPessoas(int n);

int atualizaPessoa(char *nome, int idade);

int registoPessoa(int reg,int idade);