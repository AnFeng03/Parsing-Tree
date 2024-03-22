#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

struct Stack {
    char* items;
    int top;
    int capacity;
};

Stack* stack_create(void) {
    Stack* s = malloc(sizeof(Stack));
    s->capacity = 10; // initial capacity
    s->items = malloc(s->capacity * sizeof(char));
    s->top = -1;
    return s;
}

void stack_push(Stack* s, char item) {
    if (s->top == s->capacity - 1) {
        s->capacity *= 2;
        s->items = realloc(s->items, s->capacity * sizeof(char));
    }
    s->items[++s->top] = item;
}

char stack_pop(Stack* s) {
    if (stack_is_empty(s)) return '\0'; // return null char if stack is empty
    return s->items[s->top--];
}

char stack_peek(Stack* s) {
    if (stack_is_empty(s)) return '\0';
    return s->items[s->top];
}

int stack_is_empty(Stack* s) {
    return s->top == -1;
}

void stack_destroy(Stack* s) {
    free(s->items);
    free(s);
}

void stack_print(Stack* s) {
    if (stack_is_empty(s)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack: [");
    for (int i = s->top; i >= 0; i--) {
        printf("%c", s->items[i]);
        if (i > 0) {
            printf(", ");
        }
    }
    printf("]\n");
}

