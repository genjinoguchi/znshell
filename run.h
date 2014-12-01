#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "redir.h"

int run( char *, char *, int, REDIR_FUNC);
int run_exec( char *, char *, int, REDIR_FUNC );
int run_exit( char *, char *, int, REDIR_FUNC );
int run_cd( char *, char *, int, REDIR_FUNC );
