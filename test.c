#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd = open("/dev/phonebook", O_RDONLY);

    if (fd < 0)
    {
        printf("Wow it doesnt work\n");
    }

    /*
    if (read(fd, buffer, size) < 0)
    {
    }

    if (write(fd, buffer, size) < 0)
    {
    }*/

    close(fd);

    return 0;
}