#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "main.h"

/**
 * _putchar - Helper function to write a single character to stdout.
 *
 * @c: The character to be written.
 * Return: On success, returns the number of characters written.
 *         On error, returns -1 and sets errno appropriately.
 */
static int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _print_char - Helper function to print a single character.
 *
 * @args: The va_list containing the character to be printed.
 * Return: The number of characters successfully printed.
 */
static int _print_char(va_list args)
{
	return (_putchar(va_arg(args, int)));
}

/**
 * _print_string - Helper function to print a string.
 *
 * @args: The va_list containing the string to be printed.
 * Return: The number of characters successfully printed.
 */
static int _print_string(va_list args)
{
	char *str = va_arg(args, char *);

	if (str == NULL)
		str = "(null)";

	int count = 0;

	while (*str)
		count += _putchar(*str++);

	return (count);
}

/**
 * _printf - Custom printf function supporting %c, %s
 *
 * @format: A pointer to a string containing the format specifier and optional
 *          text to be printed.
 * @...: Additional arguments to be formatted and printed based on the format
 *       specifier.
 *
 * Return: The total number of characters successfully printed to stdout.
 *         If an error occurs, -1 is returned.
 */
int _printf(const char *format, ...)
{
	if (format == NULL)
		return (-1);

	int count = 0;
	va_list args;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++; /* Move past '%' */
			switch (*format)
			{
				case 'c':
					count += _print_char(args);
					break;
				case 's':
					count += _print_string(args);
					break;
				case '%':
					count += _putchar('%');
					break;
				default:
					count += _putchar('%');
					count += _putchar(*format);
			}
		}
		else
		{
			count += _putchar(*format);
		}
		format++;
	}

	va_end(args);
	return (count);
}

