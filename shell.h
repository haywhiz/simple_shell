#ifndef GUARD
#define GUARD


char **alloc_mem(char *input_command, unsigned int words);
void freeCommand_arr(char **cmd);
unsigned int num_of_words(char *input);
void create_child(char **command_args);

#endif
