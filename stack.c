#include "monty.h"

/**
 * create_stack - create a stack
 * @n: node
 * Return: stack
 */
stack_t *create_stack(int n)
{
	stack_t *stack;

	stack = malloc(sizeof(stack_t));
	if (stack == NULL)
	{
		fprintf(stderr, "Error: Unable to initialize stack\n");
		exit(EXIT_FAILURE);
	}

	stack->n = n;
	stack->prev = NULL;
	stack->next = NULL;

	return (stack);
}

/**
 * freestack - free stack
 * @stack: stack
 */
void freestack(stack_t **stack)
{
	stack_t *temp;

	while (*stack != NULL)
	{
		temp = *stack;
		*stack = (*stack)->prev;
		free(temp);
	}
}
