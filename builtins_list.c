#include "shell.h"

/**
 * builtins_list - find  match to execute
 * @data: program data struct
 * Return: Return match of executed function ,
 * or -1.
 **/
int builtins_list(vars_of_project *data)
{
	int iter;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (iter = 0; options[iter].builtin != NULL; iter++)
	{
		if (str_compare(options[iter].builtin, data->cmd_name, 0))
		{
			return (options[iter].function(data));
		}
	}
	return (-1);
}
