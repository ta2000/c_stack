#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
    int *elements;
    int *top;
    int max_elements;
};

struct stack create_stack(int max_elements)
{
    struct stack stack;

    stack.max_elements = max_elements;
    stack.elements = malloc(max_elements * sizeof(*stack.elements));
    stack.top = stack.elements;

    return stack;
}

void destroy_stack(struct stack *stack)
{
    free(stack->elements);
}

void print_stack(struct stack *stack)
{
    printf("-- PRINTING STACK --\n");
    for (int *i = stack->elements; i != stack->top; i++) {
        printf("%d\n", *i);
    }
    printf("--------------------\n\n");
}

void push_stack(struct stack *stack, int value)
{
    if (stack->top - stack->elements == stack->max_elements) {
        printf("Stack is full!\n");
        return;
    }

    *stack->top = value;
    stack->top++;

    print_stack(stack);
}

int pop_stack(struct stack *stack)
{
    if (stack->top == stack->elements) {
        printf("Stack is empty!\n");
        return -1;
    }

    stack->top--;
    print_stack(stack);
    return *stack->top;
}

int main()
{
    struct stack my_stack;
    my_stack = create_stack(5);

    for (int i = 0; i < 4; i++) {
        push_stack(&my_stack, i);
    }

    for (int i = 0; i < 3; i++) {
        pop_stack(&my_stack);
    }

    for (int i = 0; i < 13; i++) {
        push_stack(&my_stack, i);
    }

    for (int i = 0; i < 9; i++) {
        pop_stack(&my_stack);
    }

    destroy_stack(&my_stack);

    return 0;
}
