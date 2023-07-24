#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Custom printf function
 *
 * This function emulates the behavior of the standard printf function, allowing
 * formatted output to be printed to the standard output (stdout). It supports
 * the following format specifiers:
 *
 *   %c - Character: Prints a single character.
 *   %d - Decimal: Prints a signed integer in decimal format.
 *   %i - Integer: Same as %d, prints a signed integer in decimal format.
 *   %s - String: Prints a null-terminated string of characters.
 *   %R - ROT13 Encode: Prints a string encoded in ROT13 format.
 *   %r - Reverse String: Prints a string in reverse order.
 *
 * @format: A pointer to a string containing the format specifier and optional
 *          text to be printed.
 * @...: Additional arguments to be formatted and printed based on the format
 *       specifier.
 *
 * Return: The total number of characters successfully printed to stdout.
 *         If an error occurs, -1 is returned.
 *
 * Example:
 *     _printf("Hello, %s! My age is %d.\n", "Alice", 30);
 *
 * This function will print:
 *     "Hello, Alice! My age is 30."
 */
int _printf(const char *format, ...)
{
	int idx, jdx, total_count, found;
	va_list arg_list;
	set print_functions[] = {
		{'c', print_char},
		{'d', print_d},
		{'i', print_d},
		{'s', print_str},
		{'R', print_rot13},
		{'r', print_rev},
	};

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);

	total_count = 0;

	for (idx = 0; *(format + idx); idx++)
	{
		if (*(format + idx) == '%')
		{
			if (*(format + idx + 1) == '\0')
				continue;
			found = 0;

			for (jdx = 0; jdx < 6; jdx++)
			{
				if (*(format + idx + 1) == print_functions[jdx].spec)
				{
					total_count += print_functions[jdx].print(arg_list);
					found = 1;
					format++;
					break;
				}
			}

			if (found != 1)
			{
				if (*(format + idx + 1) == '%')
				{
					total_count += write(1, "%", 1);
					format++;
				}
				else
					total_count += write(1, (format + idx), 1);
			}
		}
		else
		{
			total_count += write(1, (format + idx), 1);
		}
	}
	va_end(arg_list);

	return (total_count);
}

