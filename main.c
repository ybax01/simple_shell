#include "shell.h"

/**
 * execute_command - Executes a command using execve
 * @command: The command line to execute
 *
 * Return: void
 */
void execute_command(char *command)
{
	pid_t pid;
	char *argv[100];
	int i = 0;
	char *token;
	char *path;

	/* Tokenize the command line into command and arguments */
	token = strtok(command, " ");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL; /* Null-terminate the argument list */

	/* Find the full path of the command */
	path = find_executable(argv[0]);
	if (!path)
	{
		fprintf(stderr, "./shell: %s: not found\n", argv[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror(argv[0]);
		}
		free(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		free(path);
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

		line[nread - 1] = '\0'; /* Remove newline character */

		execute_command(line);
	}

	free(line);
	return (0);
}

