/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 19:41:42 by qbackaer          #+#    #+#             */
/*   Updated: 2018/12/03 17:43:00 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "libft/libft.h"
# define BUFF_SIZE 12
# define SP '\n'

typedef struct	s_buffer
{
	char	rd[BUFF_SIZE];
	int		start;
	int		end;
}				t_buffer;

typedef struct	s_util
{
	char	*ptr;
	int		curr_size;
	int		size;
	int		n;
}				t_util;

int				get_next_line(const int fd, char **line);

#endif
