#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* to call printf*/
#include <unistd.h> /* to call fork and execve*/
#include <stdlib.h>
#include <string.h> /* to call strtok*/
#include <errno.h> /* to call errno , perror */
#include <sys/types.h> /* to call pid */
#include <sys/wait.h> /* to call wait function */
#include <stddef.h>
#include <signal.h> /* to do signal management */
#include <sys/stat.h> /* to call stat function */
#include <fcntl.h> /* to open files*/

/************* MACROS **************/

#include "messages.h" /* messages and prompt */

/************* All STRUCTURES **************/

/**
 * struct info - for the program's data
 * @prog_name: for executable name 
 * @line_inpt: pointer to input that read
 * @cmd_name: pointer to first command 
 * @counter_ex: excecuted comands
 * @descr_file: descriptor for commands
 * @toks: for array tokenized input
 * @envir: a copy for environ
 * @ls_alias: list of pointers for aliases.
 */
typedef struct info
{
	char *prog_name;
	char *line_inpt;
	char *cmd_name;
	int counter_ex;
	int descr_file;
	char **toks;
	char **envir;
	char **ls_alias;
} vars_of_project;

/**
 * struct builtins - this is a struct for builtins
 * @builtin: the builtin name
 * @function: associated function for builtin
 */
typedef struct builts
{
	char *built;
	int (*function)(vars_of_project *data);
} builts;


/************* FOR MAIN *************/


/*========  myshell.c  ========*/

/* to initialize program data*/
void start_data(vars_of_project *data, int arc, char *argv[], char **env);

/* Print new line */
void deal_with_ctrlc(int opr UNUSED);

/* Show prompt with a loop*/
void promptshow(char *myprompt, vars_of_project *data);

/*========  _readline.c  ========*/

/* Read one input line */
int _readline(vars_of_project *data);

/* split lines */
int logic_ops_spliter(char *arr_cmds[], int i, char arr_opr[]);


/*======== toexpans.c ========*/

/* variables expanding */
void vars_expander(vars_of_project *data);

/* aliases  expanding*/
void alias_expander(vars_of_project *data);

/* add the string to buffer end*/
int add_tobuff(char *mybuffer, char *add_the_str);


/*======== tokenize_str.c ========*/

/* to create a pointer to a string */
char *_stringtok(char *myline, char *mydelim);

/* Separate string with delimiter */
void tokenizing(vars_of_project *data);



/*======== executer.c ========*/

/* execute command with path*/
int executer(vars_of_project *data);


/*======== list_built.c ========*/

/* execute if it matches*/
int list_builts(vars_of_project *data);


/*======== search_in_path.c ========*/

/* to search in paths*/
int search_program(vars_of_project *data);

/* Create path directories array*/
char **path_tokenizing(vars_of_project *data);


/************** HELPERS **************/

/*======== free_help.c ========*/

/* to free directory memory */
void free_arr_of_ptrs(char **directories);

/* to free the fields */
void freeing_recurrentData(vars_of_project *data);

/* to free all data fields */
void freeing_allData(vars_of_project *data);


/************** ALL BUILTINS **************/


/*======== more_built.c ========*/

/* exit the shell */
int exit_built(vars_of_project *data);

/* to change current directory */
int cd_built(vars_of_project *data);

/* set working directory */
int set_workdir(vars_of_project *data, char *new_dir);

/* show help info */
int help_built(vars_of_project *data);

/* handle aliases */
int alias_built(vars_of_project *data);


/*======== env_built.c ========*/

/* show environment of running shell */
int environ_built(vars_of_project *data);

/* handle variable environment */
int built_set_environ(vars_of_project *data);

/* remove variable environment */
int built_unset_environ(vars_of_project *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES **************/

/*======== manage_env.c ========*/

/* Get environment variable value */
char *environ_key_get(char *name, vars_of_project *data);

/* handle environment variable values */
int environ_key_set(char *key, char *value, vars_of_project *data);

/* delete a key from  environ */
int environ_rmv_key(char *key, vars_of_project *data);

/* to show current environ */
void prt_env(vars_of_project *data);


/************** HELPERS FOR PRINT **************/


/*======== print_help.c ========*/

/* to print a string in output */
int _prt(char *string);

/* to print a string in an error */
int _prte(char *string);

/* to print a string in an error */
int _print_err(int errorcode, vars_of_project *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== str_help.c ========*/

/* counting characters of a string */
int string_len(char *string);

/* Duplicate the string */
char *string_dup(char *string);

/* Compare strings */
int string_cmp(char *string1, char *string2, int number);

/* Concatenates strings */
char *string_concati_nate(char *string1, char *string2);

/* Reverse a string */
void string_rev(char *string);


/*======== number_help.c ========*/

/* convert from num to string */
void lng_to_str(long number, char *string, int base);

/* convert a string into a number */
int _tiao(char *s);

/* count coincidences of character in a string */
int count_chars(char *string, char *character);


/*======== manage_alias.c ========*/

/* print alias list*/
int alias_print(vars_of_project *data, char *alias);

/* get alias name */
char *alias_get(vars_of_project *data, char *alias);

/* set alias name */
int alias_st(char *alias_string, vars_of_project *data);


#endif /* SHELL_H */
