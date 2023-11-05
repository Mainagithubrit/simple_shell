#include "shell.h"

/**
  * get_index - Get index of the first occurence of char =
  * @s: String to check
  * Return: Index
  */
int get_index(char *s)
{
	int i = 0;

	if (s == NULL)
	return (0);
	while (s[i])
	{
		if (s[i] == '=')
		return (i);
		i++;
	}
	return (0);
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
void new_free(data_t *data)
{
	free(data->token);
	free(data->linearg);
	free_list(data->envp);
}

/**
 * get_dir_path - returns a path from the env
 * @envp: env pointer
 * @env: env
 * Return: dir path
*/
char *get_dir_path(list_t *envp, char *env)
{
	list_t *tmp = envp;


	while (tmp)
	{
		if (_strncmp(tmp->str, env, _strlen(env)) == 0)
			return (tmp->str + _strlen(env) + 1);
		tmp = tmp->next;
	}
	return (NULL); /*This should never be evecuted*/
}
