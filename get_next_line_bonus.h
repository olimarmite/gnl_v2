/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:06:48 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/06 23:52:44 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vector
{
	size_t	capacity;
	size_t	size;
	void	*buff;
}			t_vector;

void		vector_resize_if_needed(t_vector *vector, size_t buff_size);
void		vector_resize(t_vector *vector, size_t new_size, size_t elem_size);
void		vector_insert_buff(t_vector *vector, char *buff, size_t buff_size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		free_vector(t_vector **vector);
char		*extract_str(char *buff, size_t size, int add_terminator);

char		*get_next_line(int fd);

#endif
