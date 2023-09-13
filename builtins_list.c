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
		{"exit", exit_built},
		{"help", help_built},
		{"cd", cd_built},
		{"alias", alias_built},
		{"env", environ_built},
		{"setenv", built_set_environ},
		{"unsetenv", built_unset_environ},
		{NULL, NULL}
	};

	for (iter = 0; options[iter].builtin != NULL; iter++)
	{
		if (string_cmp(options[iter].builtin, data->cmd_name, 0))
		{
			return (options[iter].function(data));
		}
	}
	return (-1);
}
