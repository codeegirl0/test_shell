#include "shell.h"

/**
 * environ_key_get - to get env var value
 * @key: interest env variable
 * @data: program data struct
 * Return:  value as pointer or NULL
 */
char *environ_key_get(char *key, vars_of_project *data)
{
	int m, len_key = 0;

	if (key == NULL || data->envir == NULL)
		return (NULL);

	len_key = string_len(key);

	for (m = 0; data->envir[m]; m++)
	{
		if (string_cmp(key, data->envir[m], len_key) &&
		 data->envir[m][len_key] == '=')
		{
			return (data->envir[m] + len_key + 1);
		}
	}
	return (NULL);
}

/**
 * environ_key_set - to set a key
 * @key: variable to set
 * @value: the new data
 * @data: program data struct
 * Return: 1 if null or 2 if error 0 if sucess.
 */

int environ_key_set(char *key, char *value, vars_of_project *data)
{
	int m, len_key = 0, the_new_key = 1;

	if (key == NULL || value == NULL || data->envir == NULL)
		return (1);

	len_key = string_len(key);

	for (m = 0; data->envir[m]; m++)
	{
		if (string_cmp(key, data->envir[m], len_key) &&
		 data->envir[m][len_key] == '=')
		{
			the_new_key = 0;
			free(data->envir[m]);
			break;
		}
	}
	data->envir[m] = string_concati_nate(string_dup(key), "=");
	data->envir[m] = string_concati_nate(data->envir[m], value);

	if (the_new_key)
	{
		data->envir[m + 1] = NULL;
	}
	return (0);
}

/**
 * environ_rmv_key - to remove key from env
 * @key: remove the key
 * @data: program data struct
 * Return: 1 if the key removed or 0 if the key is not exist;
 */
int environ_rmv_key(char *key, vars_of_project *data)
{
	int m, len_key = 0;

	if (key == NULL || data->envir == NULL)
		return (0);

	len_key = string_len(key);

	for (m = 0; data->envir[m]; m++)
	{
		if (string_cmp(key, data->envir[m], len_key) &&
		 data->envir[m][len_key] == '=')
		{
			free(data->envir[m]);

			m++;
			for (m = 0 ; data->envir[m]; m++)
			{
				data->envir[m - 1] = data->envir[m];
			}
			data->envir[m - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * prt_env - to print current env
 * @data: program data struct
 * Return: nothing
 */
void prt_env(vars_of_project *data)
{
	int n;

	for (n = 0; data->envir[n]; n++)
	{
		_prt(data->envir[n]);
		_prt("\n");
	}
}
