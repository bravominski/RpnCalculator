/*
 * calculator.h - Minsu Kim
 */

typedef struct num_stack {
	double number;
	struct num_stack *prev, *next;
} num_stack;

num_stack *push (num_stack *first_num, double number);
double pop (num_stack *first_num);
double get (num_stack *first_num);
num_stack *delete (num_stack *first_num, num_stack *num);
char *trimmed (char *input, char *ret);
int isSpaced (char *input);