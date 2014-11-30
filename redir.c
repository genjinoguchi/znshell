#include "redir.h"
#include "run.h"
#include "strip_spaces.h"

char * opers_redir = {
	">",
	"1>",
	">>",
	"2>",
	"2>>",
	"&>",
	"&>>",
	"<",
	"|"
};

/*
 * Runs functions. implementations of following redirection operators included.
 * Expects ;, &&, and | to be filtered out.
 * Operators to include:
 * 	>,1> redirect stdout to a file. Truncates the file.
 * 	>>,1>> redirect stdout to a file. Appends to the file.
 * 	&> redirect everything to a file. Truncates the file.
 * 	&>> redirect everything to a file. Appends to the file.
 * 	< get stdin from the preceding file.
 * 	| gets the stdout from the first command and pipes it into stdin of the second file.
 *	
 * 	
 */
int process_redir( char * cmd)
{
	int status;

	status = run( cmd );

	return status;
}
