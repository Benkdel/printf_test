#include "main.h"

/**
 * push_char - pushes char into main buffer
 *
 * @main_buffer: main buffer to store data
 * @c: character to be push into buffer
 * @index: position
 *
 * Return: none - void function
 */
void push_char(struct main_buffer *m_buffer, char c)
{
	if (m_buffer == NULL)
	{
		free(m_buffer->buffer_data);
	}

	m_buffer->buffer_data[m_buffer->index] = c;
	m_buffer->len++;
	m_buffer->index++;
}

/**
 * write_buffer - write data reserved in main buffer
 *
 * @main_buffer: main buffer string
 * @data_size: size of valid data to print in bytes
 *
 * Return: none - void function
 */
void write_buffer(struct main_buffer *m_buffer)
{
	write(1, m_buffer->buffer_data, m_buffer->index);
}

/**
 * check_overflow - checks if new size is bigger than BUFFERSIZE
 * and reset if necessary
 * @main_buffer: main buffer string
 * @index: current index of data
 * Return: none - void
 *
 */
void check_overflow(struct main_buffer *m_buffer, unsigned int new_bytes)
{
	int _overflow = ((int)m_buffer->index + (int)new_bytes - BUFFERSIZE);

	if (_overflow >= 0)
		write_buffer(m_buffer);
}
