#include "shell.h"

/**
 * get_cmd - get a command
 * @path: the env path
 * @command: command to get
 * Return: Full command
 */

char *get_cmd(char *path, char *command)
{
	char *cmd = NULL, *path_token;
	char *path_cpy = _strdup(path);
	struct stat statbuf;
	int path_len, cmd_len;

	cmd_len = _strlen(command);

	path_token = _strtok(path_cpy, ":");

	while (path_token)
	{
		path_len = _strlen(path_token);
		cmd = malloc(cmd_len + path_len + 2);
		if (!cmd)
			exit(128); /* Cannot allocate memory */
		_strcpy(cmd, path_token);
		_strcat(cmd, "/");
		_strcat(cmd, command);
		_strcat(cmd, "\0");
		if (stat(cmd, &statbuf) == 0)
		{
			free(path_cpy);
			return (cmd);
		}
		free(cmd);
		path_token = _strtok(NULL, ":");
	}

	if (stat(command, &statbuf) == 0)
	{
		cmd = _strdup(command);
		free(path_cpy);
		return (cmd);
	}

	free(path_cpy);
	return (NULL);
}

/**
 * free_list - Frees a list_t
 * @head: head pointer
 */

void free_list(list_t *head)
{
	if (!head)
		return;

	free_list(head->next);
	if (head->str)
		free(head->str);
	free(head);
}
