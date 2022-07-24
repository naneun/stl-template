#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (500000 + 5)

typedef struct _Queue Queue;

struct _Queue {
	int front;
	int back;
	int* buffer;
};

/*
* Queue
*/
Queue* create_queue();
void delete_queue(Queue** queue);
int empty(Queue* queue);
int full(Queue* queue);
int size(Queue* queue);
int front(Queue* queue);
void push(Queue* queue, int value);
void pop(Queue* queue);

int main()
{
	int n;
	scanf("%d", &n);

	Queue* queue = create_queue();

	int i;
	for (i = 1; i <= n; ++i) {
		push(queue, i);
	}

	while (size(queue) > 1) {
		pop(queue);
		push(queue, front(queue));
		pop(queue);
	}

	printf("%d", front(queue));

	delete_queue(&queue);
}

Queue* create_queue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->front = queue->back = 0;
	queue->buffer = (int*)malloc(sizeof(int) * BUFFER_SIZE);
	return queue;
}

void delete_queue(Queue** queue) {
	free((*queue)->buffer);
	free(*queue);
	*queue = NULL;
}

int empty(Queue* queue) {
	return queue->front == queue->back;
}

int full(Queue* queue) {
	return (queue->back + 1) % BUFFER_SIZE == queue->front;
}

int size(Queue* queue) {
	return (queue->back + BUFFER_SIZE - queue->front) % BUFFER_SIZE;
}

int front(Queue* queue) {
	return queue->buffer[queue->front];
}

void push(Queue* queue, int value) {
	if (full(queue)) {
		return;
	}
	queue->buffer[(queue->back)++] = value;
	queue->back %= BUFFER_SIZE;
}

void pop(Queue* queue) {
	if (empty(queue)) {
		return;
	}
	queue->front = (queue->front + 1) % BUFFER_SIZE;
}
