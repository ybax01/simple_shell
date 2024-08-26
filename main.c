#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


/**
 * execute_command - Executes a command using execve
 * @command: The command line to execute
 *
 * Return: void
 */
void execute_command(char *command)
{
	pid_t pid;
	char *argv[100]; /* Array to hold command and arguments */
	int i = 0;
	char *token;

	token = strtok(command, " ");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL; /* Null-terminate the argument list */

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(argv[0]);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - A simple UNIX command line interpreter
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break; /* Handle Ctrl+D (EOF) */

		line[nread - 1] = '\0';

		execute_command(line);
	}

	free(line);
	return (0);
}

