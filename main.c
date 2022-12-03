/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:22:31 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/03 20:22:59 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
	fd = open("./gnlTester/files/empty", O_RDONLY);
	printf("\n----------------------------------------\n");
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			printf("(NULL)\n");
		else
			printf("\nresult:[%s]\n", line);
		fflush(stdout);
		free(line);
		i++;
	}
	printf("\n################################################\n");
	close(fd);
}
