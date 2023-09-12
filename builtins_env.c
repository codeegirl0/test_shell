#include "shell.h"

/**
 * builtin_env - to show env
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int builtin_env(vars_of_project *data)
{
	int m;
	char namecp[50] = {'\0'};
	char *cp_var = NULL;

	if (data->toks[1] == NULL)
		print_environ(data);
	else
	{
		for (m = 0; data->toks[1][m]; m++)
		{
			if (data->toks[1][m] == '=')
			{
				cp_var = str_duplicate(env_get_key(namecp, data));
				if (cp_var != NULL)
					env_set_key(namecp, data->toks[1] + m + 1, data);

				print_environ(data);
				if (env_get_key(namecp, data) == NULL)
				{
					_print(data->toks[1]);
					_print("\n");
				}
				else
				{
					env_set_key(namecp, cp_var, data);
					free(cp_var);
				}
				return (0);
			}
			namecp[m] = data->toks[1][m];
		}
		errno = 2;
		perror(data->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - to set env
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int builtin_set_env(vars_of_project *data)
{
	if (data->toks[1] == NULL || data->toks[2] == NULL)
		return (0);
	if (data->toks[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}

	env_set_key(data->toks[1], data->toks[2], data);

	return (0);
}

/**
 * builtin_unset_env - to unset env
 * @data: program data struct
 * Return: 0 if success
 */
int builtin_unset_env(vars_of_project *data)
{
	if (data->toks[1] == NULL)
		return (0);
	if (data->toks[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	env_remove_key(data->toks[1], data);

	return (0);
}
