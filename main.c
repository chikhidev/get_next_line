#include "get_next_line.h"

int main()
{
    int fd = open("tests/test_file1.txt", O_RDWR);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("line => %s\n", line);
        free(line);
    }
}