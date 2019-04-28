#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
  FILE* file = fopen("myfs", "w+");
  if (file == NULL) {
    perror(strerror(errno));
    return 1;
  }
  const char wbuf[] = "data";
  size_t s = fwrite(&wbuf, 1, strlen(wbuf), file);
  char rbuf[5];
  memset(rbuf, 0, 5);
  rewind(file);
  fread(&rbuf, 1, s, file);
  fprintf(stdout, "rbuf=%s\n", rbuf);
  fclose(file);
  return 0;
}
