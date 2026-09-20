#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  while (1) {
    char *line = NULL;
    size_t n = 0;

    printf("Please enter some text: ");
    ssize_t len = getline(&line, &n, stdin);

    if (len < 1) {
      perror("ERROR: getline failed");
      free(line);
      break;
    }

    if (strncmp(line, "exit", 4) == 0) {
      free(line);
      return 0;
    }

    char *saveptr = NULL;
    char *token = strtok_r(line, " ", &saveptr);
    printf("\nTokens:\n");

    while (token) {
      printf(" %s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }

    free(line);
  }
}
