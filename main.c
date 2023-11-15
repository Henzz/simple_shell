#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"
/**
 * calc_ntokens - calculates the number of tokens.
 * @cmd_copy: the token to calculate.
 * Return: number of tokens,
 * or -1 for helper commands.
 */
int calc_ntokens(char *cmd_copy)
{
	char *token, *delim = " ";
	int n_tokens;

	token = strtok(cmd_copy, delim);
	/* Checking if it's a helper command */
	if (helper_cmd(token) == 1)
		return (-1);
	/* Calculate the total number of tokens */
	while (token != NULL)
	{
		n_tokens++;
		token = strtok(NULL, delim);
	}
	return (n_tokens);
}
/**
 * main - executes a command passed.
 * Return: 0 on success, -1 of failure.
 */
int main()
{
	char **cmdArgv;
	char cmd[MAX_BUFFER_LENGTH], cmd_copy[MAX_BUFFER_LENGTH];
	int n_tokens, cmdread;

	while (1)
	{
		display_prompt();
		n_tokens = 0;
		cmdread = 0;
		/* Read input stream */
		cmdread = read_input(cmd);
		if (cmdread == 1)
			continue;
		/* Make a copy of the command */
		strcpy(cmd_copy, cmd);
		/* Split the string into an array of words */
		n_tokens = calc_ntokens(cmd_copy);
		if (n_tokens == -1)
			continue;
		/* Allocate space to hold the array of strings */
		cmdArgv = (char **)malloc(sizeof(char *) * n_tokens + 1);
		if (cmdArgv == NULL)
		{
			dprintf(STDERR_FILENO, "Malloc failed\n");
			cmdArgv = NULL;
			continue;
		}
		/* tokenize cmd */
		tokenize_cmd(cmd, cmdArgv);
		exec_cmd(cmdArgv);
	}
	/* Free the dynamically allocated memory */
	free(cmdArgv);
	return (0);
}
