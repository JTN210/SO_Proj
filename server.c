#include "dserver.h"

int nPipeSigns(char *str)
{
    int counter = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '|')
            counter++;
    }
    return counter;
}

void parsing(char* fifoName, char **args)
{
    int fdFIFO = open(fifoName, O_RDONLY, 0666);

    char str[512];
    int bytesRead = read(fdFIFO, &str, 512);

    int nArgs = nPipeSigns(str);
    args[nArgs] = NULL;

    int i, j = 0 ;

    ////////// falta acabar parsing
}