#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define MAX_ROWS 10
#define MAX_COLS 10

volatile sig_atomic_t child_done = 1;

void signal_handler(int signum) {
    if (signum == SIGCHLD) {
        child_done++;
    }
}

void display_matrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows1, cols1, rows2, cols2;

    // Get dimensions of matrix 1
    printf("Enter the number of rows in matrix 1: ");
    scanf("%d", &rows1);

    printf("Enter the number of columns in matrix 1: ");
    scanf("%d", &cols1);

    // Get dimensions of matrix 2
    printf("Enter the number of rows in matrix 2: ");
    scanf("%d", &rows2);

    printf("Enter the number of columns in matrix 2: ");
    scanf("%d", &cols2);

    if (cols1 != rows2) {
        printf("\nMatrix dimensions are not compatible for multiplication.\nThe number of columns in matrix 1 must equal the number of rows in matrix 2.\n");
        exit(EXIT_FAILURE);
    }

    int matrix1[MAX_ROWS][MAX_COLS];
    int matrix2[MAX_ROWS][MAX_COLS];
    int result[MAX_ROWS][MAX_COLS] = {0};

    // Set up signal handler for SIGCHLD
    signal(SIGCHLD, signal_handler);

    // Get elements for matrix 1
    printf("\nEnter values for Matrix 1 (%dx%d):\n", rows1, cols1);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }

    // Get elements for matrix 2
    printf("\nEnter values for Matrix 2 (%dx%d):\n", rows2, cols2);
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    // Record the start time
    clock_t start_time = clock();

    // Fork a child process for each element in the result matrix
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            pid_t pid = fork();

            if (pid == -1) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {  // Child process
                int partial_result = 0;
                for (int k = 0; k < cols1; k++) {
                    partial_result += matrix1[i][k] * matrix2[k][j];
                }
                printf("Child %d: Result at [%d][%d] = %d\n", getpid(), i, j, partial_result);
                exit(partial_result);
            }
        }
    }

    // Parent process waits for all child processes to complete
    while (child_done < rows1 * cols2) {
        pause();  // Wait for a signal
    }

    // Record the end time
    clock_t end_time = clock();

    // Collect the results from completed child processes
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            int status;
            pid_t child_pid = wait(&status);

            if (WIFEXITED(status)) {
                result[i][j] = WEXITSTATUS(status);
                printf("Parent: Received result from Child %d\n", child_pid);
            } else {
                fprintf(stderr, "Child %d did not exit normally\n", child_pid);
            }
        }
    }

    // Display the matrices and the final result
    printf("\nMatrix 1:\n");
    display_matrix(matrix1, rows1, cols1);

    printf("\nMatrix 2:\n");
    display_matrix(matrix2, rows2, cols2);

    printf("\nResult Matrix:\n");
    display_matrix(result, rows1, cols2);

    // Calculate and display the execution time
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f seconds\n", execution_time);

    return 0;
}
