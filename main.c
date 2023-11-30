#include "get_next_line.h"

int main()
{
    int fd = open("tests/1char.txt", O_RDWR);
    char *line;
    int i = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("line => %s\nlen: %zu\n", line, ft_strlen(line));
        free(line);
    }
    // system("leaks a.out");
}