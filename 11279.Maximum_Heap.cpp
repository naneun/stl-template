#include <stdio.h>
#include <malloc.h>

#define MAX_SIZ 100000 + 5

typedef struct _Heap Heap;

struct _Heap {
	int count;
	int ary[MAX_SIZ];
};

Heap hp;

typedef int boolean;

void init() { hp.count = 0; }

boolean empty() { return hp.count == 0; }

int size() { return hp.count; }

int top() {
	int ret = 0;
	if (!empty()) ret = hp.ary[1];
	return ret;
}

void push(int data) {
	int cur = ++hp.count;
	while (cur != 1 && data > hp.ary[cur >> 1]) {
		hp.ary[cur] = hp.ary[cur >> 1];
		cur >>= 1;
	}
	hp.ary[cur] = data;
}

int pop() {
	int ret = 0;
	if (!empty()) {
		ret = hp.ary[1];
		int parent = 1, child = 2, last_data = hp.ary[hp.count--];
		while (child <= hp.count) {
			if (child < hp.count && hp.ary[child] < hp.ary[child + 1]) child += 1;
			if (last_data >= hp.ary[child]) break;
			hp.ary[parent] = hp.ary[child];
			parent = child;
			child <<= 1;
		}
		hp.ary[parent] = last_data;
		return ret;
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