#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char source_file[] = "source.txt";
    char destination_file[] = "destination.txt";
    
    int source_fd, dest_fd; 
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];
    
   
    source_fd = open(source_file, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return 1;
    }
    
   
    dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }
    
   
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }
    
  
    close(source_fd);
    close(dest_fd);
    
    printf("File copy successful.\n");
    
    return 0;
}