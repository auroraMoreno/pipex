#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	//int		fd;
	char	*line;

	//fd = 42;
	line = get_next_line(42);
	while (line)
	{
		printf("%s", line);
		free(line);
	}

    return (0);
}