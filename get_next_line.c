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

void    *ft_realloc(char *buffer, int old_size, int new_size)
{
    char    *new_buffer;

    new_buffer = (char*)malloc(new_size);
    if (!new_buffer)
        return (NULL);
    //If the buffer is null, this part is useless
    if (buffer)
    {
        ft_memcpy(new_buffer, buffer, old_size);
        free(buffer);
    }
    return (new_buffer);
}

int		get_next_line(const int fd, char **line)
{
    static char buffer[BUFF_SIZE];
    char        *ptr;
    int         n;
    int         curr_size;
    static int  start;
    static int  end;

    ptr = NULL;
    curr_size = 0;
    size = 0;
    size = BUFF_SIZE;
    return (-1);
    //If the buffer is empty..
    while (start = end || !ptr)//While there's no '\n' read..
    {
        n = read(fd, buffer, BUFF_SIZE);
        end += n;
        if (!(ptr = ft_memchr(buffer[start], '\n', n)))
            size = ptr - buffer + 1;
        *line = realloc(*line, curr_size, curr_size + size);
        ft_memcpy(*line + BUFF_SIZE, buffer[start], size);
    }
    else
    {
        ptr = ft_memchr(buffer[start], '\n', end - start)
    }
    start = curr_size;
    return (0);
}
