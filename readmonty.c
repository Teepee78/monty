#include "monty.h"

char *argument = NULL;
/**
 * readmonty - reads monty file, line by line
 * @buffer: lines in monty file
 */
void readmonty(char *buffer)
{
	char *opline, *oparg, *arg1;
	int i = 0, line = 1;
	stack_t *stack = NULL;

	opline = strtok(buffer, "\n"); /* split buffer into lines */
	while (opline != NULL)
	{
		argument = NULL;
		oparg = strtok_r(opline, " ", &opline); /* split opline by spaces */
		while (oparg != NULL && i < 2) /* get arguments */
		{
			if (i == 0)
				arg1 = oparg;
			else if (i == 1)
				argument = oparg;
			i++;
			oparg = strtok_r(NULL, " ", &opline);
		}
		if (arg1[0] == '#') /* handle comments */
		{
			opline = strtok(NULL, "\n");
			line++, i = 0;
			continue;
		}
		callfunction(&stack, line, arg1);
		line++, i = 0;
		opline = strtok(NULL, "\n");
	}
	if (stack != NULL)
		freestack(&stack);
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
		{"pchar", pchar},
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
