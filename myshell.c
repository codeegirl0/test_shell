#include "shell.h"
/**
 * main - give variables for program
 * @argc: received value number of commandline
 * @argv: value received of commandline
 * @env: number of values received from the command line
 * Return: 0 if success.
 */
int main(int argc, char *argv[], char *env[])
{
	vars_of_project data_struct = {NULL}, *data = &data_struct;
	char *myprompt = "";

	start_data(data, argc, argv, env);

	signal(SIGINT, deal_with_ctrlc);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		myprompt = PROMPT_MSG;
	}
	errno = 0;
	promptshow(myprompt, data);
	return (0);
}

/**
 * deal_with_ctrlc - print prompt in new line
 * when ctrl + c sent to program
 * @UNUSED: a prototype
 */
void deal_with_ctrlc(int opr UNUSED)
{
	_prt("\n");
	_prt(PROMPT_MSG);
}

/**
 * start_data - give initial struct with info of the program
 * @data: pointer to the structure of data
 * @argv: arguments pased to program execution
 * @env: environ pased to program execution
 * @argc: n value received from the commandline
 */
void start_data(vars_of_project *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->prog_name = argv[0];
	data->line_inpt = NULL;
	data->cmd_name = NULL;
	data->counter_ex = 0;
	if (argc == 1)
		data->descr_file = STDIN_FILENO;
	else
	{
		data->descr_file = open(argv[1], O_RDONLY);
		if (data->descr_file == -1)
		{
			_prte(data->prog_name);
			_prte(": 0: Can't open ");
			_prte(argv[1]);
			_prte("\n");
			exit(127);
		}
	}
	data->toks = NULL;
	data->envir = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->envir[i] = string_dup(env[i]);
		}
	}
	data->envir[i] = NULL;
	env = data->envir;

	data->ls_alias = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->ls_alias[i] = NULL;
	}
}
/**
 * promptshow - the loop to shows the prompt
 * @myprompt: printed prompt 
 * @data: data from struct
 */
void promptshow(char *myprompt, vars_of_project *data)
{
	int code_err = 0, len_str = 0;

	while (++(data->counter_ex))
	{
		_prt(myprompt);
		code_err = len_str = _readline(data);

		if (code_err == EOF)
		{
			freeing_allData(data);
			exit(errno); 
		}
		if (len_str >= 1)
		{
			alias_expander(data);
			vars_expander(data);
			tokenizing(data);
			if (data->toks[0])
			{ 
				code_err = executer(data);
				if (code_err != 0)
					_print_err(code_err, data);
			}
			freeing_recurrentData(data);
		}
	}
}
