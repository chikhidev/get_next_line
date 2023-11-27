/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:13:43 by abchikhi          #+#    #+#             */
/*   Updated: 2023/11/27 23:24:19 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "test.utils.c"

char	*ft_strchr(const char *s, int c)
{
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

char	*get_remaining(char *start)
{
	char	*res;
	int		i;

	i = ft_strlen(start);
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, start, i);
	res[i] = '\0';
	return (res);
}

char	*extract_line(char **saved, store_t store)
{
	char	*line;
	static int callback = 0;

	line = ft_substr(*saved, 0, store.new_line_pos - *saved);
	store.temp = get_remaining(store.new_line_pos + 1);
	if (store.temp == NULL)
		return (NULL);
	free(*saved);
	*saved = store.temp;
	if (store.bytes == 0)
		printf("found end of line here in line %d", callback + 1);
	if (store.bytes == -1)
		printf("found error in line %d", callback + 1);
		// return (NULL);
	callback++;
	return (line);
}

char	*get_line(int fd, char **saved)
{
	store_t	store;

	store.bytes = read(fd, store.buff, BUFFER_SIZE);
	while (store.bytes > 0 || *saved)
	{
		store.buff[store.bytes] = '\0';
		store.temp = ft_strjoin(*saved, store.buff);
		if (*saved != NULL)
			free(*saved);
		*saved = store.temp;
		store.new_line_pos = ft_strchr(*saved, '\n');
		if (store.new_line_pos != NULL)
			return (extract_line(saved, store));
		store.bytes = read(fd, store.buff, BUFFER_SIZE);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;

	return (get_line(fd, &saved));
}

