#include "pessoas.h"

int main(int argc, char* argv[]){

    if ( argc < 3 )
    {
        printf("Usage:\n");
        printf("Add new person: ./pessoas -i [name] [age]\n");
        printf("List N persons: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return 1;
    }

    if ( strcmp(argv[1],"-i") == 0 )
    {
        return inserePessoa(argv[2], atoi(argv[3])); //atoi passa de string para inteiro, quando escreves no terminal para executar um ficheiro, aquilo é uma string, como o inserePessoa recebe um inteiro tens de passar para inteiro
    }

    if ( strcmp(argv[1],"-l") == 0 )
    {
       return listaPessoas(atoi(argv[2]));
    }

    if ( strcmp(argv[1],"-u") == 0 )
    {
        return atualizaPessoa(argv[2], atoi(argv[3]));
    }

    if ( strcmp(argv[1],"-o") == 0 )
    {
        return registoPessoa(atoi(argv[2]),atoi(argv[3]));
    }

    return 0;
}

