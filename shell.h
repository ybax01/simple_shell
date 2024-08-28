#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

/* Function Prototypes */
void execute_command(char *command);
char *find_executable(const char *command);

#endif /* SHELL_H */

