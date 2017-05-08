// Eli Simmonds
// CS450
// H4 P3

/*
 My program opens "test.txt" and reads from it initially.
 A process is spawned to unlink the file. 
 The file is then read again from the parent process 
 and child process. Since unlink does not delete the file,
 it only deletes the link to said file we can read twice 
 even with a broken link.
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
    char * filename = argv[1];
    
    
    char buffer[100];
    static char message[] = "this is a test lets see the size of this message";
    
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error opening %s. Are you sure it exists?\n", filename);
        return 0;
    }
    
    lseek(fd, 0, 0);
    read(fd, buffer, sizeof(buffer));
    printf("First read: %s was read from %s \n", buffer, filename);
    
    if (pid = fork()) {
        if (unlink(filename) == -1) {
            printf("Error deleting file");
        }
    }
    
    if (pid != 0) {
        wait(NULL);
        
        lseek(fd, 0, 0);
        if (read(fd, buffer, sizeof(12)) == -1) {
            printf("Cannot read from %s. Are you sure it exists?\n", filename);
        }
        else {
            printf("Second read: %s was read from %s \n", buffer, filename);
        }
    }
    
    return 0;
}
