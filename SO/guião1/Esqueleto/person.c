#include "pessoas.h"

int inserePessoa(char *nome, int idade)
{

    Pessoa p;
    p.idade = idade;
    strcpy(p.nome, nome);

    int fd = open(bd, O_CREAT | O_WRONLY | O_APPEND, 0660);
    ssize_t bytes_escritos = write(fd, &p, sizeof(Pessoa));
    printf("%ld\n", bytes_escritos);

    close(fd);

    return bytes_escritos;
}

int listaPessoas(int n)
{
    Pessoa p;

    int fd = open(bd, O_RDONLY, 0600);
    
    for (int r = 0; r < n && read(fd, &p, sizeof(Pessoa)) > 0; r++)
    {
        printf("Registo: %d ---- Nome: %s ---- idade: %d\n", r, p.nome, p.idade);
    }

    close(fd);
    return 0;
}

int atualizaPessoa(char *nome, int idade)
{

    Pessoa p;
    int fd = open(bd, O_RDWR, 0660);
    while (read(fd, &p, sizeof(Pessoa)))
    {
        if (strcmp(p.nome, nome) == 0)
        {
            lseek(fd, -sizeof(int), SEEK_CUR);
            p.idade = idade;
            write(fd, &p.idade, sizeof(int));
        }
    }

    close(fd);
    return 0;
}

int registoPessoa(int reg, int idade)
{
    int fd = open(bd, O_RDWR, 0666);
    int pos = (reg + 1) * sizeof(Pessoa);

    lseek(fd, pos - sizeof(int), SEEK_SET);
    write(fd, &idade, sizeof(int));
    // return 0;

    // int res = lseek(fd, reg*sizeof(Pessoa), SEEK_CUR);

    // while (read(fd, &p, sizeof(Pessoa)))
    // {
    //     if ( res == reg)
    //     {
    //         lseek(fd, -sizeof(int), SEEK_CUR);
    //         p.idade = idade ;
    //         write(fd, &p.idade, sizeof(int));
    //     }
    // }

    close(fd);
    return 0;
}