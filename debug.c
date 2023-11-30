#include "get_next_line.h"

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"

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
    if (!*saved || **saved == '\0')
        return (0);
    store->line = ft_strdup(*saved);
    free(*saved);
    *saved = NULL;
    return (1);
}

int free_and_fail(t_store *store, int to_return)
{
    if (store->buff != NULL)
    {
        free(store->buff);
        store->buff = NULL;
    }
    if (to_return != -1)
        return (to_return);
    return (0);
}

int store_line(char **saved, t_store *store, int fd)
{
    while (1)
    {
        store->buff = malloc(BUFFER_SIZE + 1);
        if (!store->buff)
            return (0);
        store->bytes = read(fd, store->buff, BUFFER_SIZE);
        if (store->bytes == -1)
        {
            printf(RED "[DEBUG] : read error\n" RESET);
            return (free_and_fail(store, -1));
        }
        store->buff[store->bytes] = '\0';

        store->temp = ft_strjoin(*saved, store->buff);
        free(store->buff);
        if (*saved != NULL)
            free(*saved);
        *saved = store->temp;
        store->new_line_pos = ft_strchr(*saved, '\n');

        if (store->bytes == 0 && !store->new_line_pos)
            return (get_last(store, saved));

        printf(GREEN "[DEBUG] : Updated saved content: %s\n" RESET, *saved);

        if (store->new_line_pos != NULL)
            return (extract_line(store, saved));
    }

    return (1);
}

char *get_next_line(int fd)
{
    static char *saved;
    t_store store;

    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        printf("\n" RED "[DEBUG] : size of buffer not accepted\n");
        return (NULL);
    }
    printf("\n" GREEN "[DEBUG] : accepting size of buffer\n");
    if (!store_line(&saved, &store, fd))
    {
        printf(YELLOW "[DEBUG] : No more lines to read\n" RESET);
        return (NULL);
    }

    printf("\n" GREEN "[DEBUG] : Final saved content: %s\n" RESET "\n", saved);
    return (store.line);
}

