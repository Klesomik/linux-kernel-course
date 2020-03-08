#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    printf("=====================================\n");

    int fd = open("/dev/phonebook", O_RDONLY);

    if (fd < 0)
    {
        printf("[test]: Can not open /dev/phonebook\n");
    }
    else
    {
        printf("[test]: /dev/phonebook was opened\n");
    }

    /*if (read(fd, buffer, size) < 0)
    {
        printf("[test]: Can not read from device\n");
    }*/

    const char buf[] = "abacaba";

    printf("[test]: wrote %d bytes\n", write(fd, buf, sizeof(buf)));

    close(fd);

    printf("[test]: /dev/phonebook was closed\n");

    printf("=====================================\n");

    return 0;
}