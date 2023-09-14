#include "shell.h"

/**
 * alias_prt - handle aliases
 * @data: program data struct
 * @alias:  alias to print
 * Return: 0 if sucess, or other number
 */
int alias_print(vars_of_project *data, char *alias)
{
	int m, n, len_aliases;
	char buffer[250] = {'\0'};

	if (data->ls_alias)
	{
		len_aliases = string_len(alias);
		for (m = 0; data->ls_alias[m]; m++)
		{
			if (!alias || (string_cmp(data->ls_alias[m], alias, len_aliases)
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
				_prt(buffer);
			}
		}
	}

	return (0);
}

/**
 * alias_get - handle aliases
 * @data: program data struct
 * @name: the requested alias.
 * Return: 0 if sucess, or other number
 */
char *alias_get(vars_of_project *data, char *name)
{
	int m, len_aliases;

	if (name == NULL || data->ls_alias == NULL)
		return (NULL);

	len_aliases = string_len(name);

	for (m = 0; data->ls_alias[m]; m++)
	{
		if (string_cmp(name, data->ls_alias[m], len_aliases) &&
				data->ls_alias[m][len_aliases] == '=')
		{
			return (data->ls_alias[m] + len_aliases + 1);
		}
	}
	return (NULL);

}

/**
 * alias_st - create and rewrite alias
 * @alias_string: alias to set
 * @data: program data struct
 * Return: 0 if sucess, or other number 
 */
int alias_st(char *alias_string, vars_of_project *data)
{
	int m, j;
	char buffer[250] = {'0'}, *mytemp = NULL;

	if (alias_string == NULL ||  data->ls_alias == NULL)
		return (1);
	for (m = 0; alias_string[m]; m++)
		if (alias_string[m] != '=')
			buffer[m] = alias_string[m];
		else
		{
			mytemp = alias_get(data, alias_string + m + 1);
			break;
		}

	for (j = 0; data->ls_alias[j]; j++)
		if (string_cmp(buffer, data->ls_alias[j], m) &&
				data->ls_alias[j][m] == '=')
		{
			free(data->ls_alias[j]);
			break;
		}

	if (mytemp)
	{
		add_tobuff(buffer, "=");
		add_tobuff(buffer, mytemp);
		data->ls_alias[j] = string_dup(buffer);
	}
	else
		data->ls_alias[j] = string_dup(alias_string);
	return (0);
}
