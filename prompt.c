#include "prompt.h"
#include "parser.h"

//this file will contain the prompt messages and link to the main file

//prints out the prompt, with the current working directory
int print_prompt(){
  char * cwd;
  cwd = malloc(sizeof(char)*256);
  getcwd(cwd,sizeof(cwd));
  
  printf("%s$: ",cwd);
  
  return 0;
}

//gets the input from the user
int get_input(){

  char * input;
  input = malloc(sizeof(char)*256);
  fgets(input,sizeof(input),stdin);

  //test
  printf("This is what you inputted: %s\n",input);
  
}
