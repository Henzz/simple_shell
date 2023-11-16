#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
/**
 * str_len - Calculates the lenght of a string.
 * @str: The string to calculate.
 * Return: On success the length of the string str,
 * Otherwise 0.
 */
int str_len(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}

/**
 * str_dup - Creates a copy of a string.
 * @str: The string to copy.
 * Return: The copy of the string str.
 */
char *str_dup(char *str)
{
	int i, len;
	char *dest;

	len = str_len(str);
	dest = malloc(sizeof(char) * (len + 1));
	/* On malloc failure */
	if (dest == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Failed to allocate memory for str_dup\n");
		return (NULL);
	}
	for (i = 0; str[i] != '\0'; i++)
		dest[i] = str[i];
	dest[i] = '\0';

	return (dest);
}

/**
 * str_cmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: 0 on strings match, Otherwise -1.
 */
int str_cmp(char *s1, char *s2)
{
	int i;

    /* Check if string length match */
	if (str_len(s1) != str_len(s2))
		return (-1);

    /* Check each characters */
	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}

	return (0);
}

/**
 * print_char - Writes a character to stdout.
 * @c: Character that will be written to stdout.
 * Return: On success number of characters written.
 */
int print_char(char c)
{
	return (write(1, &c, 1));
}

/**
 * print_str - Prints a string character by character.
 * @str: String to be printed. If the string is NULL it will print (null)
 * @new_line: If integer is 0 a new line will be printed. Otherwise a new line
 * will not be printed.
 */
void print_str(char *str, int new_line)
{
	int i;

	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i] != '\0'; i++)
		write(STDOUT_FILENO, &str[i], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}

