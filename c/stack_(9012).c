#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE		(50 + 5)
#define STRING_LENGTH	(50 + 5)

int strlen(const char* str) {
	int i;
	for (i = 0; str[i]; ++i);
	return i;
}

int strcmp(const char* s1, const char* s2) {
	int i;
	for (i = 0; s1[i] || s2[i]; ++i) {
		if (s1[i] != s2[i]) {
			return s1[i] < s2[i] ? -1 : 1;
		}
	}
	return 0;
}

void strcpy(char* s1, const char* s2) {
	int i;
	for (i = 0; s2[i]; ++i) {
		s1[i] = s2[i];
	}
	s1[i] = 0;
}

struct _Stack {

	int top;
	char* buffer;
};

typedef struct _Stack Stack;

Stack* create_stack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = 0;
	stack->buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	return stack;
}

void free_stack(Stack* stack) {
	free(stack);
	stack = NULL;
}

int empty(Stack* stack) {
	return !stack->top;
}

int size(Stack* stack) {
	return stack->top;
}

char top(Stack* stack) {
	return stack->buffer[stack->top - 1];
}

void push(Stack* stack, char ch) {
	stack->buffer[(stack->top)++] = ch;
}

void pop(Stack* stack) {
	--(stack->top);
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		Stack* stack = create_stack();
		char str[STRING_LENGTH];
		scanf("%s", str);
		int i, length = strlen(str);
		for (i = 0; i < length; ++i) {
			push(stack, str[i]);
			if (size(stack) > 1 
				&& stack->buffer[stack->top - 2] == '(' 
				&& stack->buffer[stack->top - 1] == ')') {

				pop(stack);
				pop(stack);
			}
		}
		printf("%s\n", empty(stack) ? "YES" : "NO");

		free_stack(stack);
	}
}
