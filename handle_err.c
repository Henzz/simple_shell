#include <stdio.h>
#include <stdlib.h>
/**
 * handle_error - handles excve error.
 */
void handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

