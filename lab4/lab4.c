#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *message) {
  write(STDERR_FILENO, message, strlen(message));
  write(STDERR_FILENO, "\n", 1);
  exit(1);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main(void) {
  void *start = sbrk(256);
  if (start == (void *)-1) {
    handle_error("sbrk");
  }

  struct header *b1 = start;
  struct header *b2 = (struct header *)((uint8_t *)start + 128);

  b1->size = 128;
  b1->next = NULL;
  b2->size = 128;
  b2->next = b1;

  uint8_t *data1 = (uint8_t *)b1 + sizeof(struct header);
  uint8_t *data2 = (uint8_t *)b2 + sizeof(struct header);
  size_t data_size = 128 - sizeof(struct header);

  memset(data1, 0, data_size);
  memset(data2, 1, data_size);

  print_out("first block:       %p\n", &b1, sizeof(b1));
  print_out("second block:      %p\n", &b2, sizeof(b2));
  print_out("first block size:  %lu\n", &b1->size, sizeof(b1->size));
  print_out("first block next:  %p\n", &b1->next, sizeof(b1->next));
  print_out("second block size: %lu\n", &b2->size, sizeof(b2->size));
  print_out("second block next: %p\n", &b2->next, sizeof(b2->next));

  for (size_t i = 0; i < data_size; i++) {
    uint64_t value = data1[i];
    print_out("%lu\n", &value, sizeof(value));
  }
  for (size_t i = 0; i < data_size; i++) {
    uint64_t value = data2[i];
    print_out("%lu\n", &value, sizeof(value));
  }

  return 0;
}
