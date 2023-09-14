#include "shell.h"

/**
 * exit_built - leave with status
 * @data: program  data struct
 * Return: 0 if sucess, or other number
 */
int exit_built(vars_of_project *data)
{
	int m;

	if (data->toks[1] != NULL)
	{
		for (m = 0; data->toks[1][m]; m++)
			if ((data->toks[1][m] < '0' || data->toks[1][m] > '9')
					&& data->toks[1][m] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _tiao(data->toks[1]);
	}
	freeing_allData(data);
	exit(errno);
}

/**
 * cd_built - to change current directory
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int cd_built(vars_of_project *data)
{
	char *the_homedir = environ_key_get("HOME", data), *the_dirold = NULL;
	char the_olddir[128] = {0};
	int code_err = 0;

	if (data->toks[1])
	{
		if (string_cmp(data->toks[1], "-", 0))
		{
			the_dirold = environ_key_get("OLDPWD", data);
			if (the_dirold)
				code_err = set_workdir(data, the_dirold);
			_prt(environ_key_get("PWD", data));
			_prt("\n");

			return (code_err);
		}
		else
		{
			return (set_workdir(data, data->toks[1]));
		}
	}
	else
	{
		if (!the_homedir)
			the_homedir = getcwd(the_olddir, 128);

		return (set_workdir(data, the_homedir));
	}
	return (0);
}

/**
 * set_workdir - show working directory
 * @data: program data struct
 * @new_dir: path as working directory
 * Return: 0 if sucess, or other number
 */
int set_workdir(vars_of_project *data, char *new_dir)
{
	char the_olddir[128] = {0};
	int err_code = 0;

	getcwd(the_olddir, 128);

	if (!string_cmp(the_olddir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		environ_key_set("PWD", new_dir, data);
	}
	environ_key_set("OLDPWD", the_olddir, data);
	return (0);
}

/**
 * help_built - to show running environnement
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int help_built(vars_of_project *data)
{
	int m, leng = 0;
	char *messj[6] = {NULL};

	messj[0] = HELP_MSG;

	if (data->toks[1] == NULL)
	{
		_prt(messj[0] + 6);
		return (1);
	}
	if (data->toks[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	messj[1] = HELP_EXIT_MSG;
	messj[2] = HELP_ENV_MSG;
	messj[3] = HELP_SETENV_MSG;
	messj[4] = HELP_UNSETENV_MSG;
	messj[5] = HELP_CD_MSG;

	for (m = 0; messj[m]; m++)
	{
		leng = string_len(data->toks[1]);
		if (string_cmp(data->toks[1], messj[m], leng))
		{
			_prt(messj[m] + leng + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * alias_built - handle aliases
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int alias_built(vars_of_project *data)
{
	int m = 0;

	if (data->toks[1] == NULL)
		return (alias_print(data, NULL));

	while (data->toks[++m])
	{
		if (count_chars(data->toks[m], "="))
			alias_st(data->toks[m], data);
		else
			alias_print(data, data->toks[m]);
	}

	return (0);
}
