#include "SocketHandler.hpp"

namespace et {
void SocketHandler::readAll(int fd, void* buf, size_t count) {
  size_t pos = 0;
  while (pos < count) {
    ssize_t bytesRead = read(fd, ((char*)buf) + pos, count - pos);
    if (bytesRead < 0) {
      if (errno == EAGAIN ||
          errno == EWOULDBLOCK) {
        // This is fine, just keep retrying at 10hz
        usleep(1000 * 100);
      } else {
        VLOG(1) << "Failed a call to readAll: " << strerror(errno);
        throw std::runtime_error("Failed a call to readAll");
      }
    } else {
      pos += bytesRead;
    }
  }
}

void SocketHandler::writeAll(int fd, const void* buf, size_t count) {
  size_t pos = 0;
  while (pos < count) {
    ssize_t bytesWritten = write(fd, ((const char*)buf) + pos, count - pos);
    if (bytesWritten < 0) {
      if (errno == EAGAIN ||
          errno == EWOULDBLOCK) {
        // This is fine, just keep retrying at 10hz
        usleep(1000 * 100);
      } else {
        VLOG(1) << "Failed a call to writeAll: " << strerror(errno);
        throw std::runtime_error("Failed a call to writeAll");
      }
    } else {
      pos += bytesWritten;
    }
  }
}
}
