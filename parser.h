#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include <string.h>

int parse_input();
char * strip_spaces(char * input);

int execute_command(char * cmd);

int check_cd(char * command);
int run_cd(char * command);

int check_exit(char * command);
int run_exit(char * command);
