#include <stdlib.h>
#include <stdio.h>
/**
 * init_shell - Greetings message during shell startup.
 */
void init_shell(void)
{
	char *username = getenv("USER");

	printf("******************************************\n");
	printf("\t\t\t\t\t *\n");
	printf("\t\t\t\t\t *\n");
	printf("\tWELCOME TO SIMPLE SHELL\t\t *\n");
	printf("\t\t\t\t\t *\n");
	printf("\t-USE AT YOUR OWN RISK-\t\t *\n");
	printf("\t\t\t\t\t *\n");
	printf("\t\t\t\t\t *\n");
	printf("******************************************\n");
	printf("USER is: @%s\n", username);
}

