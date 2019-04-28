#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd = open("myf", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd == -1) {
        perror(strerror(errno));
        return 1;
    }
    const char wbuf[] = "data";
    ssize_t sw = write(fd, &wbuf, strlen(wbuf));
    if (sw == -1) {
        perror(strerror(errno));
        return 1;
    }
    lseek(fd, 0, SEEK_SET);
    char rbuf[5];
    ssize_t sr = read(fd, &rbuf, sizeof(rbuf));
    if (sr == -1) {
        perror(strerror(errno));
        return 1;
    }
    fprintf(stdout, "rbuf=%s\n", rbuf);
    close(fd);
    return 0;
}
