#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    int p1[2]; // 0-->read 1-->write
    int p2[2]; // Missing declaration for the second pipe
    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("Pipe creation failed");
        return -1;
    }

    int pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 2;
    }

    if (pid == 0) { // Child process
        close(p1[0]);
        close(p2[1]);

        int x;
        int rd1 = read(p2[0], &x, sizeof(x));

        if (rd1 == -1) {
            perror("Child: Read from p2 failed");
            return 3;
        }

        printf("Child: Received p2 %d\n", x);

        x *= 4;

        int wrt1 = write(p1[1], &x, sizeof(x));

        if (wrt1 == -1) {
            perror("Child: Write to p1 failed");
            return 4;
        }

        printf("Child: Wrote p1 %d\n", x);//4
    } else { // Parent process
        close(p1[1]);
        close(p2[0]);

        srand(time(NULL));
        int y = rand() % 10;

        int wrt2 = write(p2[1], &y, sizeof(y));

        if (wrt2 == -1) {
            perror("Parent: Write to p2 failed");
            return 5;
        }

        printf("Parent: Wrote p2 %d\n", y);

        int rd2 = read(p1[0], &y, sizeof(y));

        if (rd2 == -1) {
            perror("Parent: Read from p1 failed");
            return 6;
        }

        printf("Parent: Received p1 %d\n", y);
    }

    return 0;
}
