#include "redir.h"
#include "run.h"
#include "strip_spaces.h"

char * opers_redir[] = {
	">",
	"1>",
	">>",
	"1>>",
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
	char * cmd2;
	int min_oper; // The position of the first operator in opers_redir[]
	int tmp;

	stringsepar( &cmd, &cmd1, opers_redir, &min_oper);
	printf("min_oper: %d\n",min_oper);

	int status;
	int fd1, fd2;
	char * filename;
	switch( min_oper ){
		case 0:
		case 1:
			//>,1>
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);
			
			status = run( cmd1 );
			break;
			
		case 2:
		case 3:
			//>>,1>>
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);
			
			break;
		case 4:
			//2>
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);

			break;
		case 5:
			//2>>
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);

			break;
		case 6:
			//&>
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);

			break;
		case 7:
			//&>>
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);

			break;
		case 8:
			//<
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);

			break;
		case 9:
			//|
			stringsepar( &cmd, &cmd2, opers_redir, &tmp);
			printf("cmd1: ~%s~\n",cmd1);
			printf("cmd2: ~%s~\n",cmd2);
			status = run_pipe(cmd1, cmd2);
			break;
		default:
			status = run(cmd1);
	}

	return status;
}

int run_pipe( char * cmd1, char * cmd2 )
{
	int fd[2];
	int f;

	pipe(fd);

	int status;
	f = fork();
	if (f) {
		//Parent
		dup2(fd[WRITE_END], STDOUT_FILENO);
		if( errno ){
			fprintf(stderr, "-znshell: %s (%d)", strerror(errno),errno);
		}
		close(fd[READ_END]);
		run_exec(cmd1);
		wait(&status);
	} else {
		//Child	
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[WRITE_END]);
		printf("execing in child \n");
		status = run_exec(cmd2);
	}


	return status;
}
