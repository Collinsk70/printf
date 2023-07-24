#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

/**
 * struct specifier - Struct to store format specifiers and their corresponding
 *                     printing functions.
 *
 * @spec: The format specifier character.
 * @print: The function pointer to the corresponding printing function.
 */
typedef struct specifier
{
    char spec;
    int (*print)(va_list);
} set;

/* Function prototypes */
int _printf(const char *format, ...);
int print_char(va_list args);
int print_str(va_list args);
int print_percent(va_list args);

#endif /* MAIN_H */

