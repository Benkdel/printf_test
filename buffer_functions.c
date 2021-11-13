#include "main.h"

/**
 * push_char - pushes char into main buffer
 *
 * @main_buffer: main buffer to store data
 * @c: character to be push into buffer
 * @index: position
 *
 * Return: updated index after last push
 */
unsigned int push_char(char *main_buffer, char c, unsigned int index)
{
	if (main_buffer == NULL)
	{
		free(main_buffer);
		return (0);
	}

	main_buffer[index] = c;
	index++;
	return (index);
}

/**
 * write_buffer - write data reserved in main buffer
 *
 * @main_buffer: main buffer string
 * @data_size: size of valid data to print in bytes
 *
 * Return: write into standard output
 */
unsigned int write_buffer(char *main_buffer, unsigned int data_size)
{
	return (write(1, main_buffer, data_size));
}

/**
 * check_overflow - checks if new size is bigger than BUFFERSIZE
 * and reset if necessary
 * @main_buffer: main buffer string
 * @index: current index of data
 *
 * Return: 0 (Success)
 */
int check_overflow(char *main_buffer, unsigned int index, unsigned int new_bytes)
{
	int _overflow = ((int)index + (int)new_bytes - BUFFERSIZE);

	if (_overflow >= 0)
	{
		write_buffer(main_buffer, index);
		return (0);
	}
	else
	{
		return (index);
	}
}
