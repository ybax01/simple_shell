#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * find_executable - Finds the full path of an executable command
 * @command: The command to find
 *
 * Return: Full path of the executable or NULL if not found
 */
char *find_executable(const char *command)
{
	char *path = getenv("PATH");
	char *path_copy = NULL;
	char *dir = NULL;
	char full_path[1024];
	struct stat st;

	if (command[0] == '/')
	{
		/* Command is an absolute path */
		if (access(command, X_OK) == 0)
			return (strdup(command));
		else
			return (NULL);
	}

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
