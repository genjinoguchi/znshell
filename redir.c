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
	"<"
};

/*
 * Runs functions. implementations of following redirection operators included.
 * Expects ;, &&, and || to be filtered out.
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
int process_redir( char * cmd )
{
	char * cmd1;
	int status;

	cmd1 = strsep(&cmd, "|"); //Split the input command by the first occurence of |

	if( cmd ) {
		status = run_pipe(cmd1, cmd);
	} else {
		status = file_redir( cmd1 );
	}
	return status;	
}

int file_redir( char * cmd)
{
	char * cmd1;
	int min_oper; // The position of the first operator in opers_redir[]
	int tmp;

	stringsepar( &cmd, &cmd1, opers_redir, &min_oper);

	int status;
	int fd1;
	char * filename;
	int fd[2];
	switch( min_oper ){
		case 0:
		case 1:
			//>,1>
			stringsepar( &cmd, &filename, opers_redir, &tmp);
			fd[0]=STDOUT_FILENO;
			fd[1]=-1;
			run( cmd1, filename, fd, O_WRONLY | O_CREAT | O_TRUNC);
			break;
		case 2:
		case 3:
			//>>,1>>
			stringsepar( &cmd, &filename, opers_redir, &tmp);
			fd[0]=STDOUT_FILENO;
			fd[1]=-1;
			run( cmd1, filename, fd, O_WRONLY | O_CREAT | O_APPEND );
			break;
		case 4:
			//2>
			stringsepar( &cmd, &filename, opers_redir, &tmp);
			fd[0]=STDERR_FILENO;
			fd[1]=-1;
			run( cmd1, filename, fd, O_WRONLY | O_CREAT | O_TRUNC);
			break;
		case 5:
			//2>>
			stringsepar( &cmd, &filename, opers_redir, &tmp);
			fd[0]=STDERR_FILENO;
			fd[1]=-1;
			run( cmd1, filename, fd, O_WRONLY | O_CREAT | O_APPEND);
			break;
		case 6:
			//&>
			stringsepar( &cmd, &filename, opers_redir, &tmp);
			fd[0]=STDERR_FILENO;
			fd[1]=STDOUT_FILENO;
			run( cmd1, filename, fd, O_WRONLY | O_CREAT | O_TRUNC);
			break;
		case 7:
			//&>>
			stringsepar( &cmd, &filename, opers_redir, &tmp);
			fd[0]=STDERR_FILENO;
			fd[1]=STDOUT_FILENO;
			run( cmd1, filename, fd, O_WRONLY | O_CREAT | O_APPEND);
			break;
		case 8:
			//<
			stringsepar( &cmd, &filename, opers_redir, &tmp);
			fd[0]=STDIN_FILENO;
			fd[1]=-1;
			run( cmd1, filename, fd, O_RDONLY);
			break;
		default:
			status = run(cmd1, NULL, fd, 0);
	}

	return status;
}

//I KEEP GETTING INVALID ARGUMENT ERROR
//I HAVE NO FREAKING IDEA WHY
//WILBUR PLEASE HELP
//PLEAAAAAAAASE
void append_file(char * filename,int fd2)
{
	int fd1;
	fd1 = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (errno) {
		fprintf(stderr, "-znshell: %s (%d)\n",strerror(errno), errno);
		//exit(errno);
	}
	errno = 0;
	dup2(fd1, fd2);
}

void append_all(char * filename, int fd2)
{
	int fd1;
	errno = 0;
	fd1 = open(filename, O_CREAT | O_WRONLY | O_APPEND);
	if (errno) {
		fprintf(stderr, "-znshell: %s (%d)\n",strerror(errno), errno);
		exit(errno);
	}
	errno = 0;
	dup2(fd1, STDERR_FILENO);
	dup2(fd1, STDOUT_FILENO);
}

void trunc_file(char * filename,int fd2)
{	
	int fd1;
	fd1 = open(filename,O_WRONLY | O_CREAT,0644);
	if(errno){
		printf("-znshell: %s (%d)\n",strerror(errno), errno);
	}
	dup2(fd1, fd2);
}

void trunc_all(char * filename, int fd2)
{
	int fd1;
	fd1 = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (errno) {
		fprintf(stderr, "-znshell: %s (%d)\n",strerror(errno), errno);
		exit(errno);
	}
	errno = 0;
	dup2(fd1, STDOUT_FILENO);
	dup2(fd1, STDERR_FILENO);
}

/*
 * Still doesn't work.
 */
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
		//run_exec(cmd1);
		wait(&status);
	} else {
		//Child	
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[WRITE_END]);
		printf("execing in child \n");
		//status = run_exec(cmd2);
		exit(0);
	}


	return status;
}
