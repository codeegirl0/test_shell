#include "shell.h"

/**
 * environ_built - to show env
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int environ_built(vars_of_project *data)
{
	int m;
	char namecp[50] = {'\0'};
	char *cp_var = NULL;

	if (data->toks[1] == NULL)
		prt_env(data);
	else
	{
		for (m = 0; data->toks[1][m]; m++)
		{
			if (data->toks[1][m] == '=')
			{
				cp_var = string_dup(environ_key_get(namecp, data));
				if (cp_var != NULL)
					environ_key_set(namecp, data->toks[1] + m + 1, data);

				prt_env(data);
				if (environ_key_get(namecp, data) == NULL)
				{
					_prt(data->toks[1]);
					_prt("\n");
				}
				else
				{
					environ_key_set(namecp, cp_var, data);
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
 * built_set_environ - to set env
 * @data: program data struct
 * Return: 0 if sucess, or other number
 */
int built_set_environ(vars_of_project *data)
{
	if (data->toks[1] == NULL || data->toks[2] == NULL)
		return (0);
	if (data->toks[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}

	environ_key_set(data->toks[1], data->toks[2], data);

	return (0);
}

/**
 * built_unset_environ - to unset env
 * @data: program data struct
 * Return: 0 if success
 */
int built_unset_environ(vars_of_project *data)
{
	if (data->toks[1] == NULL)
		return (0);
	if (data->toks[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	environ_rmv_key(data->toks[1], data);

	return (0);
}
