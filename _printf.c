#include "main.h"

/**
 * _printf - function like as printf in c
 * @format: string
 *
 * Return: length of strinf print
 */
int _printf(const char *format, ...)
{
	char *main_buffer;
	mods *actModes = malloc(sizeof(mods));
	int i = 0, state = 0, sub_state = 0;
	unsigned int index = 0;
	va_list arg;
	int (*chosen_fun)(va_list, char *, unsigned int, mods*);

	actModes->f = 0, actModes->l = 0, actModes->p = 0;
	/* reserve memory for main buffer - 1024 bytes */
	main_buffer = (char *)malloc(sizeof(char) * BUFFERSIZE);
	if (main_buffer == NULL)
		return (-1);

	if (format == NULL || (format[i] == '%' && format[i + 1] == '\0'))
	{
		free(main_buffer);
		free(actModes);
		return (-1);
	}

	va_start(arg, format);
	for (i = 0; format[i];)
	{
		switch (state)
		{
		case NORM_STATE:
			switch (format[i])
			{
			case '%':
				state = FORM_STATE;
				i++;
				break;
			default:
				index = push_char(main_buffer, format[i], index);
				i++;
				break;
			}
			break;

		case FORM_STATE:
			if (format[i] == '%')
			{
				index = push_char(main_buffer, '%', index);
				state = NORM_STATE, i++;
			}
			else
			{

				sub_state = check_sub_state(format[i]);
				switch (sub_state)
				{
				case FLAGS_SUB_STATE:
					actModes->f = get_sub_mod(format[i], sub_state);
					i++;
					break;

				case PREC_SUB_STATE:
					actModes->p = get_sub_mod(format[i], sub_state);
					i++;
					break;

				case LEN_SUB_STATE:
					actModes->f = get_sub_mod(format[i], sub_state);
					i++;
					break;

				default:
					state = NORM_STATE;
					chosen_fun = get_format_func(format, i);
					if (chosen_fun != NULL)
					{
						if (actModes->f == FLAGS_SHARP)
							actModes->f = check_sharp_state(format[i]);
						index = chosen_fun(arg, main_buffer, index, actModes);
					}
					else if (format[i + 1] != '\0')
					{
						index = push_char(main_buffer, format[i - 1], index);
						i--;
					}
					else
						return (-1);
					i++;
					break;
				}
			}
			break;
		default:
			i++;
			break;
		}
	}
	va_end(arg);

	if (state != NORM_STATE && sub_state != SPEC_SUB_STATE)
	{
		free(main_buffer);
		free(actModes);
		return (-1);
	}
	
	/* print remaining data on buffer */
	write_buffer(main_buffer, index);
	free(main_buffer);
	free(actModes);
	if (format[i] == '\0')
		return (index);
	else
		return (-1);
}
