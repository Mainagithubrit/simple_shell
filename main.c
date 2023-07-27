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

/**
  * execute - a function that takes in user input and executes the command
  * @data: the command arguments
  * @path: the path of the current directory
  * Return: 0
  */
void execute(data_t data, char *path, char **envp)
{
	pid_t pid;
	char *real_cmd = get_cmd(path, data.token[0]);

	if (real_cmd)
	{
		if (access(real_cmd, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(real_cmd, data.token, envp) == -1)
				exit(120);
			}
		}
		else
			perror("Permission Denied");
		wait(NULL);
	}
	else
	{
		perr_str(data.av[0], ": ");
		perr_str(data.token[0], ": ");
		perr_str("command not found", "\n");
		perr_ch(-1);
	}
	free(real_cmd);
}

/**
  * tokenize - a function that tokenizes a string
  * @linearg: the arguments
  * @token: the first string to be tokenized
  * @tokens: the strings after the first to be tokenized
  * Return: 0
  */
void tokenize(char *linearg, char **token, int tokens)
{
	int i = 0;

	token[i] = _strtok(linearg, " \n");
	for (i = 1; i < tokens; i++)
		token[i] = _strtok(NULL, " \n");
	token[i] = NULL;
}

/**
  * get_tok - a funtion that takes in the token
  * @str: the string the function takes
  * Return: 0
  */
unsigned int get_tok(char *str)
{
	unsigned int count = 0, in_word = 0, i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != ' ' && str[i] != '\n') && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (str[i] == ' ' || str[i] == '\n')
			in_word = 0;
	}
	return (count);
}

/**
  * getpath - a function that gets the path of the current working directory
  * @data: the environmet path variable
  * Return: 0
  */
char *getpath(data_t data)
{
	list_t *tmp = data.envp;

	while (tmp)
	{
		if (_strncmp("PATH", tmp->str, 4) == 0)
			break;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	return (tmp->str);
}
