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
			free_list(data.envp);
			/* write(STDOUT_FILENO, "exit\n", 5); */
			break;
		}
	/*signal(SIGINT, handle_sigint); */
		data.tokens = get_tok(data.linearg);
		if (data.tokens == 0)
			continue;
		data.token = malloc(sizeof(char *) * (data.tokens + 1));
		if (data.token == NULL)
			exit(98);
		tokenize(data.linearg, data.token, data.tokens);
		if (check_builtin(data))
		{
			free(data.token);
			free(data.linearg);
			continue;
		}
		execute(data, path + 5, envp);
		free(data.token);
		free(data.linearg);
	}
	free(data.linearg);
}
