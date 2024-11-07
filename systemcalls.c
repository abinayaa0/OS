//fork and pid
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t process_id;
    pid_t original_pid = getpid();
    printf("Original PID: %d\n", original_pid);
    
    process_id = fork();
    if (process_id < 0) {
        perror("fork");
        return 1;
    } else if (process_id == 0) {
        pid_t new_child_pid = getpid();
        printf("New Child PID: %d\n", new_child_pid);
        printf("Child process executed\n");
    } else {
        printf("I am the parent process\n");
    }
    
    return 0;
}
//open and create a file:
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file_descriptor;
    
    // Open or create file
    file_descriptor = open("lab2(2).txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (file_descriptor == -1) {
        perror("open");
        return 1;
    }
    
    // Close the file descriptor
    if (close(file_descriptor) == -1) {
        perror("close");
        return 1;
    }
    
    return 0;
}
//READ AND WRITE TO FILES
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024

int main() {
    int input_fd, output_fd;
    char data_buffer[BUFFER_SIZE];
    ssize_t read_bytes, written_bytes;
    
    input_fd = open("lab2(2).txt", O_RDONLY);
    if (input_fd == -1) {
        perror("open input.txt");
        return 1;
    }

    // Open or create the output file for writing
    output_fd = open("lab2(1).txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (output_fd == -1) {
        perror("open output.txt");
        close(input_fd);
        return 1;
    }

    // Read from input_fd into data_buffer
    read_bytes = read(input_fd, data_buffer, BUFFER_SIZE);
    if (read_bytes == -1) {
        perror("read");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    // Write from data_buffer to output_fd
    written_bytes = write(output_fd, data_buffer, read_bytes);
    if (written_bytes == -1) {
        perror("write");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    printf("Successfully copied %zd bytes from lab2(2).txt to lab1(1).txt\n", written_bytes);
    
    // Close file descriptors
    close(input_fd);
    close(output_fd);
    return 0;
}
//WRITE FROM USER TO A FILE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int main() {
    int file_desc;
    char *user_input;
    ssize_t written_size;
    
    // Allocate memory for user_input
    user_input = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (user_input == NULL) {
        perror("malloc");
        return 1;
    }

    // Prompt user and read input
    printf("Enter text to write to file: ");
    if (fgets(user_input, BUFFER_SIZE, stdin) == NULL) {
        perror("fgets");
        free(user_input);
        return 1;
    }

    // Open or create the file
    file_desc = open("example.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);
    if (file_desc == -1) {
        perror("open");
        free(user_input);
        return 1;
    }

    // Write to file descriptor file_desc from user_input
    written_size = write(file_desc, user_input, strlen(user_input));
    if (written_size == -1) {
        perror("write");
        close(file_desc);
        free(user_input);
        return 1;
    }

    printf("Wrote %zd bytes to example.txt\n", written_size);
    
    // Close file descriptor and free allocated memory
    close(file_desc);
    free(user_input);
    return 0;
}
