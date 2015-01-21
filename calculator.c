/*
 * calculator - Minsu Kim
 */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h" 

// push - push numbers into the stack

num_stack *push (num_stack *first_num, double number) {
	num_stack *stack;
	stack = malloc (sizeof(*stack));
	if (stack == NULL) {
		printf ("Couldn't allocate a new stack\n");
		exit(1);
	}

	stack->number = number;
	stack->prev = NULL;
	stack->next = first_num;

	if (first_num != NULL) {
		first_num->prev = stack;
 	}
	return stack;
}

// pop - pop the number at the top of the stack

double pop (num_stack *first_num) {
	num_stack *next;

	double num = first_num->number;

	next = first_num->next;

	if (next)
		next->prev = NULL;
	free(first_num);
	first_num = next;
	return num;
}

double get (num_stack *first_num) {
	return first_num->number;
}

num_stack *delete (num_stack *first_num, num_stack *num) {
	num_stack *prev, *next;

	if(num == NULL ||first_num == NULL) return first_num;

	prev = num->prev;
	next = num->next;

	if(prev)
		prev->next = num->next;

	if(next)
		next->prev = num->prev;

	free(num);

	if (num == first_num)
		return next;
	else
		return first_num;
}

int isSpaced (char *input) {
	int i;
	char *first, *last;
	char copy[strlen(input)];
	first = input;
	last = first + strlen(input) - 2;

	while (isspace(*first) != 0) {
		first++;
	}

	while (isspace(*last) != 0) {
		last--;
	}
	memcpy(copy, first, last - first + 1);

	for (i = 0; i < strlen(copy); i++) {
		if (isspace(copy[i]) != 0) {
			return 1;
		}
	}
	return 0;
}