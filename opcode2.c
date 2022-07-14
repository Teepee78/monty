#include "monty.h"

/**
 * add - adds the top 2 variables
 * @stack: stack
 * @line_number: line number
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if ( *stack == NULL || (*stack)->prev == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->prev->n += (*stack)->n;
	temp = *stack;
	(*stack) = (*stack)->prev;
	(*stack)->next = NULL;
	free(temp);
}

/**
 * nop - does nothing
 * @stack: stack
 * @line_number: line number
 */
void nop(stack_t **stack, unsigned int __attribute__ ((unused)) line_number)
{
	stack_t __attribute__ ((unused)) *stacks = *stack;
}
