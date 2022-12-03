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
	do
	{
		line = get_next_line(fd);
		if (line == NULL)
			printf("(NULL)\n");
		else
			printf("\nresult:[%s]\n", line);
		fflush(stdout);
		free(line);
		i++;
	} while (line != NULL);
	printf("\n################################################\n");
	close(fd);
}
