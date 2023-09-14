#include "shell.h"

/**
* _readline - reading from the prompt.
* @data: struct of data of the program
* Return: the counting bytes.
*/
int _readline(vars_of_project *data)
{
	char buffsize[BUFFER_SIZE] = {'\0'};
	static char *arr_cmds[10] = {NULL};
	static char arr_opr[10] = {'\0'};
	ssize_t byte_reader, i = 0;
	if (!arr_cmds[0] || (arr_opr[0] == '&' && errno != 0) ||
		(arr_opr[0] == '|' && errno == 0))
	{
		for (i = 0; arr_cmds[i]; i++)
		{
			free(arr_cmds[i]);
			arr_cmds[i] = NULL;
		}
		byte_reader = read(data->descr_file, &buffsize, BUFFER_SIZE - 1);
		if (byte_reader == 0)
			return (-1);
		i = 0;
		do {
			arr_cmds[i] = string_dup(_stringtok(i ? NULL : buffsize, "\n;"));
			i = logic_ops_spliter(arr_cmds, i, arr_opr);
		} while (arr_cmds[i++]);
	}
	data->line_inpt = arr_cmds[0];
	for (i = 0; arr_cmds[i]; i++)
	{
		arr_cmds[i] = arr_cmds[i + 1];
		arr_opr[i] = arr_opr[i + 1];
	}

	return (string_len(data->line_inpt));
}


/**
* logic_ops_spliter - to check and split
* @arr_cmds: command array.
* @i: number in array to check
* @arr_opr: logical operators array of previous command
* Return:last command index.
*/
int logic_ops_spliter(char *arr_cmds[], int i, char arr_opr[])
{
	char *mytemp = NULL;
	int n;
	for (n = 0; arr_cmds[i] != NULL  && arr_cmds[i][n]; n++)
	{
		if (arr_cmds[i][n] == '&' && arr_cmds[i][n + 1] == '&')
		{
			mytemp = arr_cmds[i];
			arr_cmds[i][n] = '\0';
			arr_cmds[i] = string_dup(arr_cmds[i]);
			arr_cmds[i + 1] = string_dup(mytemp + n + 2);
			i++;
			arr_opr[i] = '&';
			free(mytemp);
			n = 0;
		}
		if (arr_cmds[i][n] == '|' && arr_cmds[i][n + 1] == '|')
		{
			mytemp = arr_cmds[i];
			arr_cmds[i][n] = '\0';
			arr_cmds[i] = string_dup(arr_cmds[i]);
			arr_cmds[i + 1] = string_dup(mytemp + n + 2);
			i++;
			arr_opr[i] = '|';
			free(mytemp);
			n = 0;
		}
	}
	return (i);
}
