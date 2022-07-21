#include <stdio.h>

#define MAX_SIZ (10000)
#define STR_SIZ (10 + 5)

int n, x, stk[MAX_SIZ], top;

/* String variable */

const char push_str[] = "push";
const char pop_str[] = "pop";
const char size_str[] = "size";
const char empty_str[] = "empty";
const char top_str[] = "top";

char str[STR_SIZ];

/* Function */

int strcmp(const char* s1, const char* s2) {
	int i;
	for (i = 0; s1[i] == s2[i]; ++i) if (s1[i] == '\0') return 0;
	return 1;
}

int empty() { return top == 0; }

void push(int value) {
	stk[top] = value;
	top += 1;
}

int pop() { 
	int ret = -1;
	if (!empty()) {
		top -= 1;
		ret = stk[top];
	}
	return ret;
}

int top_() {
	int ret = -1;
	if (!empty()) ret = stk[top - 1];
	return ret;
}

int main(void)
{
	scanf("%d", &n);

	while (n--) {
		scanf("%s", str);
		if (!strcmp(str, push_str)) scanf("%d", &x), push(x);
		else if (!strcmp(str, pop_str)) printf("%d\n", pop());
		else if (!strcmp(str, size_str)) printf("%d\n", top);
		else if (!strcmp(str, empty_str)) printf("%d\n", empty());
		else printf("%d\n", top_());
	}

	return 0;
}
