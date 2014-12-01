#include "redir.h"
#include "run.h"
#include "strip_spaces.h"

char * opers_redir[] = {
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
	char * cmd1;
	int min_oper; // The position of the first operator in opers_redir[]

	stringsepar( &cmd, &cmd1, opers_redir, &min_oper);

	int status;
	switch( min_oper ){
		case 0:
		case 1:
			//>,1>
			/*
			filename = stringsepar(&cmd, opers_redir, &min_oper);

			do {
				filename = strsep(&filename, " ");
			} while (!filename);

			fd1 = open(filename, O_TRUNC | O_CREAT, 0644);
			status = run_exec(cmd1,fd1,STDOUT_FILENO); 
			*/
			break;
			
		case 2:
		case 3:
			//>>,1>>
			break;
		case 4:
			//2>

			break;
		case 5:
			//2>>

			break;
		case 6:
			//&>

			break;
		case 7:
			//&>>

			break;
		case 8:
			//<

			break;
		case 9:
			//|
			/*
			status = run_exec(cmd1, STDIN_FILENO, STDOUT_FILENO); 
			*/
			break;
		default:
			status = run(cmd1);
	}

	return status;
}
