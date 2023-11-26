#include "get_next_line.h"

int	find_line(char *saved, char *temp, int line_pos)
{
	int	i;
	int	j;

	if (line_pos == 0)
	{
		temp = ft_strchr(saved,'\n');
		return (1);
	}
	i = 0;
	j = 0;
	while (i < line_pos && saved[j])
	{
		if (saved[j] == '\n')
			i++;
		if (i > line_pos && saved[j] == '\n')
		{
			temp = &(saved[j]);
			printf("found '\\n' in line %d\n", line_pos);
			return (1);
		}
		j++;
	}
	return (0);
}

char	*get_line(int fd, char *saved, int line_pos)
{
	char	buff[BUFFER_SIZE + 1];
	int		i;
	char	*temp;
	char	*line;

	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		buff[i] = '\0';
		temp = ft_strjoin(saved, buff);
		if (saved)
			free(saved);
		saved = temp;
		if (find_line(saved, temp, line_pos))
			return (temp);
		printf("updated=> '%s'\nadded: %d\n", saved, i);
		i = read(fd, buff, BUFFER_SIZE);
	}
	return (NULL);
}


char	*get_next_line(int fd)
{
	static char	*saved;
	static int	line_pos;

	line_pos = 0;
	return (get_line(fd, saved, line_pos));
	line_pos++;
}
