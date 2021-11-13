#include "main.h"

/**
 * *get_format_func - evaluates which function is correct for each format
 *
 * @format: user input format
 * @p: pos
 *
 * Return: pointer to function format
 *
 */

void (*get_format_func(const char *format, int p))(va_list, struct main_buffer *m_buffer)
{
	f_print func[] = {
		{"c", write_char},
		{"s", write_str},
		{"d", write_num},
		{"i", write_num},
		{"b", write_bin},
		{"x", write_hexa},
		{"X", write_HEXA},
		{"o", write_octal},
		{"u", write_unint},
		{NULL, NULL}
	};

	int i;

	i = 0;
	while (i < 9)
	{
		if (format[p] == func[i].fo[0])
			return (func[i].write_fun);
		i++;
	}
	return (NULL);
}
