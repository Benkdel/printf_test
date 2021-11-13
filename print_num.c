#include "main.h"

/**
 * write_num - prints an integer.
 * @args: argument
 *
 * Return: length of chars printed
 */
int write_num(va_list args, char *main_buffer, unsigned int index, mods *m)
{
	int number = va_arg(args, int);
	int n2 = number;
	unsigned int count = 0;
	
	if (number < 0)
	{
		number *= -1;
		index = check_overflow(main_buffer, index, count);
		index = push_char(main_buffer, '-', index);
		m->f = 0;
	}
	
	if (m != NULL)
	{
		if (m->f > 0)
			index = flags_modifier(main_buffer, index, m);
	}
	while (n2 /= 10)
		count++;

	index = check_overflow(main_buffer, index, count);
	index = convert_base(main_buffer, index, 10, number, 0);
	return (index);
}

/**
 * write_unint - print unsigned int
 * @arg: string arguments
 *
 * Return: length write
 */
int write_unint(va_list arg, char *main_buffer, unsigned int index, mods *m)
{
	unsigned long int number = va_arg(arg, unsigned long int);
	unsigned int n2 = number, count = 0;
	
	if (m != NULL)
	{
		if (m->f > 0)
			index = flags_modifier(main_buffer, index, m);
	}
	
	while (n2 /= 10)
		count++;
	
	index = check_overflow(main_buffer, index, count);
	index = convert_base(main_buffer, index, 10, number, 0);

	return (index);
}
