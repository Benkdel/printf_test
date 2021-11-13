#include "main.h"

/**
 * _printf - function like as printf in c
 * @format: string
 *
 * Return: length of strinf print
 */
int _printf(const char *format, ...)
{
	struct main_buffer m_buffer;
	va_list arg;
	void (*chosen_fun)(va_list, struct main_buffer *m_buffer);
	int i = 0, state = 0, sub_state = 0;

	m_buffer.index = 0, m_buffer.len = 0, m_buffer.f = 0, m_buffer.p = 0;
	m_buffer.l = 0, m_buffer.buffer_data = malloc(sizeof(char) * BUFFERSIZE);
	if (gargabe_collector(&m_buffer, format) < 0)
		return (-1);
	va_start(arg, format);
	for (i = 0; format[i]; i++)
	{
		switch (state)
		{
		case NORM_STATE:
			switch (format[i])
			{
			case '%':
				state = FORM_STATE;
				break;
			default:
				push_char(&m_buffer, format[i]);
				break;
			}
			break;

		case FORM_STATE:
			if (format[i] == '%')
			{
				push_char(&m_buffer, '%'), state = NORM_STATE;
			}
			else
			{
				sub_state = check_sub_state(format[i]);
				switch (sub_state)
				{
				case FLAGS_SUB_STATE:
					m_buffer.f = get_sub_mod(format[i], sub_state);
					break;

				case PREC_SUB_STATE:
					m_buffer.p = get_sub_mod(format[i], sub_state);
					break;

				case LEN_SUB_STATE:
					m_buffer.f = get_sub_mod(format[i], sub_state);
					break;

				default:
					state = NORM_STATE, chosen_fun = get_format_func(format, i);
					if (chosen_fun != NULL)
					{
						if (m_buffer.f == FLAGS_SHARP)
							m_buffer.f = check_sharp_state(format[i]);
						chosen_fun(arg, &m_buffer);
					}
					else if (format[i + 1] != '\0')
					{
						push_char(&m_buffer, format[i - 1]), i--;
					}
					else
						return (-1);
					break;
				}
			}
			break;
		}
	}
	va_end(arg);
	if (state != NORM_STATE && sub_state != SPEC_SUB_STATE)
	{
		free(m_buffer.buffer_data); return (-1);
	}
	write_buffer(&m_buffer);
	free(m_buffer.buffer_data);
	if (format[i] == '\0')
		return (m_buffer.len);
	else
		return (-1);
}
