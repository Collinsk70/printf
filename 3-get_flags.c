#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @ptr_i: Pointer to an integer that represents the current index.
 * Return: Flags representing active formatting options.
 */
int get_flags(const char *format, int *ptr_i)
{
	/* Flags: - + 0 # ' ' */
	/*       1 2 4 8  16   */

	int x, new_i;
	int flags = 0;
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};

	for (new_i = *ptr_i + 1; format[new_i] != '\0'; new_i++)
	{
		for (x = 0; FLAGS_CH[x] != '\0'; x++)
		{
			if (format[new_i] == FLAGS_CH[x])
			{
				flags |= FLAGS_ARR[x];
				break;
			}
		}

		if (FLAGS_CH[x] == 0)
			break;
	}

	*ptr_i = new_i - 1;

	return (flags);
}

