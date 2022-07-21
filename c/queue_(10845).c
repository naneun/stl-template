#include <stdio.h>

#define MAX_SIZ (10000)
#define STR_SIZ (10 + 5)

int n, x, que[MAX_SIZ], front, rear;

/* String variable */

const char push_str[] = "push";
const char pop_str[] = "pop";
const char size_str[] = "size";
const char empty_str[] = "empty";
const char front_str[] = "front";
const char back_str[] = "back";

char str[STR_SIZ];

/* Function */

int strcmp(const char* s1, const char* s2) {
	int i;
	for (i = 0; s1[i] == s2[i]; ++i) if (s1[i] == '\0') return 0;
	return 1;
}

int empty() { return front == rear; }

void push(int value) {
	if ((rear + 1) % MAX_SIZ == front) return;
	que[rear] = value;
	rear = (rear + 1) % MAX_SIZ;
}

int pop() {
	int ret = -1;
	if (!empty()) {
		ret = que[front];
		front = (front + 1) % MAX_SIZ;
	}
	return ret;
}

int front_() {
	int ret = -1;
	if (!empty()) ret = que[front];
	return ret;
}

int back() {
	int ret = -1;
	if (!empty()) ret = que[rear - 1 < 0 ? MAX_SIZ - 1 : rear - 1];
	return ret;
}

int size() {
	int ret = rear - front;
	if (front > rear) ret += MAX_SIZ;
	return ret;
}

int main(void)
{
	scanf("%d", &n);

	while (n--) {
		scanf("%s", str);
		if (!strcmp(str, push_str)) scanf("%d", &x), push(x);
		else if (!strcmp(str, pop_str)) printf("%d\n", pop());
		else if (!strcmp(str, size_str)) printf("%d\n", size());
		else if (!strcmp(str, empty_str)) printf("%d\n", empty());
		else if (!strcmp(str, front_str)) printf("%d\n", front_());
		else printf("%d\n", back());
	}

	return 0;
}
