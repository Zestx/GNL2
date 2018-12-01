/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/22 18:56:10 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void *ft_realloc(char *buffer, int old_size, int new_size)
{
	char *new_buffer;

	new_buffer = malloc(new_size);
	if (!new_buffer)
		return (NULL);
	//If the buffer is null, this part is useless
	if (old_size) {
		ft_memcpy(new_buffer, buffer, old_size);
		free(buffer);
	}
	return (new_buffer);
}

struct buff {
	char	buffer[BUFF_SIZE];
	int	start;
	int	end;
};

static int read_buffer(int fd, struct buff *buffer)
{
	int n;

	if ((buffer->start < buffer->end))
		return 1;

	n = read(fd, buffer->buffer, BUFF_SIZE);
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	buffer->start = 0;
	buffer->end = n;
	return 1;
}

int get_next_line(const int fd, char **line)
{
	static struct buff buffer;
	char *ptr;
	int curr_size;
	int size;
	int n;

	ptr = NULL;
	curr_size = 0;
	while (!ptr)			//While there's no '\n' read..
	{
		if ((n = read_buffer(fd, &buffer)) <= 0)
			return n;
		ptr = ft_memchr(&buffer.buffer[buffer.start], '\n', buffer.end - buffer.start);
		if (!ptr)
			size = buffer.end - buffer.start;
		else
		{
			*ptr = '\0';
			size = (ptr - buffer.buffer) - buffer.start + 1;
		}
		*line = ft_realloc(*line, curr_size, curr_size + size);
		ft_memcpy(*line + curr_size, &buffer.buffer[buffer.start], size);
		curr_size += size;
		buffer.start += size;
	}
	return (1);
}
