#include "shell.h"

/**
 * freeing_recurrentData - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void freeing_recurrentData(data_of_program *data)
{
	if (data->tokens)
		free_arr_of_ptrs(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * freeing_allData - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void freeing_allData(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	freeing_recurrentData(data);
	free_arr_of_ptrs(data->env);
	free_arr_of_ptrs(data->alias_list);
}

/**
 * free_arr_of_ptrs - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_arr_of_ptrs(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
