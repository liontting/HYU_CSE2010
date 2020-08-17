#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

void init(StackType *s)
{
	s->top = -1;
}

int is_empty(StackType *s)
{
	return s->top == -1;
}

int is_full(StackType *s)
{
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "stack full\n");
		return;
	}
	else {
		s->stack[++(s->top)] = item;
	}
}

element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "stack empty\n");
		exit(1);
	}
	else {
		return s->stack[(s->top)--];
	}
}

element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "stack empty\n");
		exit(1);
	}
	else {
		return s->stack[s->top];
	}
}
int main() {
	StackType s;
	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", peek(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", is_empty(&s));
	return 0;
}