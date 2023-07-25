#include "main.h"

/**
 * get_width - Extracts the width value from the format string.
 * @format: The formatted string to check for width.
 * @i: Pointer to the current position in the format string.
 * @list: The va_list of arguments.
 *
 * Return: The width value.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width = width * 10 + (format[curr_i] - '0');
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
	}

	*i = curr_i - 1;

	return (width);
}

