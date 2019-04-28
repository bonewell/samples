#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd = open("bigdata", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd == -1) {
        perror(strerror(errno));
        return 1;
    }
    const char b[] = "begin";
    write(fd, &b, strlen(b));
    lseek(fd, 12345678900000, SEEK_END);
    const char e[] = "end";
    write(fd, &e, strlen(e));
    close(fd);
    return 0;
}
