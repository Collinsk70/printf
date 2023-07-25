#include "main.h"

/**
 * handle_print - Handles printing of an argument based on its type.
 * @format: Formatted string containing the arguments.
 * @args_list: List of arguments to be printed.
 * @ptr_index: Pointer to the current index in the format string.
 * @buffer: Buffer array to handle print.
 * @flags: Active formatting flags.
 * @width: Width specification.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handle_print(const char *format, va_list args_list,
		int *ptr_index, char buffer[],
	int flags, int width, int precision, int size)
{
	int type_index, length = 0, result = -1;
	fmt_t ptr_fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexa},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	/* Loop through the format types to find a match */
	for (type_index = 0; ptr_fmt_types[type_index].fmt != '\0'; type_index++)
	{
		if (format[*ptr_index] == ptr_fmt_types[type_index].fmt)
		{
			/* Call the corresponding printing function */
			return (ptr_fmt_types[type_index].fn(args_list, buffer,
					       flags, width, precision, size));
		}
	}

	/* If no matching format specifier is found */
	if (ptr_fmt_types[type_index].fmt == '\0')
	{
		/* Check if the format string is at its end */
		if (format[*ptr_index] == '\0')
		{
			return (-1);
		}

		/* Print a single '%' character */
		length += write(1, "%%", 1);

		/* If the previous character in format string is a space */
		if (format[*ptr_index - 1] == ' ')
		{
			length += write(1, " ", 1);
		}
		/* If width is specified, handle its case */
		else if (width)
		{
			--(*ptr_index);
			while (format[*ptr_index] != ' ' && format[*ptr_index] != '%')
			{
				--(*ptr_index);
			}

			if (format[*ptr_index] == ' ')
			{
				--(*ptr_index);
			}
			return (1);
		}

		/* Print the unknown character following '%' */
		length += write(1, &format[*ptr_index], 1);
		return (length);
	}

	return (result);
}

