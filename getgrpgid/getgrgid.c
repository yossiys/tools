/*
 *  * Print a list of all users in your group
 *   */
/*
 * adduser user0002 -M -N -g testgrp01
 * gpasswd -a user0002 testgrp01
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <grp.h>
#include <errno.h>

int main( void )
{
	gid_t gid;
	struct group grp;
	char *buf;
	size_t bufsize;
	struct group *result = NULL;
	char** p;
	int ret = -1;

	gid = 1002;
	bufsize = 3;
	buf = malloc(bufsize);

	// retの値は正しくない
	while ( result == NULL ) {
		bufsize += 1;
		buf = realloc( buf, bufsize );
		ret = getgrgid_r( gid, &grp, buf, bufsize, &result );

//		printf("bufsize=%d ret = %d errno=%d\n",bufsize, ret, errno);
//      fprintf( stderr, "getgrgid: %s\n",strerror(errno));
//      return( EXIT_FAILURE );
    }

	printf( "bufsize=%d\n", bufsize);
//	printf( "buf=%p\n", &buf);
//	printf( "result=%p\n", result);
	if ( result != NULL ) {
		printf( "gid(%d) / group name(%s)\n", gid, grp.gr_name );
		for( p = grp.gr_mem; *p != NULL; p++ ) {
			printf( "\t%s\n", *p );
		}
	}

    return( EXIT_SUCCESS );
}
