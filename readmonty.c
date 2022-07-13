#include "monty.h"

char *argument;
/**
 * readmonty - reads monty file, line by line
 * @buffer: lines in monty file
 */
void readmonty(char *buffer)
{
	char **opline;
	int i, j = 0, l, m, line = 1;
	stack_t *stack = NULL;

	opline = malloc(sizeof(char *) * 2);
	if (opline == NULL)
		fprintf(stderr, "Error: Unable to malloc\n"), exit(EXIT_FAILURE);

	for (i = 0; buffer[i]; i++, line++) /* iterate through file */
	{
		if (!opline[j])
		{
			opline[j] = malloc(sizeof(char) * 1024);
			if (opline[j] == NULL)
				fprintf(stderr, "Error: malloc failed\n"), exit(EXIT_FAILURE);
		} l = 0;
		for (; buffer[i] != '\n'; i++) /* read till new line */
		{
			if (buffer[i] == ' ' && j < 1)
			{
				opline[j][l] = '\0'; /* null terminate string */
				j++;
				if (!opline[j])
				{
					opline[j] = malloc(sizeof(char) * 1024);
					if (opline[j] == NULL)
						fprintf(stderr, "Error: malloc failed\n"), exit(EXIT_FAILURE);
				} l = 0;
			}
			if (buffer[i] == ' ') /* skip spaces */
				continue;
			opline[j][l] = buffer[i], l++; /* copy character and increment l */
		}
		opline[j][l] = '\0', argument = opline[1]; /* set argument variable */
		callfunction(&stack, line, opline), j = 0;
	}

	for (m = 0; opline[m]; m++) /* free mallocs */
		free(opline[m]);
	free(opline), freestack(&stack);
}

/**
 * callfunction - finds the right function and calls it
 * @stack:  stack
 * @line_number: line number
 * @opline: array of arguments
 */
void callfunction(stack_t **stack, unsigned int line_number, char **opline)
{
	int k;
	instruction_t opcodes[] = {
		{"push", pushnode},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL}
	};

	/* find the right function */
	for (k = 0; opcodes[k].opcode != NULL; k++)
	{
		if (strcmp(opcodes[k].opcode, opline[0]) == 0)
		{
			opcodes[k].f(stack, line_number);
			break;
		}
		if (opcodes[k + 1].opcode == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opline[0]);
			exit(EXIT_FAILURE);
		}
	}
}
