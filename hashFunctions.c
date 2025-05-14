#include "dserver.h"

Livro criaLivro(char* title, char *);

Livro **append_livro(Livro **array, size_t *n, Livro *novo) 
{
    Livro **tmp = realloc(array, (*n + 1) * sizeof(Livro*));
    if (!tmp) {
        /* falha no realloc: array original fica válido */
        return array;
    }
    /* armazena o novo livro e atualiza o contador */
    tmp[*n] = novo;
    (*n)++;
    return tmp;
}