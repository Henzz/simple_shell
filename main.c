#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include "main.h"
/**
 * main - executes a command passed.
 * @ac: Number of parameters passed.
 * @av: The name of the program.
 * Return: Always 0.
 */
int main(__attribute__((unused)) int ac, char **av)
{
	char *buffer;
	size_t size;
	int cmd_counter;

	/* If it's in interactive mode */
	if (isatty(STDIN_FILENO))
		greeting();

	cmd_counter = 0;
	signal(SIGINT, SIG_IGN);
	do {
		cmd_counter++;
		buffer = NULL;
		size = 0;
		read_input(&buffer, &size, cmd_counter, av);
	} while (1);

	return (0);
}
