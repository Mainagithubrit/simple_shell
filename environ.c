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



