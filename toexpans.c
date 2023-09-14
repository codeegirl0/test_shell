#include "shell.h"

/**
 * vars_expander - to expand vars
 * @data: program data struct
 * Return: set the errno.
 */
void vars_expander(vars_of_project *data)
{
	int m, n;
	char theline[BUFFER_SIZE] = {0}, toexp[BUFFER_SIZE] = {'\0'}, *tempo;

	if (data->line_inpt == NULL)
		return;
	add_tobuff(theline, data->line_inpt);
	for (m = 0; theline[m]; m++)
		if (theline[m] == '#')
			theline[m--] = '\0';
		else if (theline[m] == '$' && theline[m + 1] == '?')
		{
			theline[m] = '\0';
			lng_to_str(errno, toexp, 10);
			add_tobuff(theline, toexp);
			add_tobuff(theline, data->line_inpt + m + 2);
		}
		else if (theline[m] == '$' && theline[m + 1] == '$')
		{
			theline[m] = '\0';
			lng_to_str(getpid(), toexp, 10);
			add_tobuff(theline, toexp);
			add_tobuff(theline, data->line_inpt + m + 2);
		}
		else if (theline[m] == '$' && (theline[m + 1] == ' ' || theline[m + 1] == '\0'))
			continue;
		else if (theline[m] == '$')
		{
			for (n = 1; theline[m + n] && theline[m + n] != ' '; n++)
				toexp[n - 1] = theline[m + n];
			tempo = environ_key_get(toexp, data);
			theline[m] = '\0', toexp[0] = '\0';
			add_tobuff(toexp, theline + m + n);
			tempo ? add_tobuff(theline, tempo) : 1;
			add_tobuff(theline, toexp);
		}
	if (!string_cmp(data->line_inpt, theline, 0))
	{
		free(data->line_inpt);
		data->line_inpt = string_dup(theline);
	}
}

/**
 * alias_expander - to expand the aliases
 * @data: program data struct
 * Return: set the errno.
 */
void alias_expander(vars_of_project *data)
{
	int m, n, the_expand = 0;
	char theline[BUFFER_SIZE] = {0}, toexp[BUFFER_SIZE] = {'\0'}, *tempo;

	if (data->line_inpt == NULL)
		return;

	add_tobuff(theline, data->line_inpt);

	for (m = 0; theline[m]; m++)
	{
		for (n = 0; theline[m + n] && theline[m + n] != ' '; n++)
			toexp[n] = theline[m + n];
		toexp[n] = '\0';

		tempo = alias_get(data, toexp);
		if (tempo)
		{
			toexp[0] = '\0';
			add_tobuff(toexp, theline + m + n);
			theline[m] = '\0';
			add_tobuff(theline, tempo);
			theline[string_len(theline)] = '\0';
			add_tobuff(theline, toexp);
			the_expand = 1;
		}
		break;
	}
	if (the_expand)
	{
		free(data->line_inpt);
		data->line_inpt = string_dup(theline);
	}
}

/**
 * add_tobuff - add string to the buffer end
 * @buffer: buffer to fill
 * @str_to_add: to copy string
 * Return: set the errno.
 */
int add_tobuff(char *buffer, char *str_to_add)
{
	int leng, m;

	leng = string_len(buffer);
	for (m = 0; str_to_add[m]; m++)
	{
		buffer[leng + m] = str_to_add[m];
	}
	buffer[leng + m] = '\0';
	return (leng + m);
}
