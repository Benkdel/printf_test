#include "main.h"

/**
 * write_bin - prints digit in binary form
 *
 * @arg: list of args
 *
 * Return: length of chars written on Success
 * otherwise, returns 0 or -1
 */
int write_bin(va_list arg, char *main_buffer, unsigned int index, mods *m)
{
	unsigned int number = va_arg(arg, int);
	unsigned int n2 = number, count = 0;

	if(m != NULL)
	{	
		if (m->f > 0)
			index = flags_modifier(main_buffer, index, m);
	}

	while (n2 /= 10)
		count++;
	index = check_overflow(main_buffer, index, count);

	index = convert_base(main_buffer, index, 2, number, 0);
	return (index);
}

/**
 * write_hexa - write hexadecimal number no caps
 *
 * @args: list of args
 *
 * Return: length of chars written on Success
 * otherwise, returns 0 or -1
 */
int write_hexa(va_list args, char *main_buffer, unsigned int index, mods *m)
{
	unsigned int number = va_arg(args, int);
	unsigned int n2 = number, count = 0;
	
	if (m != NULL)
	{
		if (m->f > 0)
		{
			if (number == 0 && m->f > 60)
				index = index;
			else
				index = flags_modifier(main_buffer, index, m);
		}
	}

	while (n2 /= 16)
		count++;
	index = check_overflow(main_buffer, index, count);

	index = convert_base(main_buffer, index, 16, number, 1);
	return (index);
}

/**
 * write_HEXA - write hexadecimal number no caps
 *
 * @args: list of args
 *
 * Return: length of chars written on Success
 * otherwise, returns 0 or -1
 */

int write_HEXA(va_list args, char *main_buffer, unsigned int index, mods *m)
{
	unsigned int number = va_arg(args, int);
	unsigned int n2 = number, count = 0;
	
	if (m != NULL)
	{
		if (m->f > 0)
		{
			if (number == 0 && m->f > 60)
				index = index;
			else
				index = flags_modifier(main_buffer, index, m);
		}
	}

	while (n2 /= 16)
		count++;
	
	index = check_overflow(main_buffer, index, count);

	index = convert_base(main_buffer, index, 16, number, 0);
	return (index);
}

/**
 * write_octal - write octadecimal number
 *
 * @args: list of args
 *
 * Return: length of chars written on Success
 * otherwise, returns 0 or -1
 */
int write_octal(va_list args, char *main_buffer, unsigned int index, mods *m)
{
	unsigned int number = va_arg(args, int);
	unsigned int n2 = number, count = 0;

	if (m != NULL)
	{
		if (m->f > 0)
		{
			if (number == 0 && m->f > 60)
				index = index;
			else
				index = flags_modifier(main_buffer, index, m);
		}
	}

	while (n2 /= 8)
		count++;
	index = check_overflow(main_buffer, index, count);

	index = convert_base(main_buffer, index, 8, number, 0);
	return (index);
}
