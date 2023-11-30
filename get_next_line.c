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

int	extract_line(t_store *store, char **saved)
{
	store->line = ft_substr(*saved, 0, store->new_line_pos - *saved + 1);
	store->temp = ft_substr(store->new_line_pos, 1, ft_strlen(store->new_line_pos));
	free(*saved);
	*saved = store->temp;
	return (1);
}

int    store_line(char **saved, t_store *store, int fd)
{
    while (1)
    {
        store->bytes = read(fd, store->buff, BUFFER_SIZE);
        if (store->bytes == -1)
            return (0);
        if (store->bytes == 0)
        {
            if (!*saved)
                return (0);
            store->line = ft_strdup(*saved);
            free(*saved);
            *saved = NULL;
            return (1);
        }
        store->buff[store->bytes] = '\0';
        store->temp = ft_strjoin(*saved, store->buff);
        if (*saved != NULL)
            free(*saved);
        *saved = store->temp;
        store->new_line_pos = ft_strchr(*saved, '\n');
        if (store->new_line_pos != NULL)
			return (extract_line(store, saved));
    }
    return (1);
}

char    *get_next_line(int fd)
{
    static char    *saved;
    t_store store;

	if (fd < 0 || fd > _SC_OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= SSIZE_MAX)
        return (NULL);
    if (!store_line(&saved, &store, fd))
        return (NULL);
    printf("\nsaved: %s\n\n", saved);
    return (store.line);
}
