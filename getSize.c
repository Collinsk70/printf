#include "main.h"

/**
 * get_size - Determines the size of the argument type specifier
 * @format: Formatted string containing the arguments
 * @ptr_n: Pointer to an integer that represents the current inde
 *
 * Return: Size of the argument type specifier.
 */
int get_size(const char *format, int *ptr_n)
{
	int index = *ptr_n + 1;
	int size = 0;

	/* Check if the argument type specifier is 'l' for long */
	if (format[index] == 'l')
		size = S_LONG;
	/* Check if the argument type specifier is 'h' for short */
	else if (format[index] == 'h')
		size = S_SHORT;

	/* If size is still 0, there was no valid argument type specifier */
	if (size == 0)
		*ptr_n = index - 1;
	else
		*ptr_n = index;

	return (size);	/* Parentheses added for clarity */
}

