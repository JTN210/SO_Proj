#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
pid_t fork_ret;
int status;
int pids[N];
for (int i = 0; i < N; i++)
{
	fork_ret = fork();

	if (fork_ret == 0)
	{
		int counter = 0;
		int res = 1;
		while (res > 0)
		{
			res = mysystem(commands[i]);
			counter++;
		}
		_exit(counter);
	}
	else
	{
		pids[i] = fork_ret;
	}
}

for (int i = 0; i < N; i++) {
	waitpid(pids[i], &status, 0);
	if (WIFEXITED(status)) {
		printf("%s %d\n", commands[i], WEXITSTATUS(status));
	}
}

}

int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	return 0;
}