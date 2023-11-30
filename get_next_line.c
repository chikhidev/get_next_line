/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:13:43 by abchikhi          #+#    #+#             */
/*   Updated: 2023/11/30 17:45:12 by abchikhi         ###   ########.fr       */
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

int get_last(t_store *store, char **saved)
{
    int to_return;

    to_return = 1;
    if (!*saved || **saved == '\0')
        to_return = 0;
    else
        store->line = ft_strdup(*saved);
    free(*saved);
    *saved = NULL;
    return (to_return);
}

int free_and_fail(t_store *store, char **saved)
{
    if (store->buff != NULL)
    {
        free(store->buff);
        store->buff = NULL;
    }
    if (*saved != NULL)
    {
        free(*saved);
        *saved = NULL;
    }
    return (0);
}

int    store_line(char **saved, t_store *store, int fd)
{
    while (1)
    {
        store->buff = malloc(BUFFER_SIZE + 1);
        if (!store->buff)
            return (free_and_fail(store, saved));
        store->bytes = read(fd, store->buff, BUFFER_SIZE);
        if (store->bytes == -1)
            return (free_and_fail(store, saved));
        store->buff[store->bytes] = '\0';
        store->temp = ft_strjoin(*saved, store->buff);
        free(store->buff);
        if (*saved != NULL)
        {
            free(*saved);
            *saved = NULL;
        }
        *saved = store->temp;
        store->new_line_pos = ft_strchr(*saved, '\n');
        if (store->bytes == 0 && !store->new_line_pos)
            return (get_last(store, saved));
        if (store->new_line_pos != NULL)
            return (extract_line(store, saved));
    }
    return (1);
}

char    *get_next_line(int fd)
{
    static char    *saved;
    t_store store;

	if (fd < 0 || fd > _SC_OPEN_MAX || BUFFER_SIZE <= 0)
        return (NULL);
    if (!store_line(&saved, &store, fd))
        return (NULL);
    return (store.line);
}
