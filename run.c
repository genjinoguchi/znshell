#include "run.h"
#include "check.h"
#include "strip_spaces.h"

/*
 * Runs a command.
 * Expects chain and redirection operators to be filtered out prior.
 * Functions currently supported:
 * 	* All exec-able functions
 * 	* cd
 * 	* exit
 */
int run( char * cmd )
{
	int status;

	cmd = strip_spaces( cmd );

	if ( check_cd( cmd ) ){
		status = run_cd( cmd );
	} else if ( check_exit( cmd ) ){
		status = run_exit( cmd );
	} else {
		status = run_exec( cmd );
	}
	
	return status;
}

/*
 * Parses a command in preparation for an execvp call.
 * args is a pointer to a string array.
 */
void parse_exec( char * cmd, char *** args )
{
	char * cmdname;
	
	//gets the name of the command and sets it to the first position of the array
	cmdname = strsep(&cmd," ");
	(*args)[0] = cmdname;

	int index = 1;
	//gets arguments
	while (cmd){
		(*args)[index] = strsep(&cmd," ");
		index++;
	}

	//array must null-terminate
	(*args)[index] = NULL;
}

/*
 * Runs a function using execvp.
 */
int run_exec(char * cmd)
{
	char ** args;
	args = (char **)malloc(256 * sizeof(char *));

	parse_exec(cmd, &args);

	int f,w,status;
	f = fork();
	if (f){//parent waits
		w = wait(&status);
	} else {//child executes
		execvp(args[0],args);
		if (errno){
			fprintf(stderr,"-znshell: %s\n",strerror(errno));
			errno = 0;
		}
		exit(0);
	}

	free( args );
	
	return status;
}

/*
void run_exec( char * cmd )
{
	parse_exec(cmd, args); 

}
*/

//changes directory into the directory specified by the argument
int run_cd(char * command){

	char * temp;
	temp = strsep(&command," ");
	//command now has the directory path

	int status;
	status = chdir(command);

	//status is 0 if it works, -1 if not

	if(status == 0){
		//printf("Directory changed!\n");
	} else {
		printf("Directory %s not found.\n",command);
	}
	return status;
}

int run_exit(char * command){
	exit(0);
}


