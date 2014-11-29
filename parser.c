#include "prompt.h"
#include "parser.h"

//this will contain all of the parsing functions

//main parsing function
//input will have a newline character from the fgets
int parse_input(char * input){
  //takes out the newline character
  input = strsep(&input,"\n");
  input = strip_spaces(input);

  printf("input after stripping: %s\n",input);
  
  if (check_cd(input)){
    run_cd(input);
  } else if (check_exit(input)){
    run_exit(input);
  } else {
    execute_command(input);
  }
  
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

//executes a command
int execute_command(char * cmd){

  //printf("executing this: %s\n",cmd);

  char * cmdname;
  char ** args;
  args = malloc(256*sizeof(char *));
  //gets the name of the command and sets it to the first position of the array
  cmdname = strsep(&cmd," ");
  args[0] = cmdname;
  
  int index = 1;
  //gets arguments
  while (cmd){
    args[index] = strsep(&cmd," ");
    index++;
  }

  //array must null-terminate
  args[index] = NULL;
  
  int f,w;
  f = fork();
  if (f){//parent waits
    w = wait();
  } else {//child executes
    execvp(cmdname,args);
    if (errno){
      printf("%s is not a recognized command\n",cmdname);
      errno = 0;
    }
    exit(0);
  }
  
  return 0;
}

int check_cd(char * command){
  //location of cd substring in command
  char * cdloc;
  cdloc = strstr(command, "cd");
  if (cdloc == command){
    return 1;
  }
  return 0;
}

//changes directory into the directory specified by the argument
int run_cd(char * command){

  char * temp;
  temp = strsep(&command," ");
  //command now has the directory path
  
  int r;
  r = chdir(command);
  
  //r is 0 if it works, -1 if not
  
  if(!r){
    //printf("Directory changed!\n");
  } else {
    printf("Directory %s not found.\n",command);
  }
  
}

//similar in nature to check_cd
int check_exit(char * command){
  char * exitloc;
  exitloc = strstr(command, "exit");
  if (exitloc == command){
    return 1;
  }
  return 0;
}

int run_exit(char * command){
  exit(0);
}

