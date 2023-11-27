/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:13:43 by abchikhi          #+#    #+#             */
/*   Updated: 2023/11/27 16:19:16 by abchikhi         ###   ########.fr       */
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

char *get_remaining(char *start)
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

typedef struct store_s
{
	int		bytes;
	char	buff[BUFFER_SIZE + 1];
	char	*temp;
	char	*new_line_pos;
} store_t;

char	*get_next_line(int fd)
{
	static char *saved;
	char		*line;
	store_t store;

	saved = NULL;
	store.bytes = read(fd, store.buff, BUFFER_SIZE);
	while (store.bytes > 0)
	{
		store.buff[store.bytes] = '\0';
		store.temp = ft_strjoin(saved, store.buff);
		if (saved)
			free(saved);
		saved = store.temp;
		store.new_line_pos = ft_strchr(saved, '\n');
		if (store.new_line_pos != NULL)
		{
			line = ft_substr(saved, 0, store.new_line_pos - saved);
			store.temp = get_remaining(store.new_line_pos);
			if (store.temp == NULL)
				return (NULL);
			free(saved);
			saved = store.temp;
			return (line);
		}
		store.bytes = read(fd, store.buff, BUFFER_SIZE);
	}
	return (NULL);
}
