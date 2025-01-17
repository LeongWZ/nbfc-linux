#ifndef NBFC_SLURP_FILE_H
#define NBFC_SLURP_FILE_H

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/// Read `file` into `buf`
static inline ssize_t slurp_file(char* buf, size_t size, const char* file) {
  ssize_t   nread = -1;
  const int fd = open(file, O_RDONLY);
  if (fd >= 0) {
    if ((nread = read(fd, buf, size)) >= 0)
      buf[nread] = '\0';
    else if (nread == (ssize_t) size)
      (errno = ENOBUFS), nread = -1;
    close(fd);
  }
  return nread;
}

#endif
