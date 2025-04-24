#include "matrix.h"

int **createMatrix()
{

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **)malloc(sizeof(int *) * ROWS);
    for (int i = 0; i < ROWS; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++)
        {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix)
{

    for (int i = 0; i < ROWS; i++)
    {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++)
        {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void lookupNumber(int **matrix, int value, int *vector)
{

    // Encontrar as ocorrências  de um N nas linhas de uma matriz
    // Hint - use the Minfo struct from matrix.h!
    int fd[2];
    pid_t pid = fork();
    int status;
    pipe(fd);
    for (int i = 0; i < ROWS; i++)
    {

        if (pid == 0)
        {
            Minfo mf;
            mf.line_nr = i;
            mf.ocur_nr = 0;
            for (int j = 0; j < COLUMNS; j++)
            {
                if (matrix[i][j] == value)
                {
                    mf.ocur_nr++;
                }
            }
            int res = write(fd[1], &mf, sizeof(struct Minfo));
            if (res <= 0)
            {
                printf("O write deu asneira!");
            }
            close(fd[1]);
            _exit(0);
        }
    }
    Minfo mp;
    mp.line_nr = 0;
    mp.ocur_nr = 0;
    int res = 0;
    while ((res = read(fd[0], &mp, sizeof(struct Minfo))) > 0)
    {
        vector[mp.line_nr] = mp.ocur_nr;
    }
    close(fd[0]);

    for (int i = 0; i < ROWS; i++)
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("O filho %d terminou com codigo de saida %d\n", i, WEXITSTATUS(status));
        }
    }
}