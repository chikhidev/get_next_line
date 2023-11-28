#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct {
	char buff[BUFFER_SIZE + 1];
	char *temp;
	size_t bytes;
	char *new_line_pos;
} store_t;

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned char		*s;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
    if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	result = malloc(len_s1 + len_s2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

size_t	ft_strlen(const char *str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	for (size_t i = 0; i <= len; i++)
		dup[i] = s[i];
	return (dup);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	debug_print(const char *msg)
{
	printf("[DEBUG] %s\n", msg);
}

char	*get_remaining(char *start)
{
	debug_print("Entering get_remaining");
	char	*res;
	int		i;

	i = ft_strlen(start);
	res = malloc(i + 1);
	if (!res)
	{
		debug_print("get_remaining: Memory allocation failed");
		return (NULL);
	}
	ft_memcpy(res, start, i);
	res[i] = '\0';
	debug_print("Leaving get_remaining");
	return (res);
}

char	*extract_line(char **saved, store_t store)
{
	debug_print("Entering extract_line");
	char	*line;

	line = ft_substr(*saved, 0, store.new_line_pos - *saved);
	store.temp = get_remaining(store.new_line_pos + 1);
	if (store.temp == NULL)
	{
		debug_print("extract_line: get_remaining failed");
		return (NULL);
	}
	free(*saved);
	*saved = store.temp;
	debug_print("Leaving extract_line");
	return (line);
}

char	*get_line(int fd, char **saved, int condition)
{
	debug_print("Entering get_line");
	store_t	store;

	if (condition)
	{
		debug_print("Reading from file");
		store.bytes = read(fd, store.buff, BUFFER_SIZE);
		store.buff[store.bytes] = '\0';
		store.temp = ft_strjoin(*saved, store.buff);
		if (*saved != NULL)
			free(*saved);
		*saved = store.temp;
		debug_print("File content after read: ");
		printf("%s\n", *saved);
	}
    store.new_line_pos = ft_strchr(*saved, '\n');
	if (store.new_line_pos != NULL)
	{
		debug_print("Newline found");
		return (extract_line(saved, store));
	}
	if (condition)
		return get_line(fd, saved, store.bytes > 0);
	if (*saved && **saved != '\0' && store.bytes == 0)
		return get_line(fd, saved, 0);
	if (*saved && !condition)
	{
		debug_print("End of file, copying remaining content");
		store.temp = ft_strdup(*saved);
		free(*saved);
		return (store.temp);
	}
	debug_print("Leaving get_line");
	return (NULL);
}

char	*get_next_line(int fd)
{
	debug_print("Entering get_next_line");
	static char	*saved = NULL;
	char *result = get_line(fd, &saved, 1);
	debug_print("Leaving get_next_line");
	return result;
}

int		main(void)
{
	debug_print("Starting program");
	int fd = open("tests/test_file1.txt", O_RDONLY);
	if (fd == -1)
	{
		debug_print("Failed to open file");
		return (1);
	}

	char *line;
	int i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line %d => %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	debug_print("Program completed");
	return (0);
}
