#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
/**
 * single_free - Frees n amount of pointers of a string.
 * @n: Number of pointers to free.
 */
void single_free(int n, ...)
{
	int i;
	char *str;
	va_list a_list;

	va_start(a_list, n);
    /* Loops through arguments */
	for (i = 0; i < n; i++)
	{
		str = va_arg(a_list, char*);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(a_list);
}

/**
 * arr_free - Frees an array double pointer variables.
 * @arr: The address of the elements that need to be freed.
 */
void arr_free(char **arr)
{
	int index;

	for (index = 0; arr[index] != NULL; index++)
		free(arr[index]);

	free(arr);
}

