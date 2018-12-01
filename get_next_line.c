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

int get_next_line(const int fd, char **line)
{
	static char buffer[BUFF_SIZE];
	char *ptr;
	int curr_size;
	int size;
	static int start;
	static int end;

	ptr = NULL;
	curr_size = 0;

	//If the buffer is empty..
	while (!ptr)			//While there's no '\n' read..
	{
		if ((start == end)) {
			int n = read(fd, buffer, BUFF_SIZE);
			if (n < 0)
				return -1;
			if (n == 0)
				return 0;
			start = 0;
			end = n;
		}
		ptr = ft_memchr(&buffer[start], '\n', end - start);
		if (!ptr) {
			size = end - start;
		} else {
			*ptr = '\0';
			size = (ptr - buffer) - start + 1;
		}
		*line = ft_realloc(*line, curr_size, curr_size + size);
		ft_memcpy(*line + curr_size, &buffer[start], size);
		curr_size += size;
		start += size;
	}

	return (1);
}
