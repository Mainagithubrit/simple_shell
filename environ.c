#include "shell.h"
/**
  * env - a function that handles the environment env
  * @data: data containing envrionment
  */

void env(data_t *data)
{
	list_t *list = data->envp;

	while (list)
	{
		p_str(list->str, "\n");
		list = list->next;
	}
	p_ch(-1);
}

/**
  * initialize_path - a funtion that initializes the path variable
 * @data: a list of arguments
 * @envp: the path environment
 */
void initialize_path(data_t *data, char **envp)
{
	list_t *list = NULL;
	int i = 0;

	while (envp[i])
		add_node_end(&list, envp[i++]);

	data->envp = list;
}
/**
  * add_node_end - a function that adds a node at the
  * end of a singly linked list
  * @head: the head of the sinly linked list
  * @str: the string to be added
  * Return: 0
   */

void add_node_end(list_t **head, char *str)
{
	list_t *ptr = NULL;
	list_t *temp = NULL;


	ptr = malloc(sizeof(list_t));
	if (ptr == NULL)
		exit(129); /* Cannot allocate memory */
	ptr->str = _strdup(str);
	if (ptr->str == NULL)
	{
		free(ptr);
		exit(129); /* Cannot allocate memory */
	}
	ptr->next = NULL;
	if (*head == NULL)
	{
		*head = ptr;
	return;
	}
		temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = ptr;
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
