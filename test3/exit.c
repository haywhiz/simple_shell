#include "shell.h"
#include "_string.h"
#include <ctype.h>
#include <stdlib.h>
/**
 * hsh_exit - Exit shell
 *
 * @shell: shell data
 * Return: 0 for success otherwise another integer
 */
int hsh_exit(shell_t *shell)
{
	int status = 0;

	if (shell->argv[1])
	{
		if (!isdigit(shell->argv[1]))
		{
			write_error(shell, 2);
			return (0);
		}

		status = atoi(shell->argv[1]);
		shell->exitcode = status % 256;
	}

	return (EXIT_IND);
}
