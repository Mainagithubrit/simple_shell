#include "shell.h"

/**
 * main - start the shell
 * @ac: argument count
 * @av: argument vector
 * @envp: environmental variable
 * Return: An int determined by the exit status
 */
int main(__attribute__((unused))int ac, char *av[], char *envp[])
{
	start_shell(av, envp);

	return (0);
}


