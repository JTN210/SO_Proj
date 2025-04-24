#include "mysystem.h"

// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {
	int res = -1;
	char *argv[128];
	int argc = 0;
	pid_t fork_ret;
	char *argumentos = NULL;
	char *comandos = strdup(command);
	char *cmd2 = comandos;
	if (command == NULL )
	{
		return 1;
	}
	while ((argumentos = strsep(&cmd2, " "))!= NULL)
	{
		if (*argumentos == '\0')
		{
			continue;
		}
		argv[argc] = argumentos;
		argc++;
	}
	argv[argc] = NULL;

	fork_ret = fork();
	if (fork_ret < 0)
	{
		perror("fork");
		free(comandos);
		return -1;
	}
	else if (fork_ret == 0)
	{
		execvp(argv[0],argv);
		perror("erro no exec");
		exit(1);
	}
	else
	{
		int status;
		if(waitpid(fork_ret, &status, 0) < 0)
		{
			perror("waitpid");
			free(comandos);
			return -1;
		}
		free(comandos);

		if (WIFEXITED(status))
		{
			res = WEXITSTATUS(status);
		}
		else
		{
			res = status;
		}
	}
	return res;
}