#include "shell.h"

int check_file(char *full_path);

/**
 * search_program - search for program path
 * @data: program data struct
 * Return: 0 if success, or an error code
 */
int search_program(vars_of_project *data)
{
	int m = 0, code_toret = 0;
	char **directs;

	if (!data->cmd_name)
		return (2);

	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (check_file(data->cmd_name));

	free(data->toks[0]);
	data->toks[0] = string_concati_nate(string_dup("/"), data->cmd_name);
	if (!data->toks[0])
		return (2);

	directs = path_tokenizing(data);

	if (!directs || !directs[0])
	{
		errno = 127;
		return (127);
	}
	for (m = 0; directs[m]; m++)
	{
		directs[m] = string_concati_nate(directs[m], data->toks[0]);
		code_toret = check_file(directs[m]);
		if (code_toret == 0 || code_toret == 126)
		{
			errno = 0;
			free(data->toks[0]);
			data->toks[0] = string_dup(directs[m]);
			free_arr_of_ptrs(directs);
			return (code_toret);
		}
	}
	free(data->toks[0]);
	data->toks[0] = NULL;
	free_arr_of_ptrs(directs);
	return (code_toret);
}

/**
 * path_tokenizing - to tokenize path in directs
 * @data: program data struct
 * Return: path directories array
 */
char **path_tokenizing(vars_of_project *data)
{
	int m = 0;
	int direct_counter = 2;
	char **toks = NULL;
	char *PATH;

	PATH = environ_key_get("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = string_dup(PATH);

	for (m = 0; PATH[m]; m++)
	{
		if (PATH[m] == ':')
			direct_counter++;
	}

	toks = malloc(sizeof(char *) * direct_counter);

	m = 0;
	toks[m] = string_dup(_stringtok(PATH, ":"));
	while (toks[m++])
	{
		toks[m] = string_dup(_stringtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (toks);

}

/**
 * check_file - file exesting and permissions
 * @full_path: full file name
 * Return: 0 on success, or error.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
