#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N 3

int matrixA[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int matrixB[N][N] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int result[N][N];

// Variables to track row and column indices during multiplication
int current_row = 0;
int current_col = 0;

// Function to handle the multiplication signal
void handle_signal(int sig) {

    printf("hlw\n");    // Perform matrix multiplication for the current row and column
    for (int i = 0; i < N; ++i) {
        result[current_row][current_col] += matrixA[current_row][i] * matrixB[i][current_col];
    }

    // Move to the next column
    ++current_col;

    // If all columns are processed for the current row, move to the next row
    if (current_col == N) {
        ++current_row;
        current_col = 0;
    }

    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < N; j++){
            printf("%d ",result[i][j]);
        }
        printf("\n");
    }

    // If all rows and columns are processed, print the result and exit
    if (current_row == N && current_col == 0) {
        printf("Matrix multiplication completed.\nResult:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d\t", result[i][j]);
            }
            printf("\n");
        }

        exit(0);
    }
}

int main() {
    pid_t child_pid;

    // Set up the signal handler for SIGUSR1
    for(int i = 0 ; i < N*N ; i++)
    {
         signal(SIGCONT, handle_signal);
    }


    // Create a child process
    if ((child_pid = fork()) == 0) {
        // Child process

        // Wait for the signal to start matrix multiplication
      //  pause();
      sleep(1);
    } else {
        // Parent process

        // Send SIGUSR1 signal to the child process to start multiplication
        kill(child_pid, SIGCONT);

        // Continue parent process execution

        // Wait for the child process to complete
        wait(NULL);
    }

    return 0;
}
