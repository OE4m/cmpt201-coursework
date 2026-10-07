#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

void add_history(char *history[], size_t *count, char *line) {
  if (*count == HISTORY_SIZE) {
    free(history[0]);
    for (size_t i = 1; i < HISTORY_SIZE; i++) {
      history[i - 1] = history[i];
    }
    (*count)--;
  }

  history[*count] = line;
  (*count)++;
}

void print_history(char *history[], size_t count) {
  for (size_t i = 0; i < count; i++) {
    printf("%s\n", history[i]);
  }
}

void free_history(char *history[], size_t count) {
  for (size_t i = 0; i < count; i++) {
    free(history[i]);
  }
}

int main() {
  char *history[HISTORY_SIZE] = {NULL};
  size_t count = 0;
  int status = 0;

  while (1) {
    char *line = NULL;
    size_t n = 0;

    printf("Enter input: ");
    fflush(stdout);
    ssize_t len = getline(&line, &n, stdin);

    if (len < 0) {
      if (!feof(stdin)) {
        perror("ERROR: getline failed");
        status = 1;
      }
      free(line);
      break;
    }

    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    add_history(history, &count, line);
    if (strcmp(line, "print") == 0) {
      print_history(history, count);
    }
  }

  free_history(history, count);
  return status;
}
