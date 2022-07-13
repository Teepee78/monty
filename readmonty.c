#include "monty.h"

char *argument;
/**
 * readmonty - reads monty file, line by line
 * @buffer: lines in monty file
 */
void readmonty(char *buffer)
{
	char **opline;
	int i, j = 0, k, l, m, line = 1;
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
	stack_t *stack = NULL;

	opline = malloc(sizeof(char *) * 2);
	if (opline == NULL)
	{
		fprintf(stderr, "Error: Unable to malloc");
		exit(EXIT_FAILURE);
	}

	/* iterate through file */
	for (i = 0; buffer[i]; i++)
	{
		if (!opline[j])
		{
			opline[j] = malloc(sizeof(char) * 1024);
			if (opline[j] == NULL)
			{
				fprintf(stderr, "Error: malloc failed");
				exit(EXIT_FAILURE);
			}
		}
		/* read till new line */
		l = 0;
		while (buffer[i] != '\n')
		{
			if (buffer[i] == ' ' && j < 1)
			{
				opline[j][l] = '\0'; /* null terminate string */
				j++;
				if (!opline[j])
				{
					opline[j] = malloc(sizeof(char) * 1024);
					if (opline[j] == NULL)
					{
						fprintf(stderr, "Error: malloc failed");
						exit(EXIT_FAILURE);
					}
				}
				l = 0;
			}
			if (buffer[i] == ' ')
			{
				i++;
				continue;
			}
			opline[j][l] = buffer[i];
			l++;
			i++;
		}
		opline[j][l] = '\0';
		argument = opline[1]; /* set argument variable */

		/* find the right function */
		for (k = 0; opcodes[k].opcode != NULL; k++)
		{
			if (strcmp(opcodes[k].opcode, opline[0]) == 0)
			{
				printf("calling function\n");
				opcodes[k].f(&stack, line);
				break;
			}
			if (opcodes[k + 1].opcode == NULL)
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line, opline[0]);
				exit(EXIT_FAILURE);
			}
		}
		j = 0;
		line++;
	}

	/* free mallocs */
	for (m = 0; opline[m]; m++)
		free(opline[m]);
	free(opline);
}
