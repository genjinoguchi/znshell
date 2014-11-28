#include "prompt.h"
#include "parser.h"

//this will contain all of the parsing functions

//main parsing function
//input will have a newline character from the fgets
int parse_input(char * input){
  //takes out the newline character
  input = strsep(&input,"\n");
  if (check_cd(input)){
    run_cd(input);
  } else {
    execute_command(input);
  }

  
  return 0;
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
  /*
  if(!r){
    printf("Directory changed!\n");
  } else {
    printf("Something went wrong\n");
  }
  */
}
