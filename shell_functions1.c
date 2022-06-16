#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * create_child - a function that uses fork() to create a child process
 *		  that executes the supplied command
 * @command_args: holds the address of array of command arguments
 * Return: nothing
 */

void create_child(char **command_args)
{
	pid_t child;
	char *env_args[] = {NULL};

	child = fork();
	if (child == -1)
	{
		perror("fork()");
		exit(1); /* continue might be ideal */
	}
	else if (child == 0)
	{ /* in the child */
		execve(command_args[0], command_args, env_args);
		perror("execve"); /* execve() returns only on error*/
		exit(1);
	}
	else
	{ /* BACK IN PARENT */
		freeCommand_arr(command_args);
		if (wait(NULL) == -1)
		{
			perror("wait()");
			exit(1);
		}
		/*free(buff);*/
	}
}

/**
 * num_of_words - a function that calculates the number of words in a string
 * @input: the entire string supplied via getline (command and arguments)
 * Return: the number of distinct words in the string
 */

unsigned int num_of_words(char *input)
{ /* this approach curbs the problem when a separator starts the line */
	int state = 0;
	int words = 0;

	while (*input)
	{
		if (*input == '\n' || *input == ' ' || *input == '\t')
			state = 0; /* state on 0 when we meet a separator */
		else if (state == 0) /* observe the 'else' */
		{
			++words;
			state = 1; /* chage state, we're looping thru a word */
		}

		input++;
	}
	return (words);
}

/**
 * alloc_mem - a function that creates the array of command arguments with
 *		the first entry being the command itself
 * @input_command: the entire string from getline()
 * @words: number of words in supplied string (command and args)
 * Return: pointer to an array of command arguments
 */

char **alloc_mem(char *input_command, unsigned int words)
{
	unsigned int i;
	char *word;
	char **argv_arr = malloc((words + 1) * sizeof(char *));

	if (argv_arr == NULL)
	{
		perror("malloc()");
		exit(1);
	}
	word = strtok(input_command, " ");
	*argv_arr = malloc(strlen(word + 1) * sizeof(char)); /* incl '\0' */
	if (*argv_arr == NULL)
	{
		perror("malloc()");
		freeCommand_arr(argv_arr);
		exit(1);
	}
	/* copy first word into array */
	strcpy(argv_arr[0], word);
	/* other words */
	for (i = 1; i < words; ++i)
	{
		word = strtok(NULL, " ");
		argv_arr[i] = malloc((strlen(word) + 1) * sizeof(char));
		if (argv_arr[i] == NULL)
		{
			perror("malloc()");
			freeCommand_arr(argv_arr);
			exit(1);
		}
		strcpy(argv_arr[i], word);
	}
	argv_arr[words] = NULL;
	return (argv_arr);
}

/**
 * freeCommand_arr - a function to free the memory allocated when creating the
 *			array of command arguments
 * @cmd: address of the command arguments array to be freed
 * Return: nothing
 */

void freeCommand_arr(char **cmd)
{
	int i = 0;

	if (cmd != NULL) /* if no error on general malloc */
	{
		while (cmd[i] != NULL) /* last element in the argv array is NUll ptr */
		{
			free(cmd[i]);
			++i;
		}
	}
	free(cmd);
}


