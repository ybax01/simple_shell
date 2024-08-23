#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define PROMPT "#cisfun$ "

/* Function prototypes */
void execute_command(char *line);

/**
 * main - Simple UNIX command line interpreter
 *
 * Description: This shell waits for a command, executes it if found,
 * and handles errors. It repeats until the user exits or inputs Ctrl+D.
 *
 * Return: 0 on success, or an error code on failure.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf(PROMPT);
		read = getline(&line, &len, stdin);
		if (read == -1) /* Check for end-of-file condition (Ctrl+D) */
		{
			free(line);
			break;
		}

		line[read - 1] = '\0'; /* Replace newline character with null terminator */

		if (strlen(line) == 0) /* Skip empty input */
			continue;

		execute_command(line);
	}

	return (0);
}

/**
 * execute_command - Executes the given command
 * @line: The command to execute
 */
void execute_command(char *line)
{
	char *argv[2];
	pid_t pid;
	int status;

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) /* Child process */
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		wait(&status);
	}
}

