// Eli Simmonds
// CS450
// H4 P3

/*
 My program opens "test.txt" read-only and reads the first two digits
 it then closes the file and spawns a new process to un-link the file,
 deleting it from the directory. It then tries to read it and errors out
 because the file no longer exists. 
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define PERMS 0666

int main (int argc, char* argv []) {
    pid_t pid;
    int status;
    
    
    char buffer[100];
    static char message[] = "this is a test lets see the size of this message";
    
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return;
    }
    
    lseek(fd, 0, 0);
    read(fd, buffer, sizeof(12));
    printf("%s was read from file\n", buffer);
    close(fd);
    
    if (pid == fork()) {
        if (unlink("test.txt") == -1) {
            printf("Error deleting file");
        }
    }
    
    waitpid(pid, &status, WNOHANG);
    lseek(fd, 0, 0);
    if (read(fd, buffer, sizeof(12)) == -1) {
        printf("Cannot read from file\n");
    }
    
    return 0;
}
