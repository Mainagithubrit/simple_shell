#include "shell.h"

/**
  * check_builtin - a funtion that checks if user input is builtin
  * @data: the list of arguments taken
  * Return: 0
  */
int check_builtin(data_t *data)
{
	builtin list[] = {
		{"exit", exit_shell},
		{"env", env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd},
		{NULL, NULL}
		};
		int i = 0;

	while (list[i].arg)
	{
		if (_strcmp(data->token[0], list[i].arg) == 0)
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
void exit_shell(data_t *data)
{
	int status;

	if (data->tokens > 2)
	{
		perr_str(data->token[0], "\n");
		perr_str(data->av[0], ": ");
		perr_str("exit: too many arguments\n", "");
		perr_ch(-1);
		return;
	}
	if (data->tokens == 2)
	{
		if (is_number(data->token[1]))
		{
			status = _atoi(data->token[1]);
		}
		else
		{
			perr_str(data->av[0], ": 1: exit: Illegal number: ");
			perr_str(data->token[1], "\n");
			perr_ch(-1);
			status = 2;
		}
		new_free(data);
		exit(status);
	}
	/* p_str(data.token[0], "\n"); */
	/* p_ch(-1); */
	new_free(data);
	exit(data->estatus);
}
/**
 * _setenv - Handle the commade setenv
 * @data: data
 */
void _setenv(data_t *data)
{
	list_t *env = data->envp;
	list_t *tmp;
	int idx = 0;
	char *value;

	if (data->tokens != 3)
	{
		perr_str("Invalid number of argument\n", "");
		perr_ch(-1);
		return;
	}
	tmp = env;

	value = malloc(_strlen(data->token[1]) + _strlen(data->token[2]) + 2);
	_strcpy(value, data->token[1]);
	_strcat(value, "=");
	_strcat(value, data->token[2]);

	while (tmp)
	{
		idx = get_index(tmp->str);

		if (_strncmp(tmp->str, data->token[1], idx) == 0)
		{
			/* Free the memory for the initial string */
			free(tmp->str);
			/*Make the struct sting point to the new string */
			tmp->str = value;
			return;
		}
		tmp = tmp->next;
	}
	/*If variable does not exit. Add a new node to the envrionment */
	add_node_end(&env, value);
	free(value);
}

/**
 * _unsetenv - unset an environmental variable
 * @data: data
 */

void _unsetenv(data_t *data)
{
	list_t *tmp = data->envp, *prev = NULL;
	int idx, i = 0;

	if (data->tokens != 2)
	{
		perr_str("Invalid number of arguments\n", "");
		perr_ch(-1);
		return;
	}

	while (tmp)
	{
		idx = get_index(tmp->str);

		if (_strncmp(tmp->str, data->token[1], idx) == 0)
		{
			if (i == 0)
			{
				data->envp = tmp->next;
				free(tmp->str);
				free(tmp);
			}
			else
			{
				prev->next = tmp->next;
				free(tmp->str);
				free(tmp);
			}
			return;
		}

		i++;
		prev = tmp;
		tmp = tmp->next;
	}


	perr_str(data->token[1], "is not a valid environment variable\n");
	perr_ch(-1);
}
