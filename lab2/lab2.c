#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    while (1) {
        char *line = NULL;
        size_t n = 0;

        printf("Enter programs to run.\n> ");
        ssize_t len = getline(&line, &n, stdin);

        if (len < 1) {
            free(line);
            break;
        }

        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0) {
            free(line);
            continue;
        }

        char *args[64];
        int i = 0;
        char *saveptr = NULL;
        char *token = strtok_r(line, " \t", &saveptr);
        while (token != NULL && i < 63) {
            args[i++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            free(line);
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            free(line);
            exit(1);
        } else if (pid == 0) {
            execv(args[0], args);
            printf("Exec failure\n");
            free(line);
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }

        free(line);
    }
    return 0;
}