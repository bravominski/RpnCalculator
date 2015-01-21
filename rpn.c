/*
 * main.c - Minsu Kim
 */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
#define MAX_LENGTH 200

//Print out the first stack
 void print_stack (num_stack *first_num) {
 	num_stack *top = first_num;
 	printf("The top stack is %f\n", top->number);
 }

 int main () {
 	char input[MAX_LENGTH]; // array to store input
 	num_stack *first_num = NULL; // pointer to the first/top stack
 	num_stack *second_num = NULL; // pointer to the second stack
 	double number; // number to store in each stack
 	int i, num_point, non_digit, isSpace; // int i for "for loop"

 	while(1) {
 		char operator[MAX_LENGTH]; // array to store the trimmed input
 		num_point = 0;
 		non_digit = 0;
 		isSpace = 0; // boolean(does input have a white space in the middle)
 		printf("Enter input : ");

 		fgets (input, MAX_LENGTH, stdin); // take input from keyboard
 		if (input[0] == '\n') { // empty input(just newline input) is invalid
 			printf("INVALID COMMAND!\n");
  			continue;
 		}
 		isSpace = isSpaced(input); // check if there is a space in the middle of input
 		if (isSpace == 1) {
 			printf("INVALID COMMAND!\n");
  			continue;
 		}
  		sscanf(input, " %s \n", input); // trim the whitespace before and after the input command
  		
  		for (i = 0; i < strlen(input); i++) { // check the number of non-digit char and the number of point '.'
  			if (isdigit(input[i]) == 0) {
  				non_digit++;
  				if (input[i] == '.') {
  					num_point++;
  				}
  			}
  		}

  		if (num_point == 1 && strlen(input) == 1) { // If the input is just point, then it's invalid
  			printf("INVALID COMMAND!\n");
  			continue;
  		}
  		else if (non_digit == 0 || (non_digit == 1 && num_point == 1) || (non_digit == 1 && strlen(input) > 1 && input[0] == '-') || (non_digit == 2 && strlen(input) > 1 && input[0] == '-' && num_point == 1)) { // input is number if all char are digits or only 1 non-digit which is a point
  			sscanf(input, "%lf", &number);
  			if (first_num == NULL) {
 				first_num = push(first_num, number);
 				continue;
 			}
 			else {
 				second_num = first_num;
 				first_num = push(first_num, number);
 				continue;
 			}
  		}
  		else {
			sscanf(input, "%s", operator); // if input is operator command, 
			
			for (i = 0; i < strlen(operator); i++) { // convert in lowercase,
	 			operator[i] = tolower(operator[i]);
	 		}

			if (strcmp(operator, "+") == 0) { // if +, addition
				if (first_num == NULL || second_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				double first_stack = pop(first_num);
				num_stack *temp = second_num->next;
				double second_stack = pop(second_num);
				second_num = temp;
				first_num = push(first_num, first_stack + second_stack);
				first_num->next = second_num;
				print_stack(first_num);
				continue;
			}

			if (strcmp(operator, "-") == 0) { // if -, subtraction
				if (first_num == NULL || second_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				double first_stack = pop(first_num);
				num_stack *temp = second_num->next;
				double second_stack = pop(second_num);
				second_num = temp;
				first_num = push(first_num, second_stack - first_stack);
				first_num->next = second_num;
				print_stack(first_num);	
				continue;
			}

			if (strcmp(operator, "*") == 0) { // if *, multiplication
				if (first_num == NULL || second_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				double first_stack = pop(first_num);
				num_stack *temp = second_num->next;
				double second_stack = pop(second_num);
				second_num = temp;
				first_num = push(first_num, first_stack * second_stack);
				first_num->next = second_num;
				print_stack(first_num);
				continue;
			}

			if (strcmp(operator, "/") == 0) { // if /, division
				if (first_num == NULL || second_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				num_stack *temp = second_num->next;
				double second_stack = pop(second_num);
				if (second_stack != 0) {
					double first_stack = pop(first_num);
					second_num = temp;
					first_num = push(first_num, first_stack / second_stack);
					first_num->next = second_num;
					print_stack(first_num);
					continue;
				}
				else {
					second_num = push(second_num, second_stack);
					second_num->next = temp;
					first_num->next = second_num;
					printf("Error: Division by zero\n");
					continue;
				}			
			}

			// Trigs (sin, cos, tan) and log, exponential
			if (strcmp (operator, "sin") == 0) {
				if (first_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				num_stack *temp = first_num->next;
				first_num = push(first_num, sin(pop(first_num)));
				first_num->next = temp;
				print_stack(first_num);
				continue;
			}

			if (strcmp (operator, "cos") == 0) {
				if (first_num == NULL) {
					printf("Stack Error\n");
					continue;
				}			
				num_stack *temp = first_num->next;
				first_num = push(first_num, cos(pop(first_num)));	
				first_num->next = temp;
				print_stack(first_num);
				continue;
			}

			if (strcmp (operator, "tan") == 0) {
				if (first_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				num_stack *temp = first_num->next;
				first_num = push(first_num, tan(pop(first_num)));
				first_num->next = temp;
				print_stack(first_num);
				continue;
			}

			if (strcmp (operator, "log") == 0) {
				if (first_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				num_stack *temp = first_num->next;
				first_num = push(first_num, log(pop(first_num)));
				first_num->next = temp;
				print_stack(first_num);
				continue;
			}

			if (strcmp (operator, "exp") == 0) {
				if (first_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				num_stack *temp = first_num->next;
				first_num = push(first_num, exp(pop(first_num)));
				first_num->next = temp;
				print_stack(first_num);
				continue;
			}

			// duplicate the top stack
			if (strcmp (operator, "dup") == 0) {
				if (first_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				num_stack *temp2 = second_num;
				num_stack *temp1 = first_num;
				second_num = temp1;
				first_num = push(first_num, get(first_num));
				second_num->next = temp2;
				print_stack(first_num);
				continue;
			}

			// swap first and the second stack
			if (strcmp (operator, "swap") == 0) {
				if (first_num == NULL || second_num == NULL) {
					printf("Stack Error\n");
					continue;
				}
				num_stack *temp = second_num->next;
				double first_stack = pop(first_num);
				double second_stack = pop(second_num);
				second_num = push(second_num, first_stack);
				first_num = push(first_num, second_stack);
				second_num->next = temp;
				first_num->next = second_num;
				print_stack(first_num);
				continue;
			}

			// free all stack memory and exit the program.
			if (strcmp (operator, "quit") == 0) {
				while(first_num) {
					first_num = delete (first_num, first_num);
				}
				exit(0);	
			}
			
			// commands not satisfying any of the conditions above, are invalid
	 		printf("INVALID COMMAND!\n");
	 		}	
 	}
}
