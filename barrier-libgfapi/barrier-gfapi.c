#include "api/glfs.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

void barrier_owrite_test1( glfs_t *fs1, char *file) {
    int fd1;
    char buffer[256];
    glfs_fd_t *fd2;
    int written = 0;

    fd1 = open("/home/sas/smallfile", O_RDONLY);
    if( fd1 < 0 ) {
        printf( "Error:%s", strerror(errno) );
        return;
    }

    fd2 = glfs_open(fs1, file, O_WRONLY|O_SYNC|O_CREAT);
    if( fd2 == NULL ) {
        printf( "Error: %s\n",strerror(errno) );
        close( fd1 );
    }

    while( read(fd1,buffer,sizeof(buffer)) ) {
        written = glfs_write( fd2, buffer, sizeof(buffer), 0 );
        if( written <= 0 ) {
            printf( "Error: %s\n", strerror(errno) );
            break;
        }
    }
    close(fd1);
    glfs_close(fd2);
    fprintf( stdout, "file %s written with osync flag\n",file );
}

void barrier_owrite_test2( glfs_t *fs1, char *file) {
    int fd1;
    char buffer[256];
    glfs_fd_t *fd2;
    int written = 0;

    fd1 = open("/home/sas/smallfile", O_RDONLY);
    if( fd1 < 0 ) {
        printf( "Error:%s", strerror(errno) );
        return;
    }

    fd2 = glfs_open(fs1, file, O_WRONLY|O_SYNC|O_CREAT);
    if( fd2 == NULL ) {
        printf( "Error: %s\n",strerror(errno) );
        close( fd1 );
    }

    while( read(fd1,buffer,sizeof(buffer)) ) {
        written = glfs_write( fd2, buffer, sizeof(buffer), 0 );
        if( written <= 0 ) {
            printf( "Error: %s\n", strerror(errno) );
            break;
        }
    }
    close(fd1);
    glfs_close(fd2);
}

void barrier_fsync_test1( glfs_t *fs1, char *file) {
    int fd1;
    char buffer[256];
    glfs_fd_t *fd2;
    int written = 0;
    int ret = -1;

    fd1 = open("/home/sas/smallfile", O_RDONLY);
    if( fd1 < 0 ) {
        printf( "Error:%s", strerror(errno) );
        return;
    }

    fd2 = glfs_creat(fs1, file, O_RDWR, 0644);
    if( fd2 == NULL ) {
        printf( "Error: %s\n",strerror(errno) );
        close( fd1 );
        return;
    }

    while( read(fd1,buffer,sizeof(buffer)) ) {
        written = glfs_write( fd2, buffer, sizeof(buffer), 0 );
        if( written <= 0 ) {
            printf( "Error: %s\n", strerror(errno) );
            break;
        }
    }

    printf( "Fsyncing the file\n" );
    ret = glfs_fsync( fd2 );

    if( !ret ) {
        printf( "Error: %s\n",strerror(errno) );
    }
    close(fd1);
    glfs_close(fd2);
}

void barrier_unlink_test( glfs_t *fs1, char *file) {
    int ret = -1;
    struct stat st = {0};
    
    ret = glfs_unlink( fs1, file );
    if (!ret) {
        fprintf (stdout, "\n%s removed", file);
    }

    //Confirm the file is removed
    ret = glfs_stat( fs1, file, &st );
    if( !ret ) {
        fprintf(stdout, "\nFile %s still exists", file);
    }
}

void barrier_rmdir_test(glfs_t *fs1, char *file) {
    int ret = -1;
    struct stat st = {0};
    
    ret = glfs_rmdir( fs1, file );
    if (!ret) {
        fprintf (stdout, "\n%s removed", file);
    }

    //Confirm the dir is removed
    ret = glfs_stat ( fs1, file, &st );
    if( !ret ) {
        fprintf (stdout, "\nDir %s still exists", file);
    }
}

void barrier_rename_test(glfs_t *fs1, char *file) {
    int ret = -1;
    struct stat st = {0};
    char newfile[256] = "new";
   
    strcat( newfile, file ); 

    ret = glfs_rename( fs1, file, newfile );
    if (!ret) {
        fprintf (stdout, "\n%s renamed", file);
    }

    //Confirm the old file is not available
    ret = glfs_stat ( fs1, file, &st );
    if( !ret ) {
        fprintf (stdout, "\nFile %s still exists", file);
    }

    // Confirm the presence of new file
    ret = glfs_stat ( fs1, newfile, &st );
    if( ret ) {
        fprintf (stdout, "\niNewfile %s not available", newfile);
    }
}

int main( int argc, char **argv )
{
    struct stat st = {0};
    int ret = -1;

    if ( argc != 5 ) {
        printf ("Usage: %s <volname> <hostname> <opclass> <file/dir-name>\n", argv[0]);
        return -1;
    }

    glfs_t *fs = glfs_new (argv[1]);
    if (!fs) {
        fprintf (stderr, "glfs_new: returned NULL\n");
        return 1;
    }

    ret = glfs_set_volfile_server (fs, "tcp", argv[2], 24007);
    ret = glfs_set_logging (fs, "/tmp/gfapi-err.log", 7);
    ret = glfs_init (fs);

    // Below are the tests corresponding FOPS barriered
    if(!strcmp("rmfile",argv[3])) {
        barrier_unlink_test(fs,argv[4]);
    } else if(!strcmp("rmdir",argv[3])) {
        barrier_rmdir_test(fs,argv[4]);
    } else if(!strcmp("rename",argv[3])) {
        barrier_rename_test(fs,argv[4]);
    } else if(!strcmp("owrite",argv[3])) {
        barrier_owrite_test1(fs,argv[4]);
    } else if(!strcmp("write2",argv[3])) {
        barrier_owrite_test2(fs,argv[4]);
    } else if(!strcmp("fsync",argv[3])) {
        barrier_fsync_test1(fs,argv[4]);
    }
    
    
    glfs_fini(fs);
}
