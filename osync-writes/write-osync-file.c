// This intent of the program to write a file with o_sync flag set
// The input are 2 files. one file is the input which will be copied
// to the other file, which is opened with o_sync flag

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

char buffer[BUF_SIZE];   

int main( int argc, char *argv[]) {
    int fd1 = 0;
    int fd2 = 0;
    int status = 0;

    // The input should contain the input file that would
    // written to new file and also the output file
    if( argc != 3 ) {
        printf( "Usage: write-as-osync <input-file> <output-file>\n" );
        return -1;
    }
    
    // Open the big file of 1GB
    fd1 = open( argv[1], O_RDONLY );
    if( fd1 < 0 ) {
        printf( "Error while opening file %s - %s\n", argv[1],strerror(errno) );
        return -1;
    }
    
    // Open the file with O_SYNC Flag
    // This creates the file, if not exists
    fd2 = open( argv[2], O_CREAT|O_WRONLY|O_SYNC );
    if( fd2 < 0 ) {
        printf( "Error while creating file %s - %s\n", argv[2],strerror(errno) );
        close( fd1 );
        return -1;
    }
    
    // Read from the file and write to other file
    while( status = read(fd1, buffer, sizeof(buffer)) ) {
        if( status < 0 ) {
            printf( "Error reading from file - %s - %s\n", argv[1], strerror(errno) );
            close( fd1 );
            close( fd2 );
            return -1;
        }

        status = write( fd2, buffer, sizeof(buffer) );
        if( status < 0 ) {
            printf( "Error writing to file - %s - %s\n", argv[2], strerror(errno) );
            close( fd1 );
            close( fd2 );
            return -1;
        }
    
    }

    //close the files
    close( fd1 );
    close( fd2 );
}
