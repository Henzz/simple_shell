#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * error_print - Prints a message error when a comand is not found.
 * @count: A counter keeping track of the number of commands run on the shell.
 * @av: The name of the program running the shell.
 * @cmd: The specific command not being found.
 */
void error_print(char *av, int count, char *cmd)
{
	print_str(av, 1);
	print_str(": ", 1);
	print_number(count);
	print_str(": ", 1);
	print_str(cmd, 1);
}

/**
 * execve_error - Handles errors for execve.
 * @av: The name of the program running the shell.
 * @count: Keeps track of how many commands have been entered.
 * @cmd_copy: The command that filed.
 */
void execve_error(char *av, int count, char *cmd_copy)
{
	error_print(av, count, cmd_copy);
	print_str(": ", 1);
	perror("");
	exit(1);
}
