#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAXARGS 64

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

pid = fork();
if (pid == -1)
{
perror("Error:");
exit(EXIT_FAILURE);
}
if (pid == 0)
{
if (execve(argv[0], argv, NULL) == -1)
{
perror("./shell");
}
exit(EXIT_FAILURE);
}
else
{
wait(&status);
}
}

/**
 * main - prints a string
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
printf("#cisfun$ ");
}
return (0);
}
