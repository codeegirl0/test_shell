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
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(vars_of_project *data);

/* Free all field of the data */
void free_all_data(vars_of_project *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int builtin_exit(vars_of_project *data);

/* Change the current directory */
int builtin_cd(vars_of_project *data);

/* set the work directory */
int set_work_directory(vars_of_project *data, char *new_dir);

/* show help information */
int builtin_help(vars_of_project *data);

/* set, unset and show alias */
int builtin_alias(vars_of_project *data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(vars_of_project *data);

/* create or override a variable of environment */
int builtin_set_env(vars_of_project *data);

/* delete a variable of environment */
int builtin_unset_env(vars_of_project *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, vars_of_project *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, vars_of_project *data);

/* Remove a key from the environment */
int env_remove_key(char *key, vars_of_project *data);

/* prints the current environ */
void print_environ(vars_of_project *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, vars_of_project *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(vars_of_project *data, char *alias);

/* get the alias name */
char *get_alias(vars_of_project *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, vars_of_project *data);


#endif /* SHELL_H */
