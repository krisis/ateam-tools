// This intent of the program to write a file with o_sync flag set
// The input are 2 files. one file is the input which will be copied
// to the other file, which is opened with o_sync flag

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

char buffer[BUF_SIZE];   
char basefile[BUF_SIZE] = "/home/sas/smallfile";

// Testing O_SYNC Writes on the open + O_CREAT flag 
void barrier_owrite_test1( char* file ) {
    int fd1 = 0;
    int fd2 = 0;
    int status = 0;

    // Open the small file
    fd1 = open( basefile, O_RDONLY );
    if( fd1 < 0 ) {
        printf( "Error while opening file %s - %s\n", basefile, strerror(errno) );
        return;
    }
    
    // Open the file with O_SYNC Flag
    // This creates the file, if not exists
    fd2 = open( file, O_CREAT|O_WRONLY|O_SYNC );
    if( fd2 < 0 ) {
        printf( "Error while creating file %s - %s\n", file, strerror(errno) );
        close( fd1 );
        return;
    }
    
    // Read from the file and write to other file
    while( status = read(fd1, buffer, sizeof(buffer)) ) {
        if( status < 0 ) {
            printf( "Error reading from file - %s - %s\n", basefile, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }

        status = write( fd2, buffer, sizeof(buffer) );
        if( status < 0 ) {
            printf( "Error writing to file - %s - %s\n", file, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }
    
    }
    
    fprintf( stderr, "O_SYNC writes on newly created file, %s succeeded\n",file );

    //close the files
    close( fd1 );
    close( fd2 );
}

// Testing O_SYNC Writes on the file opened with O_SYNC (already existing file)
void barrier_owrite_test2( char* file ) {
    int fd1 = 0;
    int fd2 = 0;
    int status = 0;

    // Open the small file
    fd1 = open( basefile, O_RDONLY );
    if( fd1 < 0 ) {
        printf( "Error while opening file %s - %s\n", basefile, strerror(errno) );
        return;
    }
    
    // Open the file with O_SYNC Flag
    // This creates the file, if not exists
    fd2 = open( file, O_WRONLY|O_SYNC );
    if( fd2 < 0 ) {
        printf( "Error while creating file %s - %s\n", file, strerror(errno) );
        close( fd1 );
        return;
    }
    
    // Read from the file and write to other file
    while( status = read(fd1, buffer, sizeof(buffer)) ) {
        if( status < 0 ) {
            printf( "Error reading from file - %s - %s\n", basefile, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }

        status = write( fd2, buffer, sizeof(buffer) );
        if( status < 0 ) {
            printf( "Error writing to file - %s - %s\n", file, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }
    
    }
    
    fprintf( stderr, "O_SYNC write on already existing file, %s completed\n",file );

    //close the files
    close( fd1 );
    close( fd2 );
}

// Testing Writes on the file opened with O_TRUNC (already existing file)
void barrier_owrite_test3( char* file ) {
    int fd1 = 0;
    int fd2 = 0;
    int status = 0;

    // Open the small file
    fd1 = open( basefile, O_RDONLY );
    if( fd1 < 0 ) {
        printf( "Error while opening file %s - %s\n", basefile, strerror(errno) );
        return;
    }
    
    // Open the file with O_TRUNC Flag
    // This creates the file, if not exists
    fd2 = open( file, O_WRONLY|O_TRUNC );
    if( fd2 < 0 ) {
        printf( "Error while creating file %s - %s\n", file, strerror(errno) );
        close( fd1 );
        return;
    }
    
    fprintf( stderr, "File %s opened with O_TRUNC mode\n", file );

    // Read from the file and write to other file
    while( status = read(fd1, buffer, sizeof(buffer)) ) {
        if( status < 0 ) {
            printf( "Error reading from file - %s - %s\n", basefile, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }

        status = write( fd2, buffer, sizeof(buffer) );
        if( status < 0 ) {
            printf( "Error writing to file - %s - %s\n", file, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }
    
    }
    
    fprintf( stderr, "write on the file, %s completed\n",file );

    //close the files
    close( fd1 );
    close( fd2 );
}

// Testing O_SYNC Writes on the open + O_TRUNC/O_SYNC flag 
void barrier_owrite_test4( char* file ) {
    int fd1 = 0;
    int fd2 = 0;
    int status = 0;

    // Open the small file
    fd1 = open( basefile, O_RDONLY );
    if( fd1 < 0 ) {
        printf( "Error while opening file %s - %s\n", basefile, strerror(errno) );
        return;
    }
    
    // Open the file with O_SYNC Flag
    // This creates the file, if not exists
    fd2 = open( file, O_CREAT|O_WRONLY|O_SYNC|O_TRUNC );
    if( fd2 < 0 ) {
        printf( "Error while creating file %s - %s\n", file, strerror(errno) );
        close( fd1 );
        return;
    }
    
    fprintf( stderr, "File %s created with O_TRUNC + O_SYNC mode\n", file );

    // Read from the file and write to other file
    while( status = read(fd1, buffer, sizeof(buffer)) ) {
        if( status < 0 ) {
            printf( "Error reading from file - %s - %s\n", basefile, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }

        status = write( fd2, buffer, sizeof(buffer) );
        if( status < 0 ) {
            printf( "Error writing to file - %s - %s\n", file, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }
    
    }
    
    fprintf( stderr, "O_SYNC writes on newly created file, %s succeeded\n",file );

    //close the files
    close( fd1 );
    close( fd2 );
}

// Testing on the files newly created with create (already existing file)
void barrier_creat_test( char* file ) {
    int fd1 = 0;
    int fd2 = 0;
    int status = 0;

    // Open the small file
    fd1 = open( basefile, O_RDONLY );
    if( fd1 < 0 ) {
        printf( "Error while opening file %s - %s\n", basefile, strerror(errno) );
        return;
    }
    
    // Open the file with O_SYNC Flag
    // This creates the file, if not exists
    fd2 = creat( file, 0644 );
    if( fd2 < 0 ) {
        printf( "Error while creating file %s - %s\n", file, strerror(errno) );
        close( fd1 );
        return;
    }

    fprintf( stderr, "New file %s created using creat syscall\n", file );

    // Read from the file and write to other file
    while( status = read(fd1, buffer, sizeof(buffer)) ) {
        if( status < 0 ) {
            printf( "Error reading from file - %s - %s\n", basefile, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }

        status = write( fd2, buffer, sizeof(buffer) );
        if( status < 0 ) {
            printf( "Error writing to file - %s - %s\n", file, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }
    
    }
    
    fprintf( stderr, "O_SYNC write on already existing file, %s completed\n",file );

    //close the files
    close( fd1 );
    close( fd2 );
}

    
// Test rename
void barrier_rename_test( char* file ) {
    char newfile[256];
    int ret = -1;
    
    strcpy( newfile, file );
    strcat( newfile, "new" );
    ret = rename( file, newfile );
    
    if( ret == 0 ) {
        fprintf( stderr, "Renamed file %s to %s\n", file, newfile );
    } else {
        fprintf( stderr, "Error while renaming:%s\n", strerror(errno) );
    }
}

// Test unlink
void barrier_unlink_test( char* file ) {
    int ret = -1;

    ret = unlink( file );
    if( ret == 0 ) {
        fprintf( stderr, "Removed file - %s\n", file );
    } else {
        fprintf( stderr, "Error while unlinking - %s\n", strerror(errno) );
    }
}   

// Test rmdir
void barrier_rmdir_test( char* file ) {
    int ret = -1;

    ret = rmdir( file );
    if( ret == 0 ) {
        fprintf( stderr, "Removed dir -  %s\n", file );
    } else {
        fprintf( stderr, "Error while rmdir - %s\n", strerror(errno) );
    }
}   

// Test fsync 
void barrier_fsync_test( char* file ) {
    int fd1 = 0;
    int fd2 = 0;
    int status = 0;
    int ret = -1;

    // Open the small file
    fd1 = open( basefile, O_RDONLY );
    if( fd1 < 0 ) {
        printf( "Error while opening file %s - %s\n", basefile, strerror(errno) );
        return;
    }
    
    fd2 = open( file, O_WRONLY );
    if( fd2 < 0 ) {
        printf( "Error while creating file %s - %s\n", file, strerror(errno) );
        close( fd1 );
        return;
    }
    
    // Read from the file and write to other file
    while( status = read(fd1, buffer, sizeof(buffer)) ) {
        if( status < 0 ) {
            printf( "Error reading from file - %s - %s\n", basefile, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }

        status = write( fd2, buffer, sizeof(buffer) );
        if( status < 0 ) {
            printf( "Error writing to file - %s - %s\n", file, strerror(errno) );
            close( fd1 );
            close( fd2 );
            return;
        }

    }
 
    ret = fsync( fd2 );
    if( ret == 0 ) {
        fprintf( stderr, "Fynced the file -  %s\n", file );
    } else {
        fprintf( stderr, "Error while fsync operation - %s\n", strerror(errno) );
    }
}

// Test truncate 
void barrier_truncate_test( char* file ) {
    int ret = -1;

    ret = truncate( file, 16 );
    if( ret == 0 ) {
        fprintf( stderr, "Truncated file -  %s to 16bytes\n", file );
    } else {
        fprintf( stderr, "Error while truncate operation - %s\n", strerror(errno) );
    }
}   

// Test ftruncate 
void barrier_ftruncate_test( char* file ) {
    int ret = -1;
    int fd;
    
    fd = open( file, O_WRONLY );
    if( fd < 0 ) {
        fprintf( stderr, "Error:%s\n", strerror(errno) );
    }

    ret = ftruncate( fd, 16 );
    if( ret == 0 ) {
        fprintf( stderr, "Truncated file -  %s to 16bytes\n", file );
    } else {
        fprintf( stderr, "Error while truncate operation - %s\n", strerror(errno) );
    }
    close(fd);
}   

// Test setxattr
void barrier_setxattr_test( char* file ) {
    int ret = -1;
    
    ret = setxattr( file, "user.filename", file, strlen(file)+1, 0 );
    if( !ret ) {
        fprintf( stderr, "xattr set on the file-  %s\n", file );
    } else {
        fprintf( stderr, "Error while setxattr operation - %s\n", strerror(errno) );
    }
}   

// Test setxattr
void barrier_fsetxattr_test( char* file ) {
    int ret = -1;
    int fd;

    fd = open( file, O_WRONLY );
    if( fd < 0 ) {
        fprintf( stderr, "Error opening file - %s", strerror(errno) );
    }
    ret = fsetxattr( fd, "user.filename", file, strlen(file)+1, 0 );
    if( ret == 0 ) {
        fprintf( stderr, "xattr set on the file-  %s\n", file );
    } else {
        fprintf( stderr, "Error while setxattr operation - %s\n", strerror(errno) );
    }
    close(fd);
}   

// Test removexattr 
void barrier_removexattr_test( char* file ) {
    int ret = -1;

    // Set a xattr on the filepath
    barrier_setxattr_test( file );

    ret = removexattr( file, "user.filename" );
    if( ret == 0 ) {
        fprintf( stderr, "Removed xattr on file -  %s\n", file );
    } else {
        fprintf( stderr, "Error while removexattr operation - %s\n", strerror(errno) );
    }
}   

// Test fremovexattr
void barrier_fremovexattr_test( char* file ) {
    int ret = -1;
    int fd;
    
    // Set a xattr on the file
    barrier_fsetxattr_test( file );

    fd = open( file, O_WRONLY );
    if( fd < 0 ) {
        fprintf( stderr, "Error:%s\n", strerror(errno) );
    }

    ret = fremovexattr( fd, "user.filename" );
    if( ret == 0 ) {
        fprintf( stderr, "Remove xattr on file -  %s\n", file );
    } else {
        fprintf( stderr, "Error while fremovexattr operation - %s\n", strerror(errno) );
    }
    close(fd);
}   

int main( int argc, char *argv[]) {
    if(argc != 3) {
        fprintf (stderr,"Usage: barrier-test <op-class> <file/dir-name>\n");
        return 1;
    }

    if( !strcmp("owrite",argv[1]) ) {
        //Testing O_SYNC Writes on newly created files with open syscall
        barrier_owrite_test1( argv[2] );
    } else if( !strcmp("owrite-test2",argv[1]) ) {
        //Testing O_SYNC writes on already existing files
        barrier_owrite_test2( argv[2] );
    } else if( !strcmp("owrite-test3",argv[1]) ) {
        //Testing writes on already existing files using open with O_TRUNC
        barrier_owrite_test3( argv[2] );
    } else if( !strcmp("owrite-test4",argv[1]) ) {
        //Testing writes on  O_TRUNC + O_SYNC
        barrier_owrite_test4( argv[2] );
    } else if( !strcmp("creat",argv[1]) ) {
        //Testing writes on newly created files with creat syscall
        barrier_creat_test( argv[2] );
    } else if( !strcmp("rename",argv[1]) ) {
        //Testing rename operation
        barrier_rename_test( argv[2]);
    } else if( !strcmp("unlink",argv[1]) ) {
        //Testing unlink operation
        barrier_unlink_test( argv[2] );
    } else if( !strcmp("rmdir",argv[1]) ) {
        //Testing rmdir operation
        barrier_rmdir_test( argv[2] );
    } else if( !strcmp("truncate",argv[1]) ) {
        //Testing truncate operation
        barrier_truncate_test( argv[2] );
    } else if( !strcmp("ftruncate",argv[1]) ) {
        //Testing ftruncate operation
        barrier_ftruncate_test( argv[2] );
    } else if( !strcmp("fsync",argv[1] ) ) {
        //Testing fsync operation
        barrier_fsync_test( argv[2] );
    } else if( !strcmp("removexattr",argv[1]) ) {
        //Testing removexattr
        barrier_removexattr_test( argv[2] );
    } else if( !strcmp("fremovexattr",argv[1]) ) {
        //Testing fremovexattr
        barrier_fremovexattr_test(argv[2]);
    } else if( !strcmp("setxattr",argv[1]) ) {
        //Setting xattr
        barrier_setxattr_test(argv[2]);
    } else if( !strcmp("fsetxattr",argv[1]) ) {
        //Setting xattr on fd
        barrier_fsetxattr_test(argv[2]);
    } else {
        fprintf(stderr, "Error: No such opclass exists\n");
    }
}
