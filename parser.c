#include "prompt.h"
#include "parser.h"
#include "run.h"

//this will contain all of the parsing functions

//main parsing function
//input will have a newline character from the fgets
int parse_input(char * input){
	//takes out the newline character
	input = strsep(&input,"\n");
	input = strip_spaces(input);

	//printf("input after stripping: %s\n",input);

	run(input);

	return 0;
}

//strips excess space from the in the input and returns the new string
char * strip_spaces(char * input){
	int i = 0;
	//starting from the beginning, get rid of the space
	while(input[i] == ' '){
		input = &input[1];
	}

	//going through the input
	while(input[i]){
		//two consecutive spaces
		if (input[i] == ' ' && input[i+1] == ' '){
			int numConsec = 2;
			while(input[i+numConsec] == ' '){
				numConsec++;
			}
			//at this point, i + numConsec is the first non-space character
			int j = 1;
			while(input[i+numConsec]){
				input[i+j] = input[i+numConsec];
				j++;
				numConsec++;
			}
			//at this point, i + numConsec is the null at the end
			input[i+j] = 0;
		}
		i++;
	}
	//end of input
	if (input[i-1] == ' '){
		input[i-1] = 0;
	}

	return input;
}
//check for ;
long check_semicolon(char * command){
	return (long)strchr(command,';');
}

/*
//run multiple commands with the ;
int run_multiple_commands(char * command){
	char * temp;
	while(command){
		temp = strsep(&command,";");
		temp = strip_spaces(temp);
		execute_command(temp);
	}

	return 1;
}

//for > and < currently
int check_redirection(char * command){
	check_redirect_output(command);
	check_redirect_input(command);
	return 0;
}

//for >, runs redirection procedure if true
int check_redirect_output(char * command){
	if (strchr(command,'>')){
		//stores the actual command
		char * cmd;

		//command now has the file path
		cmd = strsep(&command,">");
		cmd = strip_spaces(cmd);
		command = strip_spaces(command);
		//temporary stdout file descriptor
		int stdoutfd;
		stdoutfd = dup(STDOUT_FILENO);
		//target file descriptor
		int targetfd;

		return 1;
	}
	return 0;
}

//for <, runs redirection procedure if true
int check_redirect_input(char * command){
	if (strchr(command,'<')){
		return 2;
	}
	return 0;
}
*/
