#include "monty.h"

/**
 * pushnode - push opcode
 * @stack: pointer to stack
 * @line_number: line number
 */
void pushnode(stack_t **stack, unsigned int line_number)
{
	stack_t *new_stack;
	int arg;

	if (argument == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	/* check if argument is a string */
	if (_isdigit(argument))
		arg = atoi(argument);
	else
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* check if stack is empty */
	if (*stack == NULL)
	{
		*stack = create_stack(arg);
	}
	else /* add node */
	{
		new_stack = malloc(sizeof(stack_t));
		if (new_stack == NULL)
		{
			fprintf(stderr, "Error: malloc failed\n");
			exit(EXIT_FAILURE);
		}

		new_stack->n = arg;
		new_stack->next = NULL;
		new_stack->prev = *stack;
		(*stack)->next = new_stack;
		(*stack) = new_stack;
	}
}

/**
 * pall - print values in a stack
 * @stack: pointer to stack
 * @line_number: line number
 */
void pall(stack_t **stack, unsigned int __attribute__ ((unused)) line_number)
{
	stack_t *temp = *stack;

	if (*stack == NULL)
		return;

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->prev;
	}
}

/**
 * pint - print top value
 * @stack: pointer to stack
 * @line_number: line number
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}

/**
 * pop - deletes the topmost node
 * @stack: pointer to stack
 * @line_number: line number
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->prev;
	if (*stack != NULL)
		(*stack)->next = NULL;
	free(temp);
}

/**
 * swap - swap the top 2 variables
 * @stack: stack
 * @line_number: line number
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack == NULL || (*stack)->prev == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->n;
	(*stack)->n = (*stack)->prev->n;
	(*stack)->prev->n = temp;
}
