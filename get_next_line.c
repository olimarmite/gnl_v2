/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:09:41 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/03 15:31:34 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//-----------

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
	while (i < vector->size)
	{
		new_buff[i] = ((char *)vector->buff)[i];
		i++;
	}
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

void	vector_insert_buff(t_vector *vector, char *buff, size_t buff_size)
{
	size_t	i;

	i = 0;
	vector_resize_if_needed(vector, buff_size);
	while (i < buff_size)
	{
		((char *)vector->buff)[vector->size + i] = buff[i];
		i++;
	}
	vector->size += buff_size;
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

//------------

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

size_t	check_line(char *full_buff, size_t start_pos, size_t buff_size)
{
	size_t	i;

	//char	*result;
	i = 0;
	//printf("\nstart_pos: %ld: i:%ld, full_buff:%c\n", start_pos, i,
	//		full_buff[start_pos + i]);
	//fflush(stdout);
	while (i < buff_size && full_buff[start_pos + i] != 0)
	{
		//printf("\n/%c/\n", full_buff[start_pos + i]);
		if (full_buff[start_pos + i] == '\n')
		{
			printf("\nLINE FOUND\n");
			//		result = extract_str(full_buff + start_pos, i);
			//			printf("\n[%s]\n", result);
			//return ();
			return (start_pos + i + 1);
		}
		i++;
		//printf("\nsize:%ld-/%s/\n", buff_size, full_buff);
		//printf("\nstart_pos: %ld: i:%ld, full_buff:%c\n", start_pos, i,
		//		full_buff[start_pos + i]);
		//fflush(stdout);
	}
	return (0);
}
char	*get_next_line(int fd)
{
	static t_vector	*fd_vector;
	char			*buff_ptr;
	size_t			end_line_pos;
	char			*buff_out;
	int				readed_count;

	end_line_pos = 0;
	readed_count = 0;
	if (fd_vector == NULL)
	{
		printf("CREATE NEW FD_VECTOR\n");
		printf("\n%d\n", BUFFER_SIZE);
		fd_vector = malloc(sizeof(t_vector));
		if (!fd_vector)
			return (NULL);
		fd_vector->capacity = 0;
		fd_vector->size = 0;
		fd_vector->buff = NULL;
	}
	else if ((fd_vector->size > 0 && fd_vector->size < BUFFER_SIZE))
	{
		printf("---capacity : %ld, size : %ld\n", fd_vector->capacity,
				fd_vector->size);
		end_line_pos = check_line(fd_vector->buff, 0, BUFFER_SIZE);
	}
	while (end_line_pos == 0)
	{
		vector_resize_if_needed(fd_vector, BUFFER_SIZE + 5);
		if (fd_vector->buff == NULL)
		{
			printf("###(NULL)###\n");
			return (NULL);
		}
		//	printf("capacity : %ld, size : %ld\n", fd_vector->capacity,
		//		fd_vector->size);
		//		printf("buff :%s\n", (char *)fd_vector->buff);
		buff_ptr = (char *)fd_vector->buff + fd_vector->size;
		readed_count = read(fd, buff_ptr, BUFFER_SIZE);
		if (readed_count <= 0)
		{
			printf("\nEND OF FILE\n");
			if (fd_vector->size == 0)
			{
				free(fd_vector->buff);
				free(fd_vector);
				fd_vector = NULL;
				return (NULL);
			}
			if (((char *)fd_vector->buff)[0] == 0)
			{
				free(fd_vector->buff);
				free(fd_vector);
				fd_vector = NULL;
				return (NULL);
			}
			buff_out = extract_str(fd_vector->buff, fd_vector->size, 1);
			free(fd_vector->buff);
			free(fd_vector);
			fd_vector = NULL;
			// fd_vector->size = 0;
			// fd_vector->capacity = 0;
			// fd_vector->buff = NULL;
			return (buff_out);
			//return (NULL);
		}
		end_line_pos = check_line(fd_vector->buff, fd_vector->size, readed_count);
		fd_vector->size += readed_count;
	}
	if (end_line_pos > 0)
	{
		buff_out = extract_str(fd_vector->buff, end_line_pos, 1);
		if (1 || ((fd_vector->capacity > BUFFER_SIZE * 2)
				|| (fd_vector->capacity - end_line_pos < (fd_vector->capacity
						/ 2))))
		//TODO verify that Oliv
		{
			// realocate
			buff_ptr = NULL;
			if ((fd_vector->size - end_line_pos) <= BUFFER_SIZE)
			{
				buff_ptr = malloc(BUFFER_SIZE + 1 * sizeof(char));
				if (!buff_ptr)
					return (NULL);
				fd_vector->capacity = BUFFER_SIZE;
			}
			else
			{
				buff_ptr = malloc((fd_vector->size + 1 - end_line_pos)
						* sizeof(char));
				if (!buff_ptr)
					return (NULL);
				fd_vector->capacity = fd_vector->size - end_line_pos;
			}
			printf("\nsize=[%ld],  end_line_pos=[%ld], readed_count=[%d], calc[%ld]\n ", fd_vector->size, end_line_pos, readed_count,
					(fd_vector->size - end_line_pos));
				fflush(stdout);
			buff_ptr[(fd_vector->size - end_line_pos)] = 0;
			printf("\nsizeee[%ld]\n", fd_vector->size - end_line_pos);
			ft_memcpy(buff_ptr, fd_vector->buff + end_line_pos, fd_vector->size - end_line_pos);
			free(fd_vector->buff);
			fd_vector->buff = buff_ptr;
			fd_vector->size = fd_vector->size - end_line_pos;
		}
		else
		{
			//move memory data
			//memcpy()
			ft_memcpy(fd_vector->buff, fd_vector->buff + end_line_pos,
					(fd_vector->size  - end_line_pos));
			((char *)fd_vector->buff)[(fd_vector->size - end_line_pos)] = 0;
			fd_vector->size = fd_vector->size - end_line_pos;
		}
		printf("\nRETURN BUFF\n");
		return (buff_out);
	}
	printf("AAAAAAAA\n");
	return (NULL);
}
/*/
char	*get_next_line_bk(int fd)
{
	static t_vector	*fd_vector;
	char			*buff_ptr;
	size_t			end_line_pos;
	char			*buff_out;

	if (fd_vector == NULL)
	{
		printf("CREATE NEW FD_VECTOR\n");
		fd_vector = malloc(sizeof(t_vector));
		fd_vector->capacity = 0;
		fd_vector->size = 0;
		fd_vector->buff = NULL;
	}
	//else
	end_line_pos = 0;
	if (fd_vector->buff != NULL)
	{
		if (fd_vector->size < BUFFER_SIZE && fd_vector->size > 0)
			end_line_pos = check_line(fd_vector->buff, 0, fd_vector->size - 1);
		else
			end_line_pos = check_line(fd_vector->buff, fd_vector->size
					- BUFFER_SIZE, BUFFER_SIZE);
	}
	if (end_line_pos != 0)
	{
		buff_out = extract_str(fd_vector->buff, end_line_pos, 1);
		if ((fd_vector->capacity < BUFFER_SIZE * 2) || (fd_vector->capacity
				- end_line_pos < (fd_vector->capacity / 2)))
		//TODO verify that Oliv
		{
			//move memory data
			//memcpy()
			ft_memcpy(fd_vector->buff, fd_vector->buff + end_line_pos,
					fd_vector->size - end_line_pos);
			((char *)fd_vector->buff)[fd_vector->size - end_line_pos] = 0;
			fd_vector->size = fd_vector->size - end_line_pos;
		}
		else
		{
			// realocate
			buff_ptr = extract_str(fd_vector->buff + end_line_pos,
									fd_vector->size - end_line_pos,
									0);
			free(fd_vector->buff);
			fd_vector->buff = buff_ptr;
			fd_vector->size = fd_vector->size - end_line_pos;
		}
		return (buff_out);
	}
	if (end_line_pos == 0)
	{
		vector_resize_if_needed(fd_vector, BUFFER_SIZE + 5);
		// buff_ptr = fd_vector->size
		if (fd_vector->buff == NULL)
		{
			printf("###(NULL)###\n");
			return (NULL);
		}
		printf("capacity : %ld, size : %ld\n", fd_vector->capacity,
				fd_vector->size);
		//		printf("buff :%s\n", (char *)fd_vector->buff);
		buff_ptr = (char *)fd_vector->buff + fd_vector->size;
		read(fd, buff_ptr, BUFFER_SIZE);
		if (read == NULL)
		{
			return (NULL);
		}
		fd_vector->size += BUFFER_SIZE;
	}
	return (get_next_line(fd));
}
*/

// int	main(void)
// {
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
// 	fd = open("./gnlTester/files/multiple_nlx5", O_RDONLY);
// 	printf("\n----------------------------------------\n");
// 	i = 0;
// 	while (i < 10)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			printf("(NULL)\n");
// 		else
// 			printf("\nresult:[%s]\n", line);
// 		fflush(stdout);
// 		free(line);
// 		i++;
// 	}
// 	printf("\n################################################\n");
// 	close(fd);
// }
