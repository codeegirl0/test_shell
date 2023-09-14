#include "shell.h"

/**
 * _prt - write many chars in output
 * @string: pointer of chars
 * Return: writed bytes -1 in error, errno setted approp.
 */
int _prt(char *string)
{
	return (write(STDOUT_FILENO, string, string_len(string)));
}
/**
 * _prte - write chars in error 
 * @string: pointer of chars
 * Return: writed number of bytes.
 * if error -1 , errno setted.
 */
int _prte(char *string)
{
	return (write(STDERR_FILENO, string, string_len(string)));
}

/**
 * _print_err - write chars in error
 * @data: program data struct
 * @errorcode: the error code
 * Return: writed bytes or -1 and errno.
 */
int _print_err(int errorcode, vars_of_project *data)
{
	char n_like_str[10] = {'\0'};

	lng_to_str((long) data->counter_ex, n_like_str, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_prte(data->prog_name);
		_prte(": ");
		_prte(n_like_str);
		_prte(": ");
		_prte(data->toks[0]);
		if (errorcode == 2)
			_prte(": Illegal number: ");
		else
			_prte(": can't do cd to ");
		_prte(data->toks[1]);
		_prte("\n");
	}
	else if (errorcode == 127)
	{
		_prte(data->prog_name);
		_prte(": ");
		_prte(n_like_str);
		_prte(": ");
		_prte(data->cmd_name);
		_prte(": not found\n");
	}
	else if (errorcode == 126)
	{
		_prte(data->prog_name);
		_prte(": ");
		_prte(n_like_str);
		_prte(": ");
		_prte(data->cmd_name);
		_prte(": Permission denied\n");
	}
	return (0);
}
