#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @types: arguments
 * @buffer: print
 * @flags: flags
 * @width: getWidth
 * @precision: PrecisionSpecification
 * @size: SizeSpecifier
 * Return: CharsPrinted.
 */
int print_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num1 = va_arg(types, unsigned long int);

	num1 = convert_size_unsgnd(num1, size);

	if (num1 == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num1 > 0)
	{
		buffer[y--] = (num1 % 10) + '0';
		num1 /= 10;
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints unsigned number using octal notation
 * @types: ListArguments
 * @buffer: handlePrint
 * @flags: activeFlags
 * @width: getWidth
 * @precision: PrecisionSpecification
 * @size: SizeSpecifier
 * Return: charsPrinted
 */
int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num1 = va_arg(types, unsigned long int);
	unsigned long int initial_num = num1;

	UNUSED(width);

	num1 = convert_size_unsgnd(num1, size);

	if (num1 == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num1 > 0)
	{
		buffer[y--] = (num1 % 8) + '0';
		num1 /= 8;
	}

	if (flags & F_HASH && initial_num != 0)
		buffer[y--] = '0';

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - Prints unsigned number using hexadecimalNotation
 * @types: ListArguments
 * @buffer: HandlePrint
 * @flags: CalculatesActive flags
 * @width: getWidth
 * @precision: PrecisionSpecification
 * @size: SizeSpecifier
 * Return: chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
					   flags, 'x', width, precision, size));
}

/**
 * print_hexadecimal - Prints unsigned number using hexadecimalNotation
 * @types: ListArguments
 * @buffer: HandlePrint
 * @flags: CalculatesActive flags
 * @width: getWidth
 * @precision: PrecisionSpecification
 * @size: SizeSpecifier
 * Return: chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
					   flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: ListAarguments
 * @map_to: Array Values to mapNumber
 * @buffer: handlePrint
 * @flags: Calc Active flags
 * @flag_ch: Calc active flags
 * @width: getWidth
 * @precision: PrecisionSpecification
 * @size: SizeSpecifier
 * @size: SizeSpecification
 * Return: CharsPrinted
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num1 = va_arg(types, unsigned long int);
	unsigned long int initial_num = num1;

	UNUSED(width);

	num1 = convert_size_unsgnd(num1, size);

	if (num1 == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num1 > 0)
	{
		buffer[y--] = map_to[num1 % 16];
		num1 /= 16;
	}

	if (flags & F_HASH && initial_num != 0)
	{
		buffer[y--] = flag_ch;
		buffer[y--] = '0';
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

