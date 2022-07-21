#include <stdio.h>

#define HEAP_SIZE 100000 + 5

typedef struct _HEAP HEAP;

struct _HEAP {
	int count;
	int ary[HEAP_SIZE];
};

HEAP hp;

void init() { hp.count = 0; }

int size() { return hp.count; }

typedef int boolean;

boolean empty() { return hp.count == 0; }

int top() {
	int ret = 0;
	if (!empty()) ret = hp.ary[1];
	return ret;
}

void push(int value) {
	int cur = ++hp.count;
	while (cur != 1 && value < hp.ary[cur >> 1]) {
		hp.ary[cur] = hp.ary[cur >> 1];
		cur >>= 1;
	}
	hp.ary[cur] = value;
}

int pop() {
	int ret = 0;
	if (!empty()) {
		ret = hp.ary[1];
		int parent = 1, child = 2, last_data = hp.ary[hp.count--];
		while (child <= hp.count) {
			if (child < hp.count && hp.ary[child] > hp.ary[child + 1]) child += 1;
			if (hp.ary[child] >= last_data) break;
			hp.ary[parent] = hp.ary[child];
			parent = child;
			child <<= 1;
		}
		hp.ary[parent] = last_data;
	}
	return ret;
}

int main(void)
{
	int n, x;
	scanf("%d", &n);

	while (n--) {
		scanf("%d", &x);
		if (x) push(x);
		else printf("%d\n", pop());
	}

	return 0;
}
