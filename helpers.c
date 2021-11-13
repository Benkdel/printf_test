#include "main.h"

/**
 * _strlen - length
 * @s: string
 * Return: length string
 */
int _strlen(char *s)
{
	int len = 0;

	while (*(s + len) != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * _strncpy - copy a string into another
 * @dest: string dest
 * @src: string src
 * @n: number of bytes to get from dest
 *
 * Return: pointer to string dest
 *
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';
	return (dest);
}

/**
 * convert_base - print number as chars converting to any base
 *
 * @base: number base convert
 * @num: number a convert
 * @h: Hexadecimal Caps
 *
 * Return: none - void function
 */
void convert_base(struct main_buffer *m_buffer, int base, unsigned int num, int h)
{
	unsigned int n = num, count = 1;
	char *temp, buf[17], *ptr;
	int i = 0, j = 0;

	_strncpy(buf, (h == 0) ? "0123456789ABCDEF" : "0123456789abcdef", 17);
	if (n == 0)
	{
		push_char(m_buffer, '0');
	}
	while (n /= base)
		count++;
	temp = malloc(sizeof(char) * (count + 1));
	if (temp == NULL)
	{
		free(temp);
	}
	ptr = &temp[count], *ptr = '\0', ptr--;
	while (num > 0)
	{
		*ptr = buf[num % base];
		num = num / base;
		ptr--, i++;
	}
	while (i > 0)
	{
		push_char(m_buffer, temp[j]);
		j++, i--;
	}
	free(temp);
}
void reverse_string(struct main_buffer *m_buffer, char *str)
{
	int x = 0;
	while (*(str + x))
		x++;
	for (x = x - 1; x >= 0; x--)
	{
		push_char(m_buffer, str[x]);		
	}
}

/**
 * check_state - checks correspondant state for each char
 *
 * @c: char to be evaluated
 *
 * Return: STATE
 *
 */
int check_state(char c)
{
	if (c == '%')
		return (FORM_STATE);
	else
		return (NORM_STATE);
}

/**
 * check_sub_state - checks correspondant sub state for each char
 * 
 * @c: char to be evaluated
 * 
 * Return: SUB STATE
 * 
 */
int check_sub_state(char c)
{
	switch (c)
	{
	case '+':
	case ' ':
	case '#':
		return (FLAGS_SUB_STATE);
		break;

	case 'l':
	case 'h':
		return (LEN_SUB_STATE);
		break;

	case '.':
		return (PREC_SUB_STATE);
		break;
	default:
		return (SPEC_SUB_STATE);
		break;
	}
	return (-1);
}

/**
 * check_sharp_state - checks correspondant sharp state
 * 
 * @c: char to be evaluated
 * 
 * Return: sharp state = 61, 62 or 63 (octal, hexa or HEXA)
 * 
 */
int check_sharp_state(char c)
{
	switch (c)
	{
	case 'o':
		return (FLAGS_SHARP_OCTAL);
		break;

	case 'x':
		return (FLAGS_SHARP_HEXA);
		break;

	case 'X':
		return (FLAGS_SHARP_HEXA_CAPS);
		break;
	default:
		return (SPEC_SUB_STATE);
		break;
	}
	return (-1);
}

/**
 * flags_modifier - adds modifier accordin to flags: +, space or #
 * @main_buffer: main buffer storing data
 * @index: index of last written char
 * @f: flag
 * 
 * Return: none - void function
 */
void flags_modifier(struct main_buffer *m_buffer)
{
	if (m_buffer != NULL)
	{
		switch (m_buffer->f)
		{
		case FLAGS_PLUS:
			check_overflow(m_buffer, 1);
			push_char(m_buffer, '+');
			break;
		
		case FLAGS_SPACE:
			check_overflow(m_buffer, 1);
			push_char(m_buffer, ' ');
			break;
		
		case FLAGS_SHARP_OCTAL:
			check_overflow(m_buffer, 1);
			push_char(m_buffer, '0');
			break;

		case FLAGS_SHARP_HEXA:
			check_overflow(m_buffer, 1);
			push_char(m_buffer, '0');
			check_overflow(m_buffer, 1);
			push_char(m_buffer, 'x');
			break;

		case FLAGS_SHARP_HEXA_CAPS:
			check_overflow(m_buffer, 1);
			push_char(m_buffer, '0');
			check_overflow(m_buffer, 1);
			push_char(m_buffer, 'X');
			break;
			
		default:
			break;
		}
	} 
}

