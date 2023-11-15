#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "main.h"
extern char **environ;
/**
 * exec_cmd - executes system commands.
 * @argv: array of strings that are commands.
 */
void exec_cmd(char **argv)
{
	char *cmd_copy;
	pid_t pid; /* Child process id */

	if (argv)
	{
		pid = fork();
		if (pid == -1)
			dprintf(STDERR_FILENO, "\nFailed forking child..");
		else if (pid == 0)
		{
			cmd_copy = argv[0];
			/* Checking if file path exists */
			argv[0] = get_path(argv[0]);
			if (argv[0] == NULL)
			{
				dprintf(STDERR_FILENO, "bash: %s: command not found\n", cmd_copy);
				exit(0);
			}
			/* Execute command */
			if (execve(argv[0], argv, environ) == -1)
				dprintf(STDERR_FILENO, "Error executing command..");
		}
		else
		{
			/* If parent wait for child process */
			wait(NULL);
		}
	}
}
