//4.    Implement operator precedence parser
//3 4 2 * + 1 5 - /
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 100

// Stack structure for operands
typedef struct {
    int items[STACK_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return (s->top == -1);
}

void push(Stack *s, int value) {
    if (s->top == STACK_SIZE - 1) {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (is_empty(s)) {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

int evaluate_postfix(const char *postfix) {
    Stack stack;
    initialize(&stack);

    while (*postfix) {
        if (isspace(*postfix)) {
            postfix++; // Skip whitespace
            continue;
        }
        
        if (isdigit(*postfix)) {
            int operand = 0;
            while (isdigit(*postfix)) {
                operand = operand * 10 + (*postfix - '0');
                postfix++;
            }
            push(&stack, operand);
        } else {
            int right_operand = pop(&stack);
            int left_operand = pop(&stack);
            switch (*postfix) {
                case '+':
                    push(&stack, left_operand + right_operand);
                    break;
                case '-':
                    push(&stack, left_operand - right_operand);
                    break;
                case '*':
                    push(&stack, left_operand * right_operand);
                    break;
                case '/':
                    push(&stack, left_operand / right_operand);
                    break;
                default:
                    printf("Error: Invalid operator\n");
                    exit(EXIT_FAILURE);
            }
            postfix++;
        }
    }

    if (!is_empty(&stack) && stack.top == 0) {
        return stack.items[stack.top];
    } else {
        printf("Error: Invalid postfix expression\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char postfix[100];

    printf("Enter a postfix expression (tokens separated by spaces): ");
    fgets(postfix, sizeof(postfix), stdin);

    // Evaluate postfix expression
    int result = evaluate_postfix(postfix);

    printf("Result: %d\n", result);

    return 0;
}
