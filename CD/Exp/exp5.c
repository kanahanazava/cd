#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 10
#define MAX_NT 5
#define MAX_T 5
#define MAX_STACK 1000

char production[MAX_PROD][10];
char nt[MAX_NT], t[MAX_T];
int num_prod, num_nt, num_t;
int parsing_table[MAX_NT][MAX_T];
char stack[MAX_STACK];
int top = -1;

// Function to push a character onto the stack
void push(char c) {
    if (top == MAX_STACK - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = c;
}

// Function to pop a character from the stack
char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

// Function to construct the parsing table based on production rules
void construct_parsing_table() {
    int i, j, k, flag;
    char temp[10];

    for (i = 0; i < num_prod; i++) {
        strcpy(temp, production[i]);
        flag = 0;
        for (j = 0; temp[j] != '\0'; j++) {
            if (temp[j] == '>') {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            for (j = 0; j < num_t; j++) {
                parsing_table[i][j] = i + 1; // Shift action
            }
        } else {
            for (j = 0; j < num_t; j++) {
                flag = 0;
                for (k = 3; temp[k] != '\0'; k++) {
                    if (temp[k] == t[j]) {
                        parsing_table[i][j] = i + 1; // Shift action
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    parsing_table[i][j] = -1; // No valid action (error)
                }
            }
        }
    }
}

int main() {
    int i, j, line_count = 0;
    char input[100];

    printf("Enter the number of non-terminals: ");
    scanf("%d", &num_nt);
    printf("Enter the non-terminals: ");
    for (i = 0; i < num_nt; i++) {
        scanf(" %c", &nt[i]);
    }

    printf("Enter the number of terminals: ");
    scanf("%d", &num_t);
    printf("Enter the terminals: ");
    for (i = 0; i < num_t; i++) {
        scanf(" %c", &t[i]);
    }

    printf("Enter the number of productions: ");
    scanf("%d", &num_prod);
    printf("Enter the productions (e.g., S->AB): ");
    for (i = 0; i < num_prod; i++) {
        scanf("%s", production[i]);
    }

    construct_parsing_table();

    printf("\nEnter the input string: ");
    scanf("%s", input);

    push('$'); // Push initial marker '$'
    push(nt[0]); // Push start symbol onto the stack

    i = 0;
    while (input[i] != '\0' || top > 0) {
        printf("\nStack: ");
        for (j = top; j >= 0; j--) {
            printf("%c", stack[j]);
        }
        printf("\tInput: %s", &input[i]);

        if (top == -1) {
            printf("\nError: Stack is empty unexpectedly\n");
            exit(EXIT_FAILURE);
        }

        if (stack[top] == input[i]) {
            pop(); // Matched, pop from stack
            i++; // Move to next input symbol
        } else {
            // Find action in parsing table
            for (j = 0; j < num_t; j++) {
                if (parsing_table[stack[top] - nt[0]][j] != -1) {
                    if (parsing_table[stack[top] - nt[0]][j] == num_prod) {
                        // Acceptance state
                        printf("\nString accepted\n");
                        exit(EXIT_SUCCESS);
                    } else if (parsing_table[stack[top] - nt[0]][j] > 0) {
                        // Reduce by production
                        int prod_index = parsing_table[stack[top] - nt[0]][j] - 1;
                        pop(); // Pop non-terminal from stack
                        // Push production from right to left onto stack
                        for (int k = strlen(production[prod_index]) - 1; k >= 3; k--) {
                            push(production[prod_index][k]);
                        }
                        break;
                    }
                }
            }
            if (j == num_t) {
                printf("\nError in input string\n");
                exit(EXIT_FAILURE);
            }
        }

        // Increment line count and check termination condition
        line_count++;
        if (line_count >= 10) {
            printf("\nReached termination after 10 lines\n");
            break;
        }
    }

    printf("\nError in input string\n");
    return 0;
}
