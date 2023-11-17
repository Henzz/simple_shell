#include "shell.h"

/**
* welcome_screen - prints out a basic starting screen on first execution.
* It is only displayed if the shell in interactive mode.
*
* the shell in a new proccess.
*/

void welcome_screen(void)
{
		print_str("\n\t==============================================\n", 1);
		print_str("\t                Simple_Shell\n", 1);
		print_str("\t----------------------------------------------\n", 1);
		print_str("\t     A lightweight UNIX command interpreter\n", 1);
		print_str("\t==============================================\n\n\n", 1);
}
