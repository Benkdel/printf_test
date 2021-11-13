#include "main.h"

/**
 * gargabe_collector - validates and cleans memory if necessary
 *
 * @m_buffer: main data structure
 * @format: string passed
 *
 * Return: 0 if all is ok / -1 if not
 */
int gargabe_collector(struct main_buffer *m_buffer, const char *format)
{
	if (m_buffer->buffer_data == NULL)
		return (-1);

	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
	{
		free(m_buffer->buffer_data);
		return (-1);
	}
	return (0);
}
