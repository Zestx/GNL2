/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/

//2.5.End of the function, if everything went right
//
////2.5.End of the function, if everything went right..*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2018/12/05 19:38:45 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		*ft_realloc(char *line, int old_size, int new_size)
{
	char *new_line;

	//5.1.Allocating the new buffer new_size bytes. and testing if it went right.
	new_line = malloc(new_size + 1);
	if (!new_line)
		return (NULL);

	//5.2.This "realloc" part is only needed if *line is not empty.
	//	  The content of the line is copied into the new buffer,
	//	  A '\0' is set at the end: The reason for this is if the file
	//	  doesn't contain a '\n' (or separator) at the end, we can't
	//	  set it using ut.p since it will always be null.
	//	  The old line is then freed.
	if (old_size)
	{
		ft_memcpy(new_line, line, old_size);
		new_line[new_size] = '\0';
		free(line);
	}

	//5.3.End of the function, if the allocation went right.
	return (new_buffer);
}

static int		read_buffer(int fd, t_buffer *b)
{
	int n;

	//2.1. ????
	if ((b->str < b->end))
		return (1);

	//2.2.We read the file into b.rd.
	n = read(fd, b->rd, BUFF_SIZE);

	//2.3.Check for error or EOF.
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);

	//2.4.Updating the indexes, end should be the index of the last byte read into the buffer.
	b->str = 0;
	b->end = n;

	//2.5.End of the function, if everything went right.
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	//Declaring an array of t_buffer as static for the need of not being reset at each 
	//call of get_next_line. We use an array to handle multiple fd alternatively.
	//The t_buffer "object" is called 'b'.
	//The t_util u contain every "utilitarian" variables.
	static t_buffer	b[1000];
	t_util			u;

	u.p = NULL;
	u.curr_size = 0;
	//0.Check if the fd and if line is not null.
	if (fd < 0 || !line)
		return (-1);
	//1.The loop is taken as long as there is no '\n' (or any Separator) in the buffer.
	while (!u.p)
	{
		//2.The file is read by read_buffer() into b[fd]. if its return value (ret) is 0,
		//	get_next_line will return either 1 if something was read before, or 0 if not.
		//	If this value is negative (error), get_next_line will return -1.
		//	>The reason for this is that if there isnt a '\n' or Separator at the end of
		//	 the file, the loop will always evaluate to True so we need to check if something
		//	 was read or not the last time.
		if ((u.n = read_buffer(fd, &b[fd])) <= 0)
			return (u.n ? u.n : u.curr_size != 0);

		//3.Here we're looking for a '\n' (or separator) in the buffer, from buffer[start].
		//	If none is found, size = start - end.
		//	>The reason for that size should represent the "distance" between the end of the
		//	 last line in the buffer(wich is buffer[start] to the end of the buffer).
		if (!(u.p = ft_memchr(&b[fd].rd[b[fd].str], S, b[fd].end - b[fd].str)))
			u.size = b[fd].end - b[fd].str;

		//4.If a '\n' (or separator) was found, u.p points to it and we replace it with a '\0'.
		//	We set size to (the index of u.p in the buffer) - (the start of the buffer, or 
		//	of the start of the current line in the buffer (b.str)).
		else
		{
			*u.p = '\0';
			u.size = (u.p - b[fd].rd) - b[fd].str + 1;
		}
		//5.The *line is (re)allocated using ft_realloc(), and the buffer (b.rd) is copied into it.
		//  we copy: .From rd.str, since str is either 0 or the index or the start of the current line 
		//  		  in the buffer.
		//         : .To (*line + curr_size) since curr_size represent the full size of the *line 
		//  		  the last time we copied the buffer into it.
		//  The new size of *line should be it's current size + the size of the buffer or the line in it.
		//  The result of ft_realloc is tested, and if the allocation failed, get_next_line returns -1.
		if (!(*line = ft_realloc(*line, u.curr_size, u.curr_size + u.size)))
			return (-1);
		ft_memcpy(*line + u.curr_size, &b[fd].rd[b[fd].str], u.size);

		//6.The current size is updated to it's current value + the size of the line / buffer.
		//	The start index is also updated to "point" to the end of the last line.
		u.curr_size += u.size;
		b[fd].str += u.size;
	}
	//7. End of the function, if everything went right.
	return (1);
}
