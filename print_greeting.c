#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * greeting - Greetings message during shell startup.
 */
void greeting(void)
{
	char *username = getenv("USER");

	print_str("******************************************", 1);
	print_str("\t\t\t\t\t *", 1);
	print_str("\t\t\t\t\t *", 1);
	print_str("\tWELCOME TO SIMPLE SHELL\t\t *", 1);
	print_str("\t\t\t\t\t *", 1);
	print_str("\t-USE AT YOUR OWN RISK-\t\t *", 1);
	print_str("\t\t\t\t\t *", 1);
	print_str("\t\t\t\t\t *", 1);
	print_str("******************************************", 1);
	print_str("USER is: @", 0);
	print_str(username, 1);
}
