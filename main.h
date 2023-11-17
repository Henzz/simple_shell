#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
/* Maximum number of letters allowed */
#define MAX_BUFFER_LENGTH 1024
/* Prompt message */
#define PROMPT "($) "
/* Environment variable */
extern char **environ;

/**
 * struct builtin_d - Defines the builtin functions.
 * @built: The name of the builtin command.
 * @f: A pointer to the right builtin function.
 */
typedef struct builtin_d
{
	char *built;
	void (*f)(char *);
} builtin_t;

/* Greeting message during startup */
void greeting(void);

/* Displays prompt */
void display_prompt(void);

/*** Main Functions ***/
/* Reads users input */
void read_input(char *buffer, size_t size, int cmd_counter, char **av);
/* Splits a buffer in to smaller peaces based on a delimiter */
char **split_cmd(char *buffer, const char *delim, int ntoken_count);
/* Calculates the number of tokens */
int calc_ntokens(char *buffer, const char *delim);
/* Tokenizes a string into an array */
char **tokenize_cmd(char *buffer, const char *delim, int ntoken_count);
/* Fetches actual path of a command */
char *get_path(char *cmd);
/* Fetches the index of a string str */
int get_path_index(char *str);
/* Fetches actual file path of a command */
char **tokenize_path(int index, char *str);
/* Looks for command in path_tokens */
char *get_directory(char **path_tokens, char *command);
/* Build correct file path with command file */
char *build_path(char *directory, char *cmd);
/* Executes a system command */
void exec_cmd(char **argv, char *buffer, int count, char **av);
/* Creates a child process and executes a system command */
void fork_child(char **argv, char *buffer, int cmd_counter, char **av);

/*** Built in cmds ***/
/* Exits the shell */
void exit_shell(char *buffer);
/* Prints enviromnet variables */
void print_env(char *buffer);
/* Changes the current working directory to passed param */
void cd_b(char *buffer);

/*** Helper commands ***/
/* Checks and execute builtin commands. */
int helper_cmds(char **cmd, char *buffer);

/*** Utility ***/
/* Writes a character to stdout */
int print_char(char c);
/* Prints a string character by character */
void print_str(char *str, int new_line);
/* Calculates the lenght of a string */
int str_len(char *str);
/* Creates a copy of a string */
char *str_dup(char *src);
/* Compares two strings */
int str_cmp(char *s1, char *s2);
/* Prints an unsigned number */
int print_number(int n);

/*** Free Memory ***/
/* Frees n amount of pointers of a string */
void single_free(int n, ...);
/* Frees an array double pointer variables */
void arr_free(char **arr);


/*** Error Handling ***/
/* Prints a message error when a command is not found */
void error_print(char *av, int count, char *command);
/* Handles errors for execve error */
void execve_error(char *av, int count, char *tmp_command);
/* Prints malloc error message to standart output stream */
void malloc_error(char *msg);

#endif /* MAIN_H */
