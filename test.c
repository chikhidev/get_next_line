#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int		fd = open("tests/test_file1.txt", O_RDONLY);
	char	*line;

	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}

	int  i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line %d=> %s\n", i, line);
		free(line);
		i++;
	}

	close(fd);

	return 0;
}
