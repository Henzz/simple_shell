#include <stdlib.h>
#include <stdio.h>
/**
 * display_prompt - Prints the current working directory
 * with $ at the end.
 */
void display_prompt(void)
{
	/*
	 * char *username = getenv("USER");
	 * char cwd[MAX_BUFFER_LENGTH];
	 * getcwd(cwd, sizeof(cwd));
	 * printf("@%s:", username);
	 * printf("@%s:", cwd);
	 */
	printf("$ ");
}
