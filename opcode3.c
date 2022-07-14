#include "monty.h"

/**
 * modelem - mods the top 2 variables
 * @stack: stack
 * @line_number: line number
 */
void modelem(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if ( *stack == NULL || (*stack)->prev == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->prev->n %= (*stack)->n;
	temp = *stack;
	(*stack) = (*stack)->prev;
	(*stack)->next = NULL;
	free(temp);
}
