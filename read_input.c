#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * read_input - Reads input from input stream.
 * @buffer: A pointer to load stream input.
 * @size: A counter for stdin read.
 * @cmd_counter: A counter for keeping track of commands entered.
 * @av: Name of the program running the shell.
 */
void read_input(char *buffer, size_t size, int cmd_counter, char **av)
{
	int i, ntoken_count = 0;
	char **argv;
	const char *delim = " \n\t";
	ssize_t nchars_read;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, PROMPT, str_len(PROMPT));

	nchars_read = getline(&buffer, &size, stdin);
	/* Check if the getline failed or reached EOF or if user used CTRL+D */
	if (nchars_read != -1)
	{
		argv = split_cmd(buffer, delim, ntoken_count);
		if (argv[0] == NULL)
		{
			single_free(2, argv, buffer);
			return;
		}
		i = helper_cmds(argv, buffer);
		if (i == -1 && argv)
			fork_child(argv, buffer, cmd_counter, av);
		/* Free argv before exit */
		for (i = 0; argv[i] != NULL; i++)
			free(argv[i]);
		single_free(2, argv, buffer);
	}
	else
		exit_shell(buffer);
}

/**
 * split_cmd - Splits a string into smaller peaces based on a
 * delimiter.
 * @buffer: A string containing user input.
 * @delim: A constant string containing the delimeter to tokenize buffer.
 * @ntoken_count: Holder for the amount of tokens in a string.
 *
 * Return: On success an array of tokens representing commands,
 * Otherwise NULL.
 */
char **split_cmd(char *buffer, const char *delim, int ntoken_count)
{
	char **argv;

	ntoken_count = calc_ntokens(buffer, delim);
	/* If buffer is empty */
	if (ntoken_count == -1)
	{
		free(buffer);
		return (NULL);
	}

	argv = tokenize_cmd(buffer, delim, ntoken_count);
	if (argv == NULL)
	{
		free(buffer);
		return (NULL);
	}

	return (argv);
}

/**
 * calc_ntokens - Calculates the number of tokens.
 * @buffer: A string containing user input.
 * @delim: A constant string containing the delimeter to tokenize buffer.
 *
 * Return: Total number of tokens, otherwise -1.
 */
int calc_ntokens(char *buffer, const char *delim)
{
	char *buffer_cpy, *token;
	int n_tokens;

	/* Don't forget to free buffer_cpy */
	buffer_cpy = str_dup(buffer);
	/* If buffer is empty */
	if (buffer_cpy == NULL)
		return (-1);

	token = strtok(buffer_cpy, delim);
	/* Calculate the total number of tokens */
	while (token != NULL)
	{
		n_tokens++;
		token = strtok(NULL, delim);
	}
	free(buffer_cpy);

	return (n_tokens);
}

/**
 * tokenize_cmd - Tokenize a string into an array of tokens based on a
 * delimiter.
 * @buffer: A string containing user input.
 * @delim: A constant string containing the delimeter to tokenize buffer.
 * @ntoken_count: The amount of tokens in a string.
 *
 * Return: On success a NULL terminated array of pointer of strings,
 * Otherwise NULL.
 */
char **tokenize_cmd(char *buffer, const char *delim, int ntoken_count)
{
	int i;
	char **argv;
	char *token;
	char *buffer_cpy;

	/* Don't forget to free buffer_cpy */
	buffer_cpy = str_dup(buffer);
	argv = malloc(sizeof(char *) * (ntoken_count + 1));
	if (argv == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Failed to allocate
				memory for tokenize_cmd\n");
		return (NULL);
	}
	token = strtok(buffer_cpy, delim);
	/* Add tokens to the array */
	for (i = 0; token != NULL; i++)
	{
		argv[i] = str_dup(token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	free(buffer_cpy);
	return (argv);
}
