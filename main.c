#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test_element
{
    char *name;
    int name_length;
    int age;
};

void init_test_element(
    struct test_element *element,
    const char *name,
    int age)
{
    element->name_length = strlen(name) + 1;
    element->name = malloc(element->name_length);
    strcpy(element->name, name);

    element->age = age;
}

struct stack
{
    char *elements;
    size_t element_size;
    char *top;
    int max_elements;
};

struct stack create_stack(int max_elements, size_t element_size)
{
    struct stack stack;

    stack.max_elements = max_elements;
    stack.elements = malloc(max_elements * element_size);
    stack.element_size = element_size;
    stack.top = stack.elements;

    return stack;
}

void destroy_stack(struct stack *stack)
{
    free(stack->elements);
}

void print_stack(struct stack *stack)
{
    printf("Capacity: %ld/%d\n",
            (stack->top - stack->elements) / stack->element_size,
            stack->max_elements);

    printf("-- PRINTING STACK --\n");
    for (char *i = stack->elements; i != stack->top; i+=stack->element_size) {
        struct test_element *element = (struct test_element*)i;
        printf("NAME: %s\nAGE: %d\n\n", element->name, element->age);
    }
    printf("--------------------\n\n");
}

void push_stack(struct stack *stack, void* value)
{
    if ((unsigned int)(stack->top - stack->elements) ==
            stack->max_elements * stack->element_size) {
        printf("Stack is full!\n");
        return;
    }

    memcpy(stack->top, value, stack->element_size);
    stack->top += stack->element_size;

    print_stack(stack);
}

void* pop_stack(struct stack *stack)
{
    if (stack->top == stack->elements) {
        printf("Stack is empty!\n");
        return NULL;
    }

    stack->top -= stack->element_size;
    print_stack(stack);
    return stack->top;
}

int main()
{
    struct stack my_stack;
    my_stack = create_stack(5, sizeof(struct test_element));

    const char *names[] = {
        "Frank",
        "Christopher",
        "Philip",
        "Michael",
        "Steve"
    };

    int test_element_count = 5;
    struct test_element *test_elements;
    test_elements = malloc(test_element_count * sizeof(*test_elements));
    for (int i = 0; i < test_element_count; i++)
        init_test_element(&test_elements[i], names[i], i);

    for (int i = 0; i < 4; i++) {
        push_stack(&my_stack, &test_elements[i]);
    }

    for (int i = 0; i < 3; i++) {
        pop_stack(&my_stack);
    }

    for (int i = 0; i < 13; i++) {
        push_stack(&my_stack, &test_elements[i]);
    }

    for (int i = 0; i < 9; i++) {
        pop_stack(&my_stack);
    }

    destroy_stack(&my_stack);

    return 0;
}
