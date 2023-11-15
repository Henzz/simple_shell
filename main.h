#ifndef MAIN_H
#define MAIN_H

/* Maximum number of letters allowed */
#define MAX_BUFFER_LENGTH 1024
/* Maximum number of arguments allowed */
#define MAX_ARGUMENTS 64
/* Clears the shell using escape sequences */
#define clear() printf("\033[H\033[J")

/* Greeting message during startup */
void init_shell(void);
/* Displays prompt */
void display_prompt(void);
/* Reads users input */
int read_input(char *str);
/* Fetches actual path of a command */
char *get_path(char *cmd);
/* tokenize_path - Fetches actual path of a command */
char *tokenize_path(char *path, char *cmd);
/* Executes a system command */
void exec_cmd(char **argv);
/* execute builtin commands */
int helper_cmd(char *cmd);
/* Initialize each element to NULL and store each token in the cmdArgv array */
void tokenize_cmd(char *cmd, char **cmd_argv);

#endif /* MAIN_H */
