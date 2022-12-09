/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:09:41 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/09 15:09:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_line(char *full_buff, size_t start_pos, size_t buff_size)
{
	size_t	i;

	i = 0;
	while (i < buff_size && full_buff[start_pos + i] != 0)
	{
		if (full_buff[start_pos + i] == '\n')
		{
			return (start_pos + i + 1);
		}
		i++;
	}
	return (0);
}

t_vector	**get_fd_vector(int fd)
{
	t_vector		*fd_vector;
	static t_vector	*fd_vector_lst[FOPEN_MAX];

	if (fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	fd_vector = fd_vector_lst[fd];
	if (fd_vector == NULL)
	{
		fd_vector = malloc(sizeof(t_vector));
		if (!fd_vector)
			return (NULL);
		fd_vector->capacity = 0;
		fd_vector->size = 0;
		fd_vector->buff = NULL;
		fd_vector_lst[fd] = fd_vector;
	}
	return (&fd_vector_lst[fd]);
}

//return 0 when a newline were already in the buffer
//return 1 when the end of the file is reached and the buffer wasn't empty
//return 2 when the end of the file is reached
//			and the buffer was empty or on error
int	read_until_new_line(int fd, t_vector **fd_vector, size_t *end_line_pos,
		char **buff_out)
{
	int	readed_count;

	if ((fd_vector == NULL) || (*fd_vector) == NULL)
		return (2);
	if (((*fd_vector)->size > 0 && (*fd_vector)->size < BUFFER_SIZE))
		*end_line_pos = check_line((*fd_vector)->buff, 0, BUFFER_SIZE);
	while (*end_line_pos == 0)
	{
		vector_resize_if_needed((*fd_vector), BUFFER_SIZE + 5);
		if ((*fd_vector)->buff == NULL)
			return (2);
		readed_count = read(fd, ((char *)(*fd_vector)->buff
					+ (*fd_vector)->size), BUFFER_SIZE);
		if (readed_count <= 0)
		{
			if ((*fd_vector)->size == 0 || ((char *)(*fd_vector)->buff)[0] == 0)
				return (free_vector(&(*fd_vector)), 2);
			*buff_out = extract_str((*fd_vector)->buff, (*fd_vector)->size, 1);
			return (free_vector(&(*fd_vector)), 1);
		}
		*end_line_pos = check_line((*fd_vector)->buff, (*fd_vector)->size,
				readed_count);
		(*fd_vector)->size += readed_count;
	}
	return (0);
}

// return 1 on error
int	realocate(t_vector **fd_vector, size_t end_line_pos)
{
	char	*buff_ptr;

	buff_ptr = NULL;
	if (((*fd_vector)->size - end_line_pos) <= BUFFER_SIZE)
	{
		buff_ptr = malloc(BUFFER_SIZE + 1 * sizeof(char));
		if (!buff_ptr)
			return (1);
		(*fd_vector)->capacity = BUFFER_SIZE;
	}
	else
	{
		buff_ptr = malloc(((*fd_vector)->size + 1 - end_line_pos)
				* sizeof(char));
		if (!buff_ptr)
			return (1);
		(*fd_vector)->capacity = (*fd_vector)->size - end_line_pos;
	}
	buff_ptr[((*fd_vector)->size - end_line_pos)] = 0;
	ft_memcpy(buff_ptr, (*fd_vector)->buff + end_line_pos,
		(*fd_vector)->size - end_line_pos);
	free((*fd_vector)->buff);
	(*fd_vector)->buff = buff_ptr;
	(*fd_vector)->size = (*fd_vector)->size - end_line_pos;
	return (0);
}

char	*get_next_line(int fd)
{
	t_vector	**fd_vector;
	size_t		end_line_pos;
	char		*buff_out;
	int			read_status;

	end_line_pos = 0;
	fd_vector = get_fd_vector(fd);
	read_status = read_until_new_line(fd, fd_vector, &end_line_pos, &buff_out);
	if (read_status == 1)
		return (buff_out);
	if (read_status == 2)
		return (NULL);
	buff_out = extract_str((*fd_vector)->buff, end_line_pos, 1);
	if (((*fd_vector)->capacity > BUFFER_SIZE * 2)
		&& ((*fd_vector)->capacity > 20))
	{
		if (realocate(fd_vector, end_line_pos) == 1)
			return (NULL);
		return (buff_out);
	}
	ft_memcpy((*fd_vector)->buff, (*fd_vector)->buff + end_line_pos,
		(*fd_vector)->size - end_line_pos);
	((char *)(*fd_vector)->buff)[((*fd_vector)->size - end_line_pos)] = 0;
	(*fd_vector)->size = (*fd_vector)->size - end_line_pos;
	return (buff_out);
}
