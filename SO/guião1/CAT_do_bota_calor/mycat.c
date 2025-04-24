#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];
// ISTO ESTA A LER DO STDIN PARA O STDOUT
/* int main(){
	ssize_t bytes_usados;
	while ((bytes_usados = read(STDIN_FILENO, buffer, BUFFER_SIZE)))
	{
		write(STDOUT_FILENO, buffer, bytes_usados);
	}
} */

// AGORA LER UM FICHEIRO PARA O STDOUT

int main(int argc, char *argv[])
{
	int fd = STDIN_FILENO;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if(fd == -1)
		{
			write(STDERR_FILENO,"Essa merda não existe cão\n",27);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Mete os argumentos todos burro\n");
		exit(EXIT_FAILURE);
	}
	ssize_t bytes_usados;
	while ((bytes_usados = read(fd, buffer, BUFFER_SIZE)))
	{
		write(STDOUT_FILENO, buffer, bytes_usados);
	}
	close(fd);
}	