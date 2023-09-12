#include "shell.h"

/**
 * print_alias - handle aliases
 * @data: program data struct
 * @alias:  alias to print
 * Return: 0 if sucess, or other number
 */
int print_alias(vars_of_project *data, char *alias)
{
	int m, n, len_aliases;
	char buffer[250] = {'\0'};

	if (data->ls_alias)
	{
		len_aliases = str_length(alias);
		for (m = 0; data->ls_alias[m]; m++)
		{
			if (!alias || (str_compare(data->ls_alias[m], alias, len_aliases)
						&&	data->ls_alias[m][len_aliases] == '='))
			{
				for (n = 0; data->ls_alias[m][n]; n++)
				{
					buffer[n] = data->ls_alias[m][n];
					if (data->ls_alias[m][n] == '=')
						break;
				}
				buffer[n + 1] = '\0';
				add_tobuff(buffer, "'");
				add_tobuff(buffer, data->ls_alias[m] + n + 1);
				add_tobuff(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - handle aliases
 * @data: program data struct
 * @name: the requested alias.
 * Return: 0 if sucess, or other number
 */
char *get_alias(vars_of_project *data, char *name)
{
	int m, len_aliases;

	if (name == NULL || data->ls_alias == NULL)
		return (NULL);

	len_aliases = str_length(name);

	for (m = 0; data->ls_alias[m]; m++)
	{
		if (str_compare(name, data->ls_alias[m], len_aliases) &&
				data->ls_alias[m][len_aliases] == '=')
		{
			return (data->ls_alias[m] + len_aliases + 1);
		}
	}
	return (NULL);

}

/**
 * set_alias - create and rewrite alias
 * @alias_string: alias to set
 * @data: program data struct
 * Return: 0 if sucess, or other number 
 */
int set_alias(char *alias_string, vars_of_project *data)
{
	int m, n;
	char buffer[250] = {'0'}, *mytemp = NULL;

	if (alias_string == NULL ||  data->ls_alias == NULL)
		return (1);
	for (m = 0; alias_string[m]; m++)
		if (alias_string[m] != '=')
			buffer[m] = alias_string[m];
		else
		{
			mytemp = get_alias(data, alias_string + m + 1);
			break;
		}

	for (j = 0; data->ls_alias[j]; j++)
		if (str_compare(buffer, data->ls_alias[j], m) &&
				data->ls_alias[j][m] == '=')
		{
			free(data->ls_alias[j]);
			break;
		}

	if (mytemp)
	{
		add_tobuff(buffer, "=");
		add_tobuff(buffer, mytemp);
		data->ls_alias[j] = str_duplicate(buffer);
	}
	else
		data->ls_alias[j] = str_duplicate(alias_string);
	return (0);
}
