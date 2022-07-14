#include "monty.h"

char *argument;
/**
 * readmonty - reads monty file, line by line
 * @buffer: lines in monty file
 */
void readmonty(char *buffer)
{
	char *opline, *oparg, *arg1;
	int i = 0, line = 0;
	stack_t *stack = NULL;

	opline = malloc(sizeof(char) * 1024);
	if (opline == NULL)
		fprintf(stderr, "Error: Unable to malloc\n"), exit(EXIT_FAILURE);
	oparg = malloc(sizeof(char) * 256);
	if (oparg == NULL)
		fprintf(stderr, "Error: Unable to malloc\n"), exit(EXIT_FAILURE);

	opline = strtok(buffer, "\n"); /* split buffer into lines */
	while (opline != NULL)
	{
		if (opline[0] == '#') /* handle comments */
		{
			opline = strtok(NULL, "\n");
			line++, i = 0;
			continue;
		}
		oparg = strtok_r(opline, " ", &opline); /* split opline by spaces */
		while (oparg != NULL && i < 2) /* get arguments */
		{
			switch (i)
			{
				case 0:
					arg1 = oparg;
					break;
				case 1:
					argument = oparg;
					break;
			}
			i++;
			oparg = strtok_r(NULL, " ", &opline);
		}
		callfunction(&stack, line, arg1);
		line++, i = 0;
		opline = strtok(NULL, "\n");
	}
	free(oparg); /* free mallocs */
	free(opline), freestack(&stack);
}

/**
 * callfunction - finds the right function and calls it
 * @stack:  stack
 * @line_number: line number
 * @arg1: arg1
 */
void callfunction(stack_t **stack, unsigned int line_number, char *arg1)
{
	int k;
	instruction_t opcodes[] = {
		{"push", pushnode},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"sub", sub},
		{"div", divelem},
		{"mul", multelem},
		{"mod", modelem},
		{"nop", nop},
		{NULL, NULL}
	};

	/* find the right function */
	for (k = 0; opcodes[k].opcode != NULL; k++)
	{
		if (strcmp(opcodes[k].opcode, arg1) == 0)
		{
			opcodes[k].f(stack, line_number);
			break;
		}
		if (opcodes[k + 1].opcode == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, arg1);
			exit(EXIT_FAILURE);
		}
	}
}
