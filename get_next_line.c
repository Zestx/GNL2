/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2018/12/03 19:50:18 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void		*ft_realloc(char *buffer, int old_size, int new_size)
{
	char *new_buffer;

	new_buffer = malloc(new_size);
	if (!new_buffer)
		return (NULL);
	if (old_size)
	{
		ft_memcpy(new_buffer, buffer, old_size);
		free(buffer);
	}
	return (new_buffer);
}

static int		read_buffer(int fd, t_buffer *buff)
{
	int n;

	if ((buff->start < buff->end))
		return (1);
	n = read(fd, buff->rd, BUFF_SIZE);
	printf("READ RETURN: %d\n", n);
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	buff->start = 0;
	buff->end = n;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_buffer	buff;
	t_util			ut;

	ut.ptr = NULL;
	ut.curr_size = 0;
	while (!ut.ptr)
	{
		if ((ut.n = read_buffer(fd, &buff)) <= 0)
			return (ut.n);
		ut.ptr = ft_memchr(&buff.rd[buff.start], SP, buff.end - buff.start);
		if (!ut.ptr)
			ut.size = buff.end - buff.start;
		else
		{
			*ut.ptr = '\0';
			ut.size = (ut.ptr - buff.rd) - buff.start + 1;
		}
		if (!(*line = ft_realloc(*line, ut.curr_size, ut.curr_size + ut.size)))
			return (-1);
		ft_memcpy(*line + ut.curr_size, &buff.rd[buff.start], ut.size);
		ut.curr_size += ut.size;
		buff.start += ut.size;
	}
	return (1);
}
