/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:09:37 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/03 20:19:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	vector_resize(t_vector *vector, size_t new_size, size_t elem_size)
{
	size_t	i;
	char	*new_buff;

	i = 0;
	new_buff = calloc(new_size, elem_size);
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

// void	vector_insert_buff(t_vector *vector, char *buff, size_t buff_size)
// {
// 	size_t	i;

// 	i = 0;
// 	vector_resize_if_needed(vector, buff_size);
// 	while (i < buff_size)
// 	{
// 		((char *)vector->buff)[vector->size + i] = buff[i];
// 		i++;
// 	}
// 	vector->size += buff_size;
// }

//VECTOR TESTS

// int	main(void)
// {
// 	t_vector	*vector;

// 	vector = malloc(sizeof(t_vector));
// 	vector->capacity = 0;
// 	vector->size = 0;
// 	// vector_resize_if_needed(vector, BUFFER_SIZE + 5);
// 	// vector->size += BUFFER_SIZE;
// 	// ((char *)vector->buff)[0] = 'q';
// 	vector_insert_buff(vector, "0123456789", BUFFER_SIZE);
// 	if (vector->buff == NULL)
// 		printf("(NULL)\n");
// 	else
// 		printf("[%s]\n", (char *)vector->buff);
// 	printf("capacity : %ld, size : %ld\n", vector->capacity, vector->size);
// 	printf("\n-2-\n");
// 	vector_insert_buff(vector, "abcdefghij", BUFFER_SIZE);
// 	if (vector->buff == NULL)
// 		printf("(NULL)\n");
// 	else
// 		printf("[%s]\n", (char *)vector->buff);
// 	printf("capacity : %ld, size : %ld\n", vector->capacity, vector->size);
// 	printf("\n-3-\n");
// 	vector_insert_buff(vector, "jklmnpqrst", BUFFER_SIZE);
// 	if (vector->buff == NULL)
// 		printf("(NULL)\n");
// 	else
// 		printf("[%s]\n", (char *)vector->buff);
// 	printf("capacity : %ld, size : %ld\n", vector->capacity, vector->size);
// 	printf("\n-4-\n");
// 	vector_insert_buff(vector, "uvwxyzqwertyuiopasdf", 20);
// 	if (vector->buff == NULL)
// 		printf("(NULL)\n");
// 	else
// 		printf("[%s]\n", (char *)vector->buff);
// 	printf("capacity : %ld, size : %ld\n", vector->capacity, vector->size);
// }
