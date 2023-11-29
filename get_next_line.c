/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:13:43 by abchikhi          #+#    #+#             */
/*   Updated: 2023/11/28 14:29:35 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*get_remaining(char *start)
{
	char	*res;
	int		i;

	i = 0;
	while (start[i])
		i++;
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, start, i);
	res[i] = '\0';
	return (res);
}

char	*extract_line(char **saved, t_store store)
{
	char	*line;

	line = ft_substr(*saved, 0, store.new_line_pos - *saved + 1);
	store.temp = get_remaining(store.new_line_pos + 1);
	if (store.temp == NULL)
		return (NULL);
	free(*saved);
	*saved = store.temp;
	return (line);
}

int	process(t_store *store, int fd, char **saved)
{
	store->bytes = read(fd, store->buff, BUFFER_SIZE);
	if (store->bytes == -1)
		return (0);
	if (store->bytes == 0 && (!*saved || !**saved))
	{
		free(*saved);
		return (0);
	}
	// if (store->bytes == 1 && !*saved && BUFFER_SIZE == 1)
	// {
	// 	store->temp = ft_strdup(store->buff);
	// 	return (-1);
	// }
	store->buff[store->bytes] = '\0';
	store->temp = ft_strjoin(*saved, store->buff);
	free(*saved);
	*saved = store->temp;
	return (1);
}

char	*post_line(int fd, char **saved, int condition, int *stop)
{
	t_store	store;

	store.bytes = 0;
	if (condition && !*stop)
	{
		store.signal = process(&store, fd, saved);
		if (store.signal == 0)
			return (NULL);
		else if (store.signal == -1)
			return (store.temp);
	}
	store.new_line_pos = ft_strchr(*saved, '\n');
	if (store.new_line_pos && store.signal != -1)
		return (extract_line(saved, store));
	if (condition && !*stop)
		return (post_line(fd, saved, (store.bytes > 0), stop));
	if (*saved && **saved != '\0' && store.bytes == 0 && !*stop)
		return (post_line(fd, saved, 0, stop));
	if (*saved && !condition && !*stop)
	{
		*stop = 1;
		return (*saved);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	static int	stop;

	if (fd < 0 || fd >= _SC_OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	return (post_line(fd, &saved, 1, &stop));
}
