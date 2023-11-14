#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAXARGS 64

/**
 * search_path - searches the PATH for the command
 * @cmd: command to search for
 * Return: full path to command
 */
char *search_path(char *cmd)
{
char *path = getenv("PATH");
char *p = strtok(path, ":");
char *fullpath = malloc(256);

while (p != NULL)
{
sprintf(fullpath, "%s/%s", p, cmd);
if (access(fullpath, X_OK) == 0)
{
return (fullpath);
}
p = strtok(NULL, ":");
}
free(fullpath);
return (NULL);
}

/**
 * read_command - reads the command from stdin
 * @argv: array of arguments
 * Return: void
 */
void read_command(char **argv)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
char *token;
int i;

read = getline(&line, &len, stdin);
if (read == -1)
{
perror("Error:");
exit(EXIT_FAILURE);
}
line[read - 1] = '\0';
i = 0;
token = strtok(line, " ");
while (token != NULL)
{
argv[i] = token;
i++;
token = strtok(NULL, " ");
}
argv[i] = NULL;
}

/**
 * execute_command - executes the command
 * @argv: array of arguments
 * Return: void
 */
void execute_command(char **argv)
{
pid_t pid;
int status;
char *fullpath;

if (strcmp(argv[0], "exit") == 0)
{
exit(EXIT_SUCCESS);
}

fullpath = search_path(argv[0]);
if (fullpath == NULL)
{
printf("./shell: No such file or directory\n");
printf("#cisfun$ ");
return;
}

pid = fork();
if (pid == -1)
{
perror("Error:");
exit(EXIT_FAILURE);
}
if (pid == 0)
{
if (execve(fullpath, argv, NULL) == -1)
{
perror("./shell");
}
exit(EXIT_FAILURE);
}
else
{
wait(&status);
printf("#cisfun$ ");
}
free(fullpath);
}

/**
 * main - simple shell
 * Return: 0
 */
int main(void)
{
char *argv[MAXARGS];

printf("#cisfun$ ");
while (1)
{
read_command(argv);
execute_command(argv);
}
return (0);
}
