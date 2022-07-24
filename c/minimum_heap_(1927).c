#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE (100000 + 5)

typedef struct _Heap Heap;

struct _Heap {
	int count;
	int* buffer;
};

/*
* Minimum-Heap
*/
Heap* create_heap();
void delete_heap(Heap** heap);
int empty(Heap* heap);
int top(Heap* heap);
void push(Heap* heap, int value);
int pop(Heap* heap);

int main()
{
	Heap* heap = create_heap();

	int n;
	scanf("%d", &n);
	while (n--) {
		int x;
		scanf("%d", &x);
		
		if (!x) {
			printf("%d\n", pop(heap));
		}
		else {
			push(heap, x);
		}
	}

	delete_heap(&heap);
}

Heap* create_heap() {
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->count = 0;
	heap->buffer = (int*)malloc(sizeof(int) * HEAP_SIZE);
	return heap;
}

void delete_heap(Heap** heap) {
	free((*heap)->buffer);
	free(*heap);
	*heap = NULL;
}

int empty(Heap* heap) {
	return heap->count == 0;
}

int top(Heap* heap) {
	int ret = 0;
	if (!empty(heap)) {
		return heap->buffer[1];
	}
	return ret;
}

void push(Heap* heap, int value) {
	int cur = ++(heap->count);
	while (cur != 1 && value < heap->buffer[cur >> 1]) {
		heap->buffer[cur] = heap->buffer[cur >> 1];
		cur >>= 1;
	}
	heap->buffer[cur] = value;
}

int pop(Heap* heap) {
	int ret = 0;
	if (!empty(heap)) {
		ret = heap->buffer[1];
		int parent = 1, child = 2, last_pushed_value = heap->buffer[(heap->count)--];
		while (child <= heap->count) {
			if (child < heap->count && heap->buffer[child] > heap->buffer[child + 1]) {
				++child;
			}
			if (heap->buffer[child] >= last_pushed_value) {
				break;
			}
			heap->buffer[parent] = heap->buffer[child];
			parent = child;
			child <<= 1;
		}
		heap->buffer[parent] = last_pushed_value;
	}
	return ret;
}
