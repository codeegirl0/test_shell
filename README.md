simple shell project test
before start coding run git pull to make 
your local repo updated with the original

Asma changes:

---- IN SHELL.H ----
changes based on removing or adding letters
defining STRUCTURES
program_name -> prog_name
input_line -> line_inpt
command_name -> cmd_name
exec_counter -> counter_ex
file_descriptor -> descr_file
**tokens -> **toks
**env -> **envir
**alias_list -> **ls_alias

data_of_program -> vars_of_project
*builtin -> *built
builtins -> builts

Main function:

inicialize_data -> start_data
sisifo -> promptshow
handle_ctrl_c -> deal_with_ctrlc
 
for getline.c:

_getline -> _readline
check_logic_ops -> logic_ops_spliter
expand_variables -> vars_expander
expand_alias -> alias_expander
buffer_add -> add_tobuff
tokenize -> tokenizing
*_strtok -> *_stringtok
execute -> executer
builtins_list -> list_builts
**tokenize_path -> **path_tokenizing
find_program -> search_program
parameters:
*line-> *myline
*delim -> *mydelim
*str_to_add -> *add_the_str
*buffer -> *mybuffer
*array_commands -> *arr_cmds
array_operators -> arr_opr
*prompt -> *myprompt



SHELL/MAIN.C
error_code -> code_err
string_len -> len_str

GETLINE.C
bytes_read -> byte_reader
buff -> buffsize
temp -> mytemp
j -> n

ALIAS_MANAGEMENT.C 
i -> m
j -> n
alias_length -> len_aliases
temp -> mytemp


BUILTINS_ENV.C
i -> m
cpname  -> namecp
var_copy -> cp_var

BUILTINS_LIST.C
iterator -> iter
-- note : is builtins in this file same 
as builtins in shell.h ---


BUILTINS_MORE.C
dir_home -> the_homedir
dir_old -> the_dirold
old_dir -> the_olddir
error_code -> code_err
length -> leng
mensajes -> messj

ENV_MANAEMENT.C
key_length -> len_key
is_new_key -> the_new_key
i -> m 
j -> n

EXECUTE.C
retval -> valret
status -> stat


EXPANTIONS.C
i -> m
j->n 
line -> theline
expansion -> toexp
temp -> tempo
was_expanded -> the_expand
length -> leng


FIND_IN_PATH.C
ret_code -> code_toret
directories -> directs
i -> m
counter_directories -> direct_counter
 
STR_TOK.c
str -> mystr
copystr -> mystrcp


TOKENIZE.C
delimiter -> delimit
counter -> count
length -> leng
i -> m
j -> n


Mighty changes:
