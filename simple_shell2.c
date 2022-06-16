#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * main - execute simple shell
 * Return: 0 on success
 */

int main(void)
{
	/* ssize_t getline(char **lineptr, size_t *n, FILE *stream); */
	char *buffer = NULL;
	size_t buffer_len = 0;
	char **argv;
	unsigned int words;

	while (1)
	{	/* prompt for input from user */
		buffer = NULL;
		buffer_len = 0;

		printf("simple_shell..$ ");
		if (getline(&buffer, &buffer_len, stdin) == -1)
		{
			perror("getline()"); /* end of file handled */
			free(buffer);
			continue; /* a break might be ideal */
		}
		*(strchr(buffer, '\n')) = '\0';
		printf("%s\n", buffer);
		words = num_of_words(buffer);
		argv = alloc_mem(buffer, words);
		create_child(argv);
		free(buffer);
	}
	return (0);
}

