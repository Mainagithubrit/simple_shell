#include "shell.h"
/**
  * start_shell - a function that takes in command line arguments
  * @av: the agrgument array
  * @envp: the environment pasth variable
  * Return: 0
  */

void start_shell(char *av[], char *envp[])
{
	size_t n = 0;
	char *path = NULL;
	data_t data = CLEAR;

	data.av = av;
	initialize_path(&data, envp);

	path = getpath(data);
	while (1)
	{
		data.linearg = NULL;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&data.linearg, &n, stdin) == -1)
		{
			free(data.linearg);
			free_list(data.envp);
			exit(data.estatus);
		}
		data.tokens = get_tok(data.linearg);
		if (data.tokens == 0)
		{
			free(data.linearg);
			continue;
		}
		data.token = malloc(sizeof(char *) * (data.tokens + 1));
		if (data.token == NULL)
			exit(98);
		tokenize(data.linearg, data.token, data.tokens);
		if (check_builtin(&data))
		{
			free(data.token);
			free(data.linearg);
			continue;
		}
		execute(&data, path + 5, envp);
		free(data.token);
		free(data.linearg);
	}
}

/**
  * execute - a function that takes in user input and executes the command
  * @data: the command arguments
  * @path: the path of the current directory
  * @envp: environment path
  * Return: 0
  */
void execute(data_t *data, char *path, char **envp)
{
	pid_t pid;
	char *real_cmd = get_cmd(path, data->token[0]);
	int wstatus;

	if (real_cmd)
	{
		if (access(real_cmd, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(real_cmd, data->token, envp) == -1)
					exit(2);
			}
		}
		else
			perror("Permission Denied");
		wait(&wstatus);
		data->estatus = WEXITSTATUS(wstatus);
	}
	else
	{
		perr_str(data->av[0], ": ");
		perr_str("1: ", "");
		perr_str(data->token[0], ": ");
		perr_str("not found", "\n"); /* Modified */
		perr_ch(-1);
		data->estatus = 127;
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
