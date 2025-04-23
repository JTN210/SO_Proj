#include "dclient.h"

int insereDoc(char *titulo, char *autores, int ano, char *path)
{
    Doc d;
    strcpy(d.titulo, titulo);
    strcpy(d.autores, autores);
    d.ano = ano;
    strcpy(d.path, path);

    int fd = open(bd, O_CREAT | O_WRONLY | O_APPEND, 0660);
    ssize_t bytes_escritos = write(fd, &d, sizeof(struct docs));
    printf("%ld\n", bytes_escritos);

    close(fd);

    return bytes_escritos;
}

int consultaDoc(int reg)
{
    Doc d;
    int fd = open(bd, O_RDONLY, 0600);
    
    lseek(fd, reg * sizeof(Doc), SEEK_SET);
    read(fd, &d, sizeof(Doc));
    printf("Registo: %d ---- Titulo: %s ---- Autores: %s ---- Ano: %d ---- Path: %s\n", reg, d.titulo, d.autores, d.ano, d.path);

    close(fd);
    return 0;
}

int removeDoc(int reg)
{
    Doc d;
    int fd = open(bd, O_RDWR, 0660);
    int fd2 = open(ld, O_CREAT | O_WRONLY | O_APPEND, 0660);
    
    lseek(fd, reg * sizeof(Doc), SEEK_SET);
    read(fd, &d, sizeof(Doc));
    write(fd2, &d, sizeof(Doc));

    close(fd);
    close(fd2);

    return 0;
}