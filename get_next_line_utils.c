/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:09:37 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/09 14:39:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	vector_resize(t_vector *vector, size_t new_size, size_t elem_size)
{
	size_t	i;
	char	*new_buff;

	i = 0;
	new_buff = malloc(new_size * elem_size);
	if (new_buff == NULL)
	{
		free(vector->buff);
		vector->buff = NULL;
		vector->capacity = 0;
		vector->size = 0;
		return ;
	}
	while (i++ < vector->size)
		new_buff[i - 1] = ((char *)vector->buff)[i - 1];
	if (new_size > 0)
	{
		new_buff[new_size - 1] = 0;
		new_buff[i] = 0;
	}
	vector->capacity = new_size;
	if (vector->buff != NULL)
		free(vector->buff);
	vector->buff = new_buff;
}

void	vector_resize_if_needed(t_vector *vector, size_t buff_size)
{
	size_t	new_capacity;

	if (vector->capacity <= vector->size + buff_size)
	{
		new_capacity = vector->capacity * 1.5;
		if (new_capacity < buff_size)
			new_capacity = buff_size;
		while (new_capacity <= vector->size + buff_size)
			new_capacity = new_capacity * 2;
		vector_resize(vector, new_capacity, sizeof(char));
	}
}

void	free_vector(t_vector **vector)
{
	free((*vector)->buff);
	free(*vector);
	*vector = NULL;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*s;
	char		*d;

	s = src;
	d = dest;
	i = 0;
	if ((dest == NULL && src == NULL))
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*extract_str(char *buff, size_t size, int add_terminator)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (size + add_terminator));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = buff[i];
		i++;
	}
	if (add_terminator)
		dest[i] = 0;
	return (dest);
}
