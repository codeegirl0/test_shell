#include "shell.h"

/**
 * executer - to execute a command with path.
 * @data: prgram data struct
 * Return: zero or return -1.
 */

int executer(vars_of_project *data)
{
	int valret = 0, stat;
	pid_t pidd;

	valret = list_builts(data);
	if (valret != -1)
		return (valret);

	valret = search_program(data);
	if (valret)
	{
		return (valret);
	}
	else
	{
		pidd = fork(); 
		if (pidd == -1)
		{ 
			perror(data->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			valret = execve(data->toks[0], data->toks, data->envir);
			if (valret == -1) 
				perror(data->cmd_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&stat);
			if (WIFEXITED(stat))
				errno = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				errno = 128 + WTERMSIG(stat);
		}
	}
	return (0);
}
