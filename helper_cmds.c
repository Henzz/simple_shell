#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
 * cd_b - Changes the current working directory to the parameter passed to cd,
 * if no parameter is passed it will change directory to HOME.
 * @buffer: A string containing user input.
 */
void cd_b(char *buffer)
{
	int index, ntoken_count;
	char **argv;
	const char *delim = " \n\t";

	ntoken_count = 0;
	argv = split_cmd(buffer, delim, ntoken_count);
	if (argv[0] == NULL)
	{
		single_free(2, argv, buffer);
		return;
	}
	if (argv[1] == NULL)
	{
		index = get_path_index("HOME");
		chdir((environ[index]) + 5);
	}
	else if (str_cmp(argv[1], "-") == 0)
		print_str(argv[1], 1);
	else
		chdir(argv[1]);

	arr_free(argv);
}

/**
 * print_env - Prints all the environmental variables in the current shell.
 * @buffer: A string containing user input.
 */
void print_env(__attribute__((unused))char *buffer)
{
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * exit_shell - Exits the shell.
 * @buffer: A string containing user input.
 */
void exit_shell(char *buffer)
{
	/* free buffer before exit */
	free(buffer);

	/* If it's in interactive mode */
	if (isatty(STDIN_FILENO))
		print_str("Bye...", 1);

	exit(0);
}

/**
 * check_builtin - Searchs for builtin commands.
 * @str: A string of command.
 *
 * Return: On sucess a pointer to a void function,
 * Otherwise NULL.
 */
void (*check_builtin(char *str))(char *str)
{
	int i;

	builtin_t builtin[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"cd", cd_b},
		{NULL, NULL}
	};

	for (i = 0; builtin[i].built != NULL; i++)
	{
		if (str_cmp(str, builtin[i].built) == 0)
		{
			return (builtin[i].f);
		}
	}
	return (NULL);
}

/**
 * helper_cmds - Checks and execute builtin commands.
 * @cmd: command to execute.
 * @buffer: A string containing user input.
 *
 * Return: 1 on success, -1 on failure.
 */
int helper_cmds(char **cmd, char *buffer)
{
	void (*build)(char *);

	build = check_builtin(cmd[0]);
	if (build == NULL)
		return (-1);

	if (str_cmp("exit", cmd[0]) == 0)
		arr_free(cmd);
	build(buffer);

	return (0);
}

