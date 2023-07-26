#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @ind: ind.
 * @list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int index, unknown_length = 0, chars_printed = -1;
	fmt_t fmt_types[] = {
		{'c', print_character},
		{'s', print_string}, {'%', print_percent},
		{'i', print_integer},
		{'d', print_integer},
		{'b', print_binary},
		{'u', print_unsigned},
		{'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper},
		{'p', print_ptr}, {'S', print_non_printable_chars},
		{'r', print_reversed_string}, {'R', print_rot13_string}, {'\0', NULL}
	};
	
	for (index = 0; fmt_types[index].fmt != '\0'; index++)
		if (fmt[*ind] == fmt_types[index].fmt)
			return (fmt_types[index].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[index].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknown_length += write(1, &fmt[*ind], 1);
		return (unknown_length);
	}
	return (chars_printed);
}

