#include "shell.h"

/**
 * freeing_recurrentData - to free fields for loop
 * @data: program data struct
 * Return: nothing
 */
void freeing_recurrentData(vars_of_project *data)
{
	if (data->toks)
		free_arr_of_ptrs(data->toks);
	if (data->line_inpt)
		free(data->line_inpt);
	if (data->cmd_name)
		free(data->cmd_name);

	data->line_inpt = NULL;
	data->cmd_name = NULL;
	data->toks = NULL;
}

/**
 * freeing_allData - free every data field
 * @data: program data struct
 * Return: nothing
 */
void freeing_allData(vars_of_project *data)
{
	if (data->descr_file != 0)
	{
		if (close(data->descr_file))
			perror(data->prog_name);
	}
	freeing_recurrentData(data);
	free_arr_of_ptrs(data->envir);
	free_arr_of_ptrs(data->ls_alias);
}

/**
 * free_arr_of_ptrs - frees pointer of array and the array
 * @array: pointers's array
 * Return: Nothing
 */
void free_arr_of_ptrs(char **array)
{
	int m;

	if (array != NULL)
	{
		for (m = 0; array[m]; m++)
			free(array[m]);

		free(array);
		array = NULL;
	}
}
