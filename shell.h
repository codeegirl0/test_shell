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

#include "macros.h" /* messages and prompt */

/************* STRUCTURES **************/

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


/*========  shell.c  ========*/

/* to initialize program data*/
void start_data(vars_of_project *data, int arc, char *argv[], char **env);

/* Print new line */
void deal_with_ctrlc(int opr UNUSED);

/* Show prompt with a loop*/
void promptshow(char *myprompt, vars_of_project *data);

/*========  _getline.c  ========*/

/* Read one input line */
int _readline(vars_of_project *data);

/* split lines */
int logic_ops_spliter(char *arr_cmds[], int i, char arr_opr[]);


/*======== expansions.c ========*/

/* variables expanding */
void vars_expander(vars_of_project *data);

/* aliases  expanding*/
void alias_expander(vars_of_project *data);

/* add the string to buffer end*/
int add_tobuff(char *mybuffer, char *add_the_str);


/*======== str_tok.c ========*/

/* to create a pointer to a string */
char *_stringtok(char *myline, char *mydelim);

/* Separate string with delimiter */
void tokenizing(vars_of_project *data);



/*======== execute.c ========*/

/* execute command with path*/
int executer(vars_of_project *data);


/*======== builtins_list.c ========*/

/* execute if it matches*/
int list_builts(vars_of_project *data);


/*======== find_in_path.c ========*/

/* to search in paths*/
int search_program(vars_of_project *data);

/* Create path directories array*/
char **path_tokenizing(vars_of_project *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_arr_of_ptrs(char **directories);

/* Free the fields needed each loop */
void freeing_recurrentData(vars_of_project *data);

/* Free all field of the data */
void freeing_allData(vars_of_project *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int exit_built(vars_of_project *data);

/* Change the current directory */
int cd_built(vars_of_project *data);

/* set the work directory */
int set_work_dir(vars_of_project *data, char *new_dir);

/* show help information */
int help_built(vars_of_project *data);

/* set, unset and show alias */
int alias_built(vars_of_project *data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int env_built(vars_of_project *data);

/* create or override a variable of environment */
int built_set_environ(vars_of_project *data);

/* delete a variable of environment */
int built_unset_environ(vars_of_project *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *environ_get_key(char *name, vars_of_project *data);

/* Overwrite the value of the environment variable */
int environ_set_key(char *key, char *value, vars_of_project *data);

/* Remove a key from the environment */
int environ_rmv_key(char *key, vars_of_project *data);

/* prints the current environ */
void print_env(vars_of_project *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _prt(char *string);

/* Prints a string in the standar error */
int _prte(char *string);

/* Prints a string in the standar error */
int _print_err(int errorcode, vars_of_project *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int string_len(char *string);

/* Duplicates an string */
char *string_dup(char *string);

/* Compares two strings */
int string_cmp(char *string1, char *string2, int number);

/* Concatenates two strings */
char *string_concati_nate(char *string1, char *string2);

/* Reverse a string */
void string_rev(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void lng_to_str(long number, char *string, int base);

/* convert an string in to a number */
int _tiao(char *s);

/* count the coincidences of character in string */
int count_chars(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int alias_print(vars_of_project *data, char *alias);

/* get the alias name */
char *alias_get(vars_of_project *data, char *alias);

/* set the alias name */
int alias_set(char *alias_string, vars_of_project *data);


#endif /* SHELL_H */
