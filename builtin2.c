#include "shell.h"

/**
 * cd - changed the current working directory
 * @data: shell data
*/
void cd(data_t *data)
{
	char *new_dir, *cwd;
	char buff[BUFF_SIZE];

	cwd = getcwd(buff, BUFF_SIZE);
	if (data->tokens < 2)
		new_dir = get_dir_path(data->envp, "HOME");
	else if (data->token[1][0] == '-')
		new_dir = get_dir_path(data->envp, "OLDPWD");
	else
		new_dir = data->token[1];
	if (!new_dir)
		return;
	if (chdir(new_dir) != 0)
	{
		perr_str("./hsh: 1: cd: can't cd to", data->token[1]);
		perr_ch('\n');
		perr_ch(-1);
	}
	data->tokens = 3;
	free(data->token);
	data->token = malloc(sizeof(char *) * 3);
	data->token[0] = "setenv";
	data->token[1] = "OLDPWD";
	data->token[2] = cwd;
	_setenv(data);
	data->token[0] = "setenv";
	data->token[1] = "PWD";
	data->token[2] = new_dir;
	_setenv(data);
}
