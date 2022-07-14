#include "monty.h"

/**
 * main - monty interpreter
 * @argc: argument count
 * @argv: argument variables
 * Return: EXIT_SUCCESS
 */
int main(int argc, __attribute__((unused)) char **argv)
{
	int montyfile, readfile;
	char *buffer;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	/* open file */
	montyfile = open(argv[1], O_RDONLY);
	if (montyfile == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* read file */
	buffer = malloc(sizeof(char) * BUFFSIZE);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	readfile = read(montyfile, buffer, BUFFSIZE);
	if (readfile == -1)
	{
		fprintf(stderr, "Error: can't read file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	buffer[readfile] = '\0'; /* null teminate */
	readmonty(buffer);

	free(buffer);
	return (EXIT_SUCCESS);
}
