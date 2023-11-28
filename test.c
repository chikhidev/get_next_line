#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
	char	*line;
	int fd = 	open("tests/test_file1.txt", O_RDONLY);

	if (fd < 0)
		return (1);

	close(fd);
	int  i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line %d=> %s\n", i, line);
		free(line);
		i++;
	}

	return 0;
}
