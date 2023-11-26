#include "get_next_line.h"

int	find_line(char *saved, char *temp, int line_pos, size_t *last_pos)
{
	int	i;
	int	j;

	i = 0;
	j = *last_pos;
	while (saved[j])
	{
		if (i > line_pos && saved[j] == '\n')
		{
			temp = ft_substr(saved, *last_pos, j);
			printf("found '\\n' in line %d\n", line_pos);
			*last_pos = j;
			return (1);
		}
		if (saved[j] == '\n')
			i++;
		j++;
	}
	return (0);
}

char	*get_line(int fd, char *saved, int line_pos, size_t *last_pos)
{
	char	buff[BUFFER_SIZE + 1];
	int		i;
	char	*temp;

	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		buff[i] = '\0';
		temp = ft_strjoin(saved, buff);
		if (saved)
			free(saved);
		saved = temp;
		// if (find_line(saved, temp, line_pos, last_pos))
		// 	return (temp);
		printf("updated=> '%s'\nadded: %d\n", saved, i);
		i = read(fd, buff, BUFFER_SIZE);
	}
	return (NULL);
}


char	*get_next_line(int fd)
{
	static char		*saved;
	static int		line_pos;
	static size_t	*last_pos;

	line_pos = 0;
	*last_pos = 0;
	saved = NULL;
	
	return (get_line(fd, saved, line_pos++, last_pos));
}
