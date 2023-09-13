#ifndef HELPERS_H
#define HELPERS_H

/* message */
#define PROMPT_MSG "this is a message" 

/* this is is a buffer for getline calls*/
#define BUFFER_SIZE 1024

/* Attibute that is unused */
#define UNUSED __attribute__((unused))

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	cd is a command to change the current directory.\n\n"\
"	or change it to home.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	This command let the shell to exit in your linux system\n"\
"	with a status.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	This command will help to delete a variable from the environment.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	To print all environment variables.\n\n"\
"	This commend helps to print enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Create or modify an envirement variable\n"\
"	variable.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	This command show informations about some commands.\n\n"\
"	The arguments to use:\n\n"\
"	BUILTIN_NAME to specify a the type of help.\n\n"\
"	exit\t[status]\n"\
"	cd\t[dir]\n"\
"	env\n"\
"	unset\t[variable]\n"\
"	setenv\t[variable value]\n"\
"	help\t[built_name]\n\n"

#endif