#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>


char **alloc_mem(char *input_command, unsigned int words);
void freeCommand_arr(char **cmd);
unsigned int num_of_words(char *input);
void create_child(char **command_args);





#endif
