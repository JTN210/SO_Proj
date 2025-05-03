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

void parsing(char* fifoName)
{
    int fdFIFO = open(fifoName, O_RDONLY, 0666);

    char str[512];
    int bytesRead = read(fdFIFO, &str, 512);

    int nArgs = nPipeSigns(str);
    char **strs = malloc(sizeof(char *) * (nArgs + 1));
    for (int i = 0; i < nArgs - 1; i++)
        strs[i] = malloc(sizeof(char) * 512);
    args[nArgs] = NULL;

    int i = 0; // indice de str
    int j = 0; // indice das strings do char** args[k][j]
    int k = 0; // indica a string que estamos a escrever (args[k])

    while(str[i] != '\0')
    {
        if (str[i] == '|')
        {
            args[k][j] = '\0';
            j = 0;
            k++;
        }
        else
            args[k][j] = str[i];
        i++;
    }
    return (args);
}