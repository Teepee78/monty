#include "monty.h"

/**
 * _isdigit - check if a string is a digit
 * @string: string
 * Return: 1 if it is digit
 */
int _isdigit(char *string)
{
	int i;

	for (i = 0; string[i]; i++)
	{
		if (isdigit(string[i]) == 0)
			return (0);
	}
	return (1);
}
