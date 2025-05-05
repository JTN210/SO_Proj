#include "dserver.h"


int persistencia(GHashTable *tabela){
    const char *final = META_FILENAME;
    char temp[512];
    snprintf(temp,sizeof(temp),"%s.tmp", final);
    int fd = open(temp,O_CREAT|O_TRUNC|O_WRONLY,0.666);
    if (fd < 0)
    {
        perror("Erro");
    }
    // 2) iterador GLib 
    GHashTableIter iter;
    gpointer key, val;
    g_hash_table_iter_init(&iter, tabela);

    while (g_hash_table_iter_next(&iter, &key, &val)) 
    {
        Livro *l = (Livro*) val;
         // campos fixos
        if ((write(fd, &l->id,   sizeof l->id)   != sizeof l->id) || (write(fd, &l->year, sizeof l->year) != sizeof l->year))
        {
            close(fd);
            unlink(temp);
            return -1;
        }  
     // strings: título, autor, path
        uint32_t len;

        len = strlen(l->title) + 1;
        if (write(fd, &len, sizeof len) != sizeof len || write(fd, l->title, len) != len)
        {
            close(fd);
            unlink(temp);
            return -1;
        }

        len = strlen(l->author) + 1;
        if (write(fd, &len, sizeof len) != sizeof len || write(fd, l->author, len) != len)
        {
            close(fd);
            unlink(temp);
            return -1;
        }

        len = strlen(l->path) + 1;
        if (write(fd, &len, sizeof len) != sizeof len || write(fd, l->path, len) != len)
        {
            close(fd);
            unlink(temp);
            return -1;
        }
    }
    if(close(fd) < 0)
    {
        unlink(temp);
        return -1;
    }

    if (rename(temp,final) < 0)
    {
        unlink(temp);
        return -1;
    }

    return 0;
}

char *getTextFromFile(int fd) {
    char  buffer[512];
    size_t total = 0;
    size_t capacity = sizeof buffer;
    char  *str = malloc(capacity + 1);

    if (!str) 
        return NULL;

    ssize_t n;
    while ((n = read(fd, buffer, sizeof buffer)) > 0) {
        if ((size_t)n < sizeof buffer)
            buffer[n] = '\0';
        else
            buffer[sizeof buffer - 1] = '\0';

        // Verificação de espaço
        if (total + (size_t)n + 1 > capacity) {
            // ajuste no espaço em 2x
            size_t newcap = capacity * 2;
            while (newcap < total + (size_t)n + 1)
                newcap *= 2;
            char *tmp = realloc(str, newcap + 1);
            if (!tmp) {
                free(str);
                return NULL;
            }
            str = tmp;
            capacity = newcap;
        }

        // Copiar os bytes lidos
        memcpy(str + total, buffer, n);
        total += (size_t)n;
    }

    if (n < 0) {
        // erro no read
        free(str);
        return NULL;
    }
    str[total] = '\0';
    return str;
}

int numeroLinhas(const char *fifo, GHashTable *tabela, int id, const char *keyword)
{
    Livro *procura = g_hash_table_lookup(tabela, GINT_TO_POINTER(id));
    int fdFIFO = open(fifo, O_WRONLY, 0666);

    if (!procura)
    {
        write(fdFIFO, "Nao existe nenhum livro com esse ID\n", 37);
        return 0;
    }

    int fdLivro = open(procura->path, O_RDONLY);
    if (fdLivro < 0) {
        perror("open");
        return 0;
    }

    char *texto = getTextFromFile(fdLivro);
    close(fdLivro);
    if (!texto)
    {    
        write(fdFIFO, "Numero de linhas com essa keyword: 0\n", 38);
        return 1;
    }

    int nLinhas = 0;
    char *p = texto;
    while ((p = strstr(p, keyword)) != NULL) {
        nLinhas++;
        p += strlen(keyword);
    }

    free(texto);
    int digitosDeInt = nLinhas / 10;
    char strRetorno[37 + digitosDeInt];
    snprintf(strRetorno, sizeof strRetorno, "Numero de linhas com essa keyword: %d\n", nLinhas);
    write(fdFIFO, strRetorno, strlen(strRetorno));
    return 1;
}

int procuraID(char *fifo, int id, GHashTable *tabela)
{
    Livro *procura = g_hash_table_lookup (tabela, &(id));
    int fdFIFO = open(fifo, O_WRONLY, 0666);

    // Caso seja um indice invalido
    if (!procura)
    {
        write(fd, "ID invalido\n", 13);
        close(fdFIFO);
        return 0;
    }
    char str[512];
    int bytes_lidos = sprintf(str, "Title: %s | Author: %s | Year: %d | Path: %s\n",procura->title, procura->author, procura->year, procura->path);
    write(fd, str, bytes_lidos);
    close(fdFIFO);
    return 1;
}

int nGivenSigns(char *str, char c)
{
    int counter = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == c)
            counter++;
    }
    return counter;
}

char** parsing(char* fifoName)
{
    int fdFIFO = open(fifoName, O_RDONLY, 0666);

    char str[512];
    int bytesRead = read(fdFIFO, &str, 512);

    int nArgs = nGivenSigns(str,'|');
    char **strs = malloc(sizeof(char *) * (nArgs + 1));
    for (int i = 0; i < nArgs - 1; i++)
        strs[i] = malloc(sizeof(char) * 512);
    strs[nArgs] = NULL;

    int i = 0; // indice de str
    int j = 0; // indice das strings do char** args[k][j]
    int k = 0; // indica a string que estamos a escrever (args[k])

    while(str[i] != '\0')
    {
        if (str[i] == '|')
        {
            strs[k][j] = '\0';
            j = 0;
            k++;
        }
        else
            strs[k][j] = str[i];
        i++;
    }
    close(fdFIFO);
    return (strs);
}

int indexaDocs(GHashTable *tabela, char* title, char* authors, int year, char* path){
    Livro *novoLivro = malloc(sizeof(Livro));
    if (!novoLivro){
        perror("malloc");
        return -1;
    }
    
    novoLivro->title = strcpy(title);
    novoLivro->author = strcpy(authors);
    novoLivro->year = year;
    novoLivro->path = strcpy(path);

    if (!novoLivro->title || !novoLivro->authors || !novoLivro->path) {
        perror("strdup");
        free(novoLivro->title);
        free(novoLivro->authors);
        free(novoLivro->path);
        free(novoLivro);
        return -1;
    }

    g_hash_table_insert(tabela, ID, novoLivro);
    ID++;
    return 0;
}

int removeDoc(GHashTable *tabela, int id){
    gboolean removed = g_hash_table_remove(tabela, &id);
    if (removed) {
        printf("Document with ID %d removed successfully.\n", id);
        return 0; // Success
    } else {
        printf("Document with ID %d not found.\n", id);
        return -1; // Failure
    }
}