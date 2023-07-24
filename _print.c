#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "main.h"

/**
 * _putchar - Helper function to write a single character to stdout.
 *
 * @c: The character to be written.
 * Return: On success, returns the number of characters written.
 * On error, returns -1 and sets errno appropriately.
 */
static int _putchar(char c)
{
    return write(1, &c, 1);
}

/**
 * _printf - Custom printf function supporting %c, %s, and %% conversion specifiers.
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
    int count = 0;
    va_list args;

    if (format == NULL)
        return -1;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++; // Move past '%'
            switch (*format)
            {
                case 'c':
                    count += print_char(args);
                    break;
                case 's':
                    count += print_str(args);
                    break;
                case '%':
                    count += print_percent(args);
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
    return count;
}

