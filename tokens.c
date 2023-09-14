#include "shell.h"

/**
 * tokenizing - to separate a string with a delimit
 * @data: program data struct
 * Return: string parts array
 */
void tokenizing(vars_of_project *data)
{
	char *delimit = " \t";
	int m, n, count = 2, leng;

	leng = string_len(data->line_inpt);
	if (leng)
	{
		if (data->line_inpt[leng - 1] == '\n')
			data->line_inpt[leng - 1] = '\0';
	}

	for (m = 0; data->line_inpt[m]; m++)
	{
		for (n = 0; delimit[n]; n++)
		{
			if (data->line_inpt[m] == delimit[n])
				count++;
		}
	}

	data->toks = malloc(count * sizeof(char *));
	if (data->toks == NULL)
	{
		perror(data->prog_name);
		exit(errno);
	}
	m = 0;
	data->toks[m] = string_dup(_stringtok(data->line_inpt, delimit));
	data->cmd_name = string_dup(data->toks[0]);
	while (data->toks[m++])
	{
		data->toks[m] = string_dup(_stringtok(NULL, delimit));
	}
}
