#include "shell.h"

void exit_shell(struct shell_data);
void _setenv(data_t data);
void env(struct shell_data data);

/**
  * check_builtin - a funtion that checks if user input is builtin
  * @data: the list of arguments taken
  * Return: 0
  */
int check_builtin(data_t data)
{
	builtin list[] = {
		{"exit", exit_shell},
		{"env", env},
		{"setenv", _setenv},
		/*{"unsetenv", _unsetenv}, */
		{NULL, NULL}
		};
		int i = 0;

	while (list[i].arg)
	{
		if (_strcmp(data.token[0], list[i].arg) == 0)
		{
			list[i].ptr(data);
			break;
		}
		i++;
	}
	if (list[i].arg == NULL)
		return (0);
	return (1);
}

/**
  * exit_shell - a function that takes in the exit command and terminates
  * @data: the list of arguments it takes
  * Return: 0
  */
void exit_shell(data_t data)
{
	int status;

	if (data.tokens > 2)
	{
		perr_str(data.token[0], "\n");
		perr_str(data.av[0], ": ");
		perr_str("exit: too many arguments\n", "");
		perr_ch(-1);
		return;
	}
	if (data.tokens == 2)
	{
		if (is_number(data.token[1]))
		{
			status = _atoi(data.token[1]);
			p_str(data.token[0], "\n");
			p_ch(-1);
		}
		else
		{
			perr_str(data.token[0], "\n");
			perr_str(data.av[0], ": ");
			perr_str("exit: ", data.token[1]);
			perr_str(": ", "numeric argument required\n");
			perr_ch(-1);
			status = 2;
		}
		new_free(data);
		exit(status);
	}
	p_str(data.token[0], "\n");
	p_ch(-1);
	new_free(data);
	exit(0);
}

/**
  * is_number - a function that checks if the command input is a number
  * @s: the command to be checked
  * Return: 0
  */
int is_number(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/**
 * new_free - Free some block of memory
 * @data: data where memory is stored
 */
void new_free(data_t data)
{
	free(data.token);
	free(data.linearg);
	free_list(data.envp);
}
