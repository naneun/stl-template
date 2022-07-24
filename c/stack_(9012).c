#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (50 + 5)
#define STRING_LENGTH (50 + 5)

typedef struct _Stack Stack;

struct _Stack {
	int top;
	char* buffer;
};

/*
* Stack
*/
Stack* create_stack();
void delete_stack(Stack* stack);
int empty(Stack* stack);
int size(Stack* stack);
char top(Stack* stack);
void push(Stack* stack, char ch);
void pop(Stack* stack);

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

		delete_stack(stack);
	}
}

Stack* create_stack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = 0;
	stack->buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	return stack;
}

void delete_stack(Stack* stack) {
	free(stack);
	*(&stack) = NULL;
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
