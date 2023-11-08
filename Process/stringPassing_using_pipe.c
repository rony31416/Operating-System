#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int fd[2];
    // fd[0] - read
    // fd[1] - write

    if (pipe(fd) == -1) {
        printf("Error! Failed to open pipe...\n");
        return 1;
    }

    int id = fork();
    if (id == -1) {
        printf("Fork failed...\n");
        return 2;
    } else if (id == 0) { // Child process
        close(fd[0]); // Close the read end in the child

        char str[200];
        printf("Input String: ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0';

        write(fd[1], str, strlen(str) + 1); // Write the string to the pipe
        close(fd[1]); // Close the write end after writing
    } else { // Parent process
        close(fd[1]); // Close the write end in the parent

        char received_str[200];
        int bytes_read = read(fd[0], received_str, sizeof(received_str));
        if (bytes_read == -1) {
            printf("Error reading from the pipe\n");
            return 3;
        }

        printf("Parent received string from child: %s\n", received_str);
        close(fd[0]); // Close the read end after reading
    }

    return 0;
}
