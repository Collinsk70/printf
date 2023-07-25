#include "main.h"

/**
 * handle_write_char - Writes a character to the buffer
 * @character: The character to be written
 * @buffer: The buffer array used for printing
 * @flags: The active flags for formatting
 * @width: The width specifier
 * @precision: The precision specifier
 * @size: The size specifier
 *
 * Return: The number of characters printed.
 */
int handle_write_char(char character, char buffer[],
		int flags, int width, int precision, int size)
{
	int charIndex = 0;
	char paddingChar = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		paddingChar = '0';

	buffer[charIndex++] = character;
	buffer[charIndex] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (charIndex = 0; charIndex < width - 1; charIndex++)
			buffer[BUFF_SIZE - charIndex - 2] = paddingChar;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - charIndex - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - charIndex - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Writes a number to the buffer
 * @isNegative: A flag indicating if the number is negative
 * @index: The index at which the number starts in the buffer
 * @buffer: The buffer array used for printing
 * @flags: The active flags for formatting
 * @width: The width specifier
 * @precision: The precision specifier
 * @size: The size specifier
 *
 * Return: The number of characters printed.
 */
int write_number(int isNegative, int index, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char paddingChar = ' ';
	char extraCharacter = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';
	if (isNegative)
		extraCharacter = '-';
	else if (flags & F_PLUS)
		extraCharacter = '+';
	else if (flags & F_SPACE)
		extraCharacter = ' ';

	return (write_num(index, buffer, flags, width, precision,
					  length, paddingChar, extraCharacter));
}

/**
 * write_num - Writes a formatted number to the buffer
 * @index: The index at which the number starts in the buffer
 * @buffer: The buffer array used for printing
 * @flags: The active flags for formatting
 * @width: The width specifier
 * @precision: The precision specifier
 * @length: The number length
 * @paddingChar: The padding character
 * @extraCharacter: The extra character
 *
 * Return: The number of characters printed.
 */
int write_num(int index, char buffer[],
			  int flags, int width, int precision,
			  int length, char paddingChar, char extraCharacter)
{
	int charIndex, paddingStart = 1;

	if (precision == 0 && index == BUFF_SIZE - 2 && 
			buffer[index] == '0' && width == 0)
		return (0); /* No characters are printed for printf(".0d", 0) */
	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = paddingChar = ' '; /* Display padding ' ' */
	if (precision > 0 && precision < length)
		paddingChar = ' ';

	while (precision > length)
		buffer[--index] = '0', length++;

	if (extraCharacter != 0)
		length++;

	if (width > length)
	{
		for (charIndex = 1; charIndex < width - length + 1; charIndex++)
			buffer[charIndex] = paddingChar;

		buffer[charIndex] = '\0';

		if (flags & F_MINUS && paddingChar == ' ') /* Assign extra buffer */
		{
			if (extraCharacter)
				buffer[--index] = extraCharacter;
			return (write(1, &buffer[index], length) + write(1, 
						&buffer[1], charIndex - 1));
		}
		else if (!(flags & F_MINUS) && paddingChar == ' ')
		{
			if (extraCharacter)
				buffer[--index] = extraCharacter;
			return (write(1, &buffer[1], charIndex - 1) + write(1, 
						&buffer[index], length));
		}
		else if (!(flags & F_MINUS) && paddingChar == '0') /* Extra padding */
		{
			if (extraCharacter)
				buffer[--paddingStart] = extraCharacter;
			return (write(1, &buffer[paddingStart], charIndex - paddingStart) +
					write(1, &buffer[index], length - (1 - paddingStart)));
		}
	}

	if (extraCharacter)
		buffer[--index] = extraCharacter;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsgnd - Writes an unsigned number to the buffer
 * @isNegative: A number indicating if the number is negative
 * @index: The index at which the number starts in the buffer
 * @buffer: The buffer array used for printing
 * @flags: The active flags for formatting
 * @width: The width specifier
 * @precision: The precision specifier
 * @size: The size specifier (unused in this context)
 *
 * Return: The number of characters printed.
 */
int write_unsgnd(int isNegative, int index,
				 char buffer[], int flags,
				 int width, int precision, int size)
{
	/* The number is stored at the buffer */
	int length = BUFF_SIZE - index - 1;
	int charIndex = 0;
	char paddingChar = ' ';

	UNUSED(isNegative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0); /* No characters are printed for printf(".0d", 0) */

	if (precision > 0 && precision < length)
		paddingChar = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';

	if (width > length)
	{
		for (charIndex = 0; charIndex < width - length; charIndex++)
			buffer[charIndex] = paddingChar;

		buffer[charIndex] = '\0';

		if (flags & F_MINUS) /* Assign extra character to the left */
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], charIndex));
		}
		else /* Assign extra character to the left of padding [padding > buffer] */
		{
			return (write(1, &buffer[0], charIndex) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * write_pointer - Write a memory address to the buffer
 * @buffer: Array of characters
 * @index: The index at which the number starts in the buffer
 * @length: The length of the number
 * @width: The width specifier
 * @flags: The flags specifier
 * @paddingChar: The character representing the padding
 * @extraCharacter: The character representing the extra character
 * @paddingStart: The index at which the padding should start
 *
 * Return: The number of characters printed.
 */
int write_pointer(char buffer[], int index, int length,
				  int width, int flags,
				  char paddingChar, char extraCharacter, int paddingStart)
{
	int charIndex;

	if (width > length)
	{
		for (charIndex = 3; charIndex < width - length + 3; charIndex++)
			buffer[charIndex] = paddingChar;

		buffer[charIndex] = '\0';

		if (flags & F_MINUS && paddingChar == ' ') /* Assign extra */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraCharacter)
				buffer[--index] = extraCharacter;
			return (write(1, &buffer[index], length) + write(1, 
						&buffer[3], charIndex - 3));
		}
		else if (!(flags & F_MINUS) && paddingChar == ' ') /* Extra character */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraCharacter)
				buffer[--index] = extraCharacter;
			return (write(1, &buffer[3], charIndex - 3) + write(1, 
						&buffer[index], length));
		}
		else if (!(flags & F_MINUS) && paddingChar == '0') /* Extra character */
		{
			if (extraCharacter)
				buffer[--paddingStart] = extraCharacter;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[paddingStart], charIndex - paddingStart) +
					write(1, &buffer[index], BUFF_SIZE - index - 1));
		}
	}

	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extraCharacter)
		buffer[--index] = extraCharacter;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

