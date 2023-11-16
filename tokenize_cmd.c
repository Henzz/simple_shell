#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
/**
 * tokenize_cmd - Initialize each element to NULL
 * Store each token in the cmdArgv array.
 * @cmd: stdin read input.
 * @cmd_argv: empty array of char to push list of commands.
 */
void tokenize_cmd(char *cmd, char **cmd_argv)
{
	char *token, *delim = "\n\t ";
	int i;

	token = strtok(cmd, delim);
	if (token == NULL)
		free(cmd_argv);
	for (i = 0; token != NULL; i++)
	{
		cmd_argv[i] = malloc(sizeof(char) * strlen(token));
		if (cmd_argv[i] == NULL)
		{
			dprintf(STDERR_FILENO, "Malloc failed\n");
			break;
		}
		/* Remove the newline character from the user input */
		if (token[strlen(token) - 1] == '\n')
			token[strlen(token) - 1] = '\0';
		strcpy(cmd_argv[i], token);
		token = strtok(NULL, delim);
	}
	cmd_argv[i] = NULL;
}

