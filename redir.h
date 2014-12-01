#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <errno.h>

//These are going to be used with piping.
#define READ_END 0
#define WRITE_END 1

int process_redir( char * );
