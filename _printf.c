#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int idx, printed = 0, printed_chars = 0;
    int f, w, p, s, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (idx = 0; format && format[idx] != '\0'; idx++)
    {
        if (format[idx] != '%')
        {
            buffer[buff_ind++] = format[idx];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            /* write(1, &format[idx], 1);*/
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            f = get_flags(format, &idx);
            w = get_width(format, &idx, list);
            p = get_precision(format, &idx, list);
            s = get_size(format, &idx);
            ++idx;
            printed = handle_print(format, &idx, list, buffer,
                f, w, p, s);
            if (printed == -1)
                return (-1);
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add the next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}

