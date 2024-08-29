#include "shell.h"

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
		if (nread == -1) /* Handle Ctrl+D */
			break;

		line[nread - 1] = '\0'; /* Remove newline character */

		/* Exit the shell */
		if (strcmp(line, "exit") == 0)
			break;

		execute_command(line);
	}

	free(line);
	return (0);
}

/**
 * execute_command - Executes a command
 * @command: Command to execute
 */
void execute_command(char *command)
{
	char *argv[2];
	char *exec_path;
	pid_t pid;
	int status;

	argv[0] = command;
	argv[1] = NULL;

	exec_path = find_executable(command);
	if (exec_path == NULL)
	{
		fprintf(stderr, "./hsh: %s: not found\n", command);
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
		if (execve(exec_path, argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(exec_path);
}

/**
 * find_executable - Finds the full path of a command
 * @command: Command to find
 *
 * Return: Full path to command if found, NULL otherwise
 */
char *find_executable(char *command)
{
	if (access(command, X_OK) == 0)
		return (strdup(command));
	return (NULL);
}

