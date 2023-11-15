#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "main.h"
/**
 * exec_cmd - executes system commands.
 * @argv: array of strings that are commands.
 */
void exec_cmd(char **argv)
{
	pid_t pid; /* Child process id */

	if (argv)
	{
		pid = fork();
		if (pid == -1)
			handle_error("Forking failed");
		else if (pid == 0)
		{
			/* Checking if file path exists */
			argv[0] = get_path(argv[0]);
			if (argv[0] == NULL)
				handle_error("shell");
			/* Execute command */
			if (execve(argv[0], argv, environ) == -1)
				handle_error("Error executing command");
		}
		else
		{
			/* If parent wait for child process */
			wait(NULL);
		}
	}
}
