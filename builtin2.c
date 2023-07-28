#include "shell.h"

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
