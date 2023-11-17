#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAXARGS 64

char *search_path(char *cmd);
void read_command(char **argv);
void print_env(void);
void execute_command(char **argv);

#endif
