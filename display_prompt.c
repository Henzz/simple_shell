#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * display_prompt - Prints the current working directory
 * with $ at the end.
 */
void display_prompt(void)
{
	char *username = getenv("USER");
	char *cwd;

	getcwd(cwd, sizeof(cwd));
	print_str("@", 0);
	print_str(username, 0);
	print_str(":", 0);
	print_str("@", 0);
	if (cwd[0] == '/')
		cwd = cwd + 1;
	print_str(cwd, 0);
	print_str(":", 0);
	print_str(PROMPT, 0);
}
