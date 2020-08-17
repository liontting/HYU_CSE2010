#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 20
typedef int element;

typedef struct {
	char stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init(StackType *s) {
	s->top = -1;
}

int is_empty(StackType *s) {
	return (s->top == -1);
}

int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) {
	if (is_full(s)) {
		fprintf(stderr, " \n");
		return;
	}
	else
		s->stack[++(s->top)] = item;
}

element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "empty\n");
		exit(1);
	}
	else
		return s->stack[(s->top)--];
}

element peek(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "empty\n"); exit(1);
	}
	else
		return s->stack[s->top];
}

int prec(char op) {
	switch (op) {
	case '(':
	case ')':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	return -1;
}
void infix_to_postfix(const char exp[]) {
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	init(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
				printf("%c", pop(&s));
			}
			push(&s, ch);
		}
		else if (ch == '(')
			push(&s, ch);
		else if (ch == ')') {
			top_op = pop(&s);
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
		}
		else
			printf("%c", ch);
	}
	while (!is_empty(&s))
		printf("%c", pop(&s));
}

int main() {
	infix_to_postfix("(2+3)*4+9");
	return 0;
}