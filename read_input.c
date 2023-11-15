#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * read_input - Reads input from input stream.
 * @str: string to copy the command read to.
 *
 * Return: 1 for command not read,
 * 0 for successfully read command and
 * -1 for EOF or CTRL+D.
 */
int read_input(char *str)
{
	char *buffer;
	size_t buffersize = 0;
	ssize_t nchars_read = 0;

	nchars_read = getline(&buffer, &buffersize, stdin);
	/* Check if the getline failed or reached EOF or if user used CTRL+D */
	if (nchars_read == -1)
		exit(0);

	if (nchars_read > 0)
	{
		strcpy(str, buffer);
		return (0);
	}
	else
		return (1);
}
