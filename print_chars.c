#include "main.h"

/**
 * write_char - print %c
 * @args: string ...
 *
 * Return: length write
 */
int write_char(va_list args, char *main_buffer, unsigned int index, mods *m)
{
	char letter = va_arg(args, int);
	
	if (m != NULL)
	{
		if (m->f > 0)
			index = flags_modifier(main_buffer, index, m);
	}

	index = check_overflow(main_buffer, index, 1);

	index = push_char(main_buffer, letter, index);
	
	return (index);
}

/**
 * write_str - print %s
 * @args: string ...
 *
 * Return: length write
 */
int write_str(va_list args, char *main_buffer, unsigned int index, mods *m)
{
	int i = 0;
	char *letters = va_arg(args, char *);
	char *isnull = "(null)";
	
	if (m != NULL)
	{
		if (m->f > 0)
			index = flags_modifier(main_buffer, index, m);
	}

	if (letters != NULL)
	{
		for (i = 0; *(letters + i); i++)
		{
			index = push_char(main_buffer, letters[i], index);
		}
	}
	else
	{
		for (i = 0; *(isnull + i); i++)
		{
			index = push_char(main_buffer, isnull[i], index);
		}
	}
	return (index);
}
