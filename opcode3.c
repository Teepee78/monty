#include "monty.h"

/**
 * modelem - mods the top 2 variables
 * @stack: stack
 * @line_number: line number
 */
void modelem(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->prev == NULL)
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

/**
 * pchar - prints the char of the top variable
 * @stack: stack
 * @line_number: line number
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	if (isascii((*stack)->n) == 0)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%c\n", (*stack)->n);
}

/**
 * pstr - prints a string starting from the top variable
 * @stack: stack
 * @line_number: line number
 */
void pstr(stack_t **stack, unsigned int __attribute__ ((unused)) line_number)
{
	stack_t *temp = *stack;

	while (temp != NULL)
	{
		if (temp->n == 0 || !isascii(temp->n))
			break;
		printf("%c", temp->n);
		temp = temp->prev;
	}
	printf("\n");
}

/**
 * rotl - rotates the stack
 * @stack: stack
 * @line_number: line number
 */
void rotl(stack_t **stack, unsigned int __attribute__ ((unused)) line_number)
{
	stack_t *temp = *stack, *temp2;

	if (*stack == NULL)
		return;

	while (temp->prev != NULL) /* go to last node */
		temp = temp->prev;

	*stack = temp;
	while (temp != NULL)
	{
		temp2 = temp->prev;
		temp->prev = temp->next;
		temp->next = temp2;
		temp = temp->prev;
	}
}
