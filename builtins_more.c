#include "shell.h"

/**
 * builtin_exit - leave with status
 * @data: program  data struct
 * Return: 0 if sucess, or other number
 */
int builtin_exit(vars_of_project *data)
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
		errno = _atoi(data->toks[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - to change current directory
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int builtin_cd(vars_of_project *data)
{
	char *the_homedir = env_get_key("HOME", data), *the_dirold = NULL;
	char the_olddir[128] = {0};
	int code_err = 0;

	if (data->toks[1])
	{
		if (str_compare(data->toks[1], "-", 0))
		{
			the_dirold = env_get_key("OLDPWD", data);
			if (the_dirold)
				code_err = set_work_directory(data, the_dirold);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (code_err);
		}
		else
		{
			return (set_work_directory(data, data->toks[1]));
		}
	}
	else
	{
		if (!the_homedir)
			the_homedir = getcwd(the_olddir, 128);

		return (set_work_directory(data, the_homedir));
	}
	return (0);
}

/**
 * set_work_directory - show working directory
 * @data: program data struct
 * @new_dir: path as working directory
 * Return: 0 if sucess, or other number
 */
int set_work_directory(vars_of_project *data, char *new_dir)
{
	char the_olddir[128] = {0};
	int err_code = 0;

	getcwd(the_olddir, 128);

	if (!str_compare(the_olddir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", the_olddir, data);
	return (0);
}

/**
 * builtin_help - to show running environnement
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int builtin_help(vars_of_project *data)
{
	int m, leng = 0;
	char *messj[6] = {NULL};

	messj[0] = HELP_MSG;

	if (data->toks[1] == NULL)
	{
		_print(messj[0] + 6);
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
		leng = str_length(data->toks[1]);
		if (str_compare(data->toks[1], messj[m], leng))
		{
			_print(messj[m] + leng + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * builtin_alias - handle aliases
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int builtin_alias(vars_of_project *data)
{
	int m = 0;

	if (data->toks[1] == NULL)
		return (print_alias(data, NULL));

	while (data->toks[++m])
	{
		if (count_characters(data->toks[m], "="))
			set_alias(data->toks[m], data);
		else
			print_alias(data, data->toks[m]);
	}

	return (0);
}
