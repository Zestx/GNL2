/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2018/12/05 17:58:27 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void		*ft_realloc(char *buffer, int old_size, int new_size)
{
	char *new_buffer;

	new_buffer = malloc(new_size + 1);
	if (!new_buffer)
		return (NULL);
	if (old_size)
	{
		ft_memcpy(new_buffer, buffer, old_size);
		new_buffer[new_size] = '\0';
		free(buffer);
	}
	return (new_buffer);
}

static int		read_buffer(int fd, t_buffer *buff)
{
	int n;

	if ((buff->str < buff->end))
		return (1);
	n = read(fd, buff->rd, BUFF_SIZE);
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	buff->str = 0;
	buff->end = n;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_buffer	b[1000];
	t_util			u;

	u.p = NULL;
	u.curr_size = 0;
	if (fd < 0 || !line)
		return (-1);
	while (!u.p)
	{
		if ((u.n = read_buffer(fd, &b[fd])) <= 0)
			return (u.n ? u.n : u.curr_size != 0);
		if (!(u.p = ft_memchr(&b[fd].rd[b[fd].str], S, b[fd].end - b[fd].str)))
			u.size = b[fd].end - b[fd].str;
		else
		{
			*u.p = '\0';
			u.size = (u.p - b[fd].rd) - b[fd].str + 1;
		}
		if (!(*line = ft_realloc(*line, u.curr_size, u.curr_size + u.size)))
			return (-1);
		ft_memcpy(*line + u.curr_size, &b[fd].rd[b[fd].str], u.size);
		u.curr_size += u.size;
		b[fd].str += u.size;
	}
	return (1);
}
