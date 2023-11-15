#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"
/**
 * helper_cmd - execute builtin commands.
 * @cmd: command to execute.
 * Return: 1 on success, 0 on failure.
 */
int helper_cmd(char *cmd)
{
	int n_cmds = 2, i, switch_arg = 0;
	char *cmd_lists[2];

	cmd_lists[0] = "clear\n";
	cmd_lists[1] = "exit\n";
	for (i = 0; i < n_cmds; i++)
	{
		if (strcmp(cmd, cmd_lists[i]) == 0)
		{
			switch_arg = i + 1;
			break;
		}
	}

	switch (switch_arg)
	{
		case 1:
			clear();
			return (1);
		case 2:
			dprintf(STDOUT_FILENO, "Exiting shell...\n");
			exit(0);
		default:
			break;
	}
	return (0);
}
