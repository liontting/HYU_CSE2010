#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
	char *key;
	int top;
	int max_stack_size;
};

void init(Stack *s) {
	s->top = -1;
	s->max_stack_size = 100;
	s->key = (char *)malloc(sizeof(char) * s->max_stack_size);
}

int is_empty(Stack *s) {
	return (s->top == -1);
}

int is_full(Stack *s) {
	return (s->top == (s->max_stack_size - 1));
}

void push(Stack *s, int item) {
	if (is_full(s)) {
		fprintf(stderr, " \n");
		return;
	}
	else
		s->key[++(s->top)] = item;
}

int pop(Stack *s) {
	if (is_empty(s)) {
		fprintf(stderr, "empty\n");
		exit(1);
	}
	else
		return s->key[(s->top)--];
}

int peek(Stack *s) {
	if (is_empty(s)) {
		fprintf(stderr, "empty\n"); exit(1);
	}
	else
		return s->key[s->top];
}
int postfix_to_infix(const char exp[]) {
	char ch;
	int len = strlen(exp), tmp1, tmp2, result;
	Stack s;
	init(&s);
	for (int i = 0; i < len; i++) {
		ch = exp[i];
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
			tmp2 = pop(&s);
			tmp1 = pop(&s);
			if (ch == '+')
				result = tmp1 + tmp2;
			else if (ch == '-')
				result = tmp1 - tmp2;
			else if (ch == '*')
				result = tmp1 * tmp2;
			else if (ch == '/')
				result = tmp1 / tmp2;
			else if (ch == '%')
				result = tmp1 % tmp2;
			push(&s, result);
		}
		else if (ch == '#')
			return pop(&s);
		else
			push(&s, ch - '0');
	}
	return pop(&s);
}

int main(int argc, char **argv) {
	FILE *f1;
	f1 = fopen(argv[1], "r");
	char tmp[100], t[100];
	fscanf(f1, " %s", tmp);
	for (int i = 0; tmp[i] != '#'; i++)
		t[i] = tmp[i];
	printf("converted postfix form : %s\n", t);
	printf("evaluation result : %d", postfix_to_infix(tmp));
	return 0;
}