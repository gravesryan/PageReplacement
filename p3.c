// Eli Simmonds
// CS450
// H4 P3

/*
 My program opens "test.txt" and reads from it initially.
 A process is spawned to unlink the file. 
 The file is then read again from the parent process 
 and child process
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/unistd.h>

#define PERMS 0666

int main (int argc, char* argv []) {
    pid_t pid;
    int status;
    
    
    char buffer[100];
    static char message[] = "this is a test lets see the size of this message";
    
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening 'test.txt'. Are you sure it exists?\n");
        return 0;
    }
    
    lseek(fd, 0, 0);
    read(fd, buffer, sizeof(12));
    printf("First read: %s was read from 'test.txt'\n", buffer);
    
    
    if (pid == fork()) {
        if (unlink("test.txt") == -1) {
            printf("Error deleting file");
        }
    }
    
    while(wait(NULL) > 0);
    
    lseek(fd, 0, 0);
    if (read(fd, buffer, sizeof(12)) == -1) {
        printf("Cannot read from 'test.txt'. Are you sure it exists?\n");
    }
    else {
        printf("Second read: %s was read from 'test.txt'\n", buffer);
    }
    
    return 0;
}
