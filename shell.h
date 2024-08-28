#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Function Prototypes */
void parse_command(char *command, char **argv);
void run_command(char *path, char **argv);
void execute_command(char *command);
char *find_executable(char *command);
void shell_exit(void);

#endif /* SHELL_H */
