#include "shell.h"

/**
 * _prt - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _prt(char *string)
{
	return (write(STDOUT_FILENO, string, string_len(string)));
}
/**
 * _prte - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _prte(char *string)
{
	return (write(STDERR_FILENO, string, string_len(string)));
}

/**
 * _print_err - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_err(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	lng_to_str((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_prte(data->program_name);
		_prte(": ");
		_prte(n_as_string);
		_prte(": ");
		_prte(data->tokens[0]);
		if (errorcode == 2)
			_prte(": Illegal number: ");
		else
			_prte(": can't cd to ");
		_prte(data->tokens[1]);
		_prte("\n");
	}
	else if (errorcode == 127)
	{
		_prte(data->program_name);
		_prte(": ");
		_prte(n_as_string);
		_prte(": ");
		_prte(data->command_name);
		_prte(": not found\n");
	}
	else if (errorcode == 126)
	{
		_prte(data->program_name);
		_prte(": ");
		_prte(n_as_string);
		_prte(": ");
		_prte(data->command_name);
		_prte(": Permission denied\n");
	}
	return (0);
}
