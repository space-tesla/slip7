Q.2) Implement the following unix/linux command (use fork, pipe and exec system call)
ls -l | wc -l

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        // Child process 1 (ls -l)
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);  // Close the write end after duplicating

        execlp("ls", "ls", "-l", NULL);  // Execute ls -l
        perror("execlp ls");
        return 1;
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            return 1;
        }

        if (pid2 == 0) {
            // Child process 2 (wc -l)
            close(pipefd[1]);  // Close unused write end
            dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from pipe
            close(pipefd[0]);  // Close the read end after duplicating

            execlp("wc", "wc", "-l", NULL);  // Execute wc -l
            perror("execlp wc");
            return 1;
        } else {
            close(pipefd[0]);  // Close pipe ends in parent process
            close(pipefd[1]);

            // Wait for both children to finish
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}

Output (from wc -l in the terminal, showing the number of lines in the directory):

<Number of lines in the directory>
