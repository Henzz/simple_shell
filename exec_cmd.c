#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * exec_cmd - Executes system commands.
 * @argv: A NULL terminated Array of strings that are name of a program
 * or command and it's parameters.
 * @buffer: A string containing user input.
 * @cmd_counter: A counter for keeping track of commands entered.
 * @av: Name of the program running the shell.
 *
 * Return: On success file path, Otherwise NULL.
 */
char *exec_cmd(char **argv, char *buffer, int cmd_counter, char **av)
{
	int i, check;
	struct stat buf;
	char *cmd, *cmd_copy;

	cmd_copy = argv[0];
	/* Checking if file path exists */
	cmd = get_path(argv[0]);
	if (cmd == NULL)
	{
		/* Look for file in the current directory */
		check = stat(cmd_copy, &buf);
		if (check == -1)
		{
			error_print(av[0], cmd_counter, cmd_copy);
			print_str(": not found", 1);
			single_free(2, buffer, cmd_copy);
			for (i = 1; argv[i]; i++)
				free(argv[i]);
			free(argv);
		}
		/* File exists or has full path */
		cmd = cmd_copy;
		return (NULL);
	}
	return (cmd);
}

/**
 * fork_child - Create a child process and executes system commands.
 * @argv: A NULL terminated Array of strings that are name of a program
 * or command and it's parameters.
 * @buffer: A string containing user input.
 * @cmd_counter: A counter for keeping track of commands entered.
 * @av: Name of the program running the shell.
 *
 * Description: Creates a child to execute for actual
 * commands.
 */
void fork_child(char **argv, char *buffer, int cmd_counter, char **av)
{
	pid_t pid; /* Child process id */
	int status;

	/* check if file path exists and excute */
	argv[0] = exec_cmd(argv, buffer, cmd_counter, av);
	if (argv[0] != NULL)
	{
		pid = fork();
		if (pid == -1)
			malloc_error("\nFailed forking child");
		else if (pid == 0)
		{
			/* Execute command */
			if (execve(argv[0], argv, environ) == -1)
				execve_error(argv[0], cmd_counter, argv[0]);
		}
		else /* If parent wait for child process */
			wait(&status);
	}
}

