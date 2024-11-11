Q.1) Write a C program that demonstrates redirection of standard output to a file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    // Open file for writing (creates file if it doesn't exist, truncates if it does)
    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Redirect standard output to the file
    dup2(fd, STDOUT_FILENO);
    close(fd);  // No longer need the file descriptor

    // Now any printf will be written to the file instead of the terminal
    printf("This output is redirected to the file output.txt\n");

    return 0;
}


Output (in the output.txt file):

This output is redirected to the file output.txt

