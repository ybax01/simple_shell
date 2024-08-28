#include "shell.h"

/**
 * parse_command - Tokenizes a command line into arguments
 * @command: The command line to parse
 * @argv: Array to store the parsed arguments
 *
 * Return: void
 */
void parse_command(char *command, char **argv)
{
	int i = 0;
	char *token;

	token = strtok(command, " ");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL; /* Null-terminate the argument list */
}

/**
 * run_command - Forks a child process to run the command
 * @path: The full path to the executable
 * @argv: The arguments for the command
 *
 * Return: void
 */
void run_command(char *path, char **argv)
{
	pid_t pid;

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
 * execute_command - Executes a command by finding its path and running it
 * @command: The command line to execute
 *
 * Return: void
 */
void execute_command(char *command)
{
	char *argv[100];
	char *path;

	/* Parse the command into arguments */
	parse_command(command, argv);

	/* Find the full path of the command */
	path = find_executable(argv[0]);
	if (!path)
	{
		fprintf(stderr, "./shell: %s: not found\n", argv[0]);
		return;
	}

	/* Run the command */
	run_command(path, argv);
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

