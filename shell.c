#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * main - prints a string
 * Return: 0
*/

int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
char *argv[2];
int status;
pid_t pid;

printf("#cisfun$ ");
while ((read = getline(&line, &len, stdin)) != -1)
{
if (read == 1)
{
printf("#cisfun$ ");
continue;
}
line[read - 1] = '\0';
argv[0] = line;
argv[1] = NULL;

pid = fork();
if (pid == -1)
{
perror("Error:");
return (1);
}
if (pid == 0)
{
if (execve(argv[0], argv, NULL) == -1)
perror("./shell");

exit(EXIT_FAILURE);
}
else
{
wait(&status);
printf("#cisfun$ ");
}
}
free(line);
return (0);
}
