#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

Stack* stack_create(void);
void stack_push(Stack* s, char item);
char stack_pop(Stack* s);
char stack_peek(Stack* s);
int stack_is_empty(Stack* s);
void stack_destroy(Stack* s);
void stack_print(Stack* s);

#endif
