#include "dserver.h"

Livro criaLivro(char* title, char *);

Livro* addBook(Livro* LivrosList, Livro newBook)
{
    int lenList = 0;
    for (; LivrosList[lenList]; lenList++);
    Livro* newList = malloc(sizeof(Livro) * lenList + 2); // +1 para novo +1 para NULL
    for (lenList = 0; LivrosList[lenList]; lenList++)
        newList[lenList] = LivrosList[lenList];
    newList[lenList++] = newBook;
    newList[lenList] = NULL;
    return newList;
}