#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define MAX_COMMANDS 10

// parse the argument and execvp
// returns the result of exec
int exec_command(char* arg){

	//We are assuming a maximum number of arguments of 10.
	//This could be improved with realloc, for example.
	char *exec_args[10];
	int args_count = 0;
	int exec_ret = 0;

	char *token, *string, *tofree;

	tofree = string = strdup(arg);
	assert(string != NULL);

	while ((token = strsep(&string, " ")) != NULL) {
		exec_args[args_count]=token;
		args_count++;
	}
	exec_args[args_count]=NULL;

	exec_ret=execvp(exec_args[0],exec_args);

	perror("Exec error");

    free(tofree);

	return exec_ret;
}


int main(int argc, char** argv){

	int number_of_commands=4;
	char * commands[] = {
		"grep -v ^# /etc/passwd",
		"cut -f7 -d:",
		"uniq",
		"wc -l"
	};
	pid_t pids[number_of_commands];
	int fd[number_of_commands-1][2];
	for (int i = 0; i < number_of_commands; i++) {
		if (i == 0) 
		{
			pipe(fd[i]);
			switch (fork())
			{
			case 0:
				close(fd[i][0]);        // não lê do pipe
				dup2(fd[i][1], 1); // stdout -> pipe write
				close(fd[i][1]);   // close read end
				exec_command(commands[i]);
				_exit(0);
			default:
				close(fd[i][1]);        // não escreve no pipe
			}
		} 
		else if (i == (number_of_commands - 1)) 
		{
			switch (fork())
			{
			case 0:
				//close(fd[i - 1][1]);    não é necessario
				dup2(fd[i - 1][0], 0); // stdin <- pipe read
				close(fd[i - 1][0]);   // close read end
				exec_command(commands[i]);
				_exit(0);
			default:
				close(fd[i - 1][0]);        // não lê do pipe
			}
		} 
		else
		{
			pipe(fd[i]);
			switch (fork())
			{
			case 0:
				close (fd[i][0]);   
				dup2(fd[i][1], 1); 
				close(fd[i][1]); 
				//pipe i-1
				// close(fd[i - 1][1]);  
				dup2(fd[i - 1][0], 0); 
				close(fd[i - 1][0]);  
				exec_command(commands[i]);
				_exit(0);
			default:
				close(fd[i][1]);        // não escreve no pipe
				close(fd[i - 1][0]);   // não lê do pipe
			}
		} 
	}
	for (int i = 0; i < number_of_commands; i++)
	{
		wait(NULL);
	}
	
	return 0;
}
