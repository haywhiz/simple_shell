#ifndef GUARD
#define GUARD


char **alloc_mem(char *input_command, unsigned int words);
void freeCommand_arr(char **cmd);
unsigned int num_of_words(char *input);
void create_child(char **command_args);
void sig_handler(int sig_num)
void _EOF(int len, char *buff)
void _isatty(void)


#endif
