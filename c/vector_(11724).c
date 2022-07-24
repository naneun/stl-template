#include <stdio.h>
#include <stdlib.h>

#define TRUE 1

#define NODE_COUNT (10000 + 5)

typedef struct _Vector Vector;
typedef struct _Graph Graph;

struct _Vector {
	int size;
	int capacity;
	int* buffer;
};

struct _Graph {
	Vector** nodes;
};

int visited[NODE_COUNT];

/*
* Vector
*/
Vector* create_vector();
void resize_vector(Vector* vector);
void delete_vector(Vector** vector);
int empty(Vector* vector);
int full(Vector* vector);
int size(Vector* vector);
void emplace_back(Vector* vector, int value);
void pop_back(Vector* vector);

/*
* Graph
*/
Graph* create_graph();
void delete_graph(Graph** graph);

/*
* DFS
*/
void dfs(Graph* graph, int cur);

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	Graph* graph = create_graph();

	int i;
	for (i = 0; i < m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		emplace_back(graph->nodes[u], v);
		emplace_back(graph->nodes[v], u);
	}

	int ans = 0;
	for (i = 1; i <= n; ++i) {
		ans += !visited[i];
		dfs(graph, i);
	}

	printf("%d", ans);

	delete_graph(&graph);
}

Vector* create_vector() {
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	vector->size = 0;
	vector->capacity = 1 << 4;
	vector->buffer = (int*)malloc(sizeof(int) * vector->capacity);
	return vector;
}

void resize_vector(Vector* vector) {
	vector->capacity <<= 1;
	vector->buffer = (int*)realloc(vector->buffer, sizeof(int) * vector->capacity);
}

void delete_vector(Vector** vector) {
	free((*vector)->buffer);
	free(*vector);
	*vector = NULL;
}

int size(Vector* vector) {
	return vector->size;
}

int empty(Vector* vector) {
	return !vector->size;
}

int full(Vector* vector) {
	return vector->size == vector->capacity;
}

void emplace_back(Vector* vector, int value) {
	if (full(vector)) {
		resize_vector(vector);
	}
	vector->buffer[(vector->size)++] = value;
}

void pop_back(Vector* vector) {
	if (empty(vector)) {
		return;
	}
	--(vector->size);
}

Graph* create_graph() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->nodes = (Vector**)malloc(sizeof(Vector) * NODE_COUNT);
	int i;
	for (i = 0; i < NODE_COUNT; ++i) {
		*(graph->nodes + i) = create_vector();
	}
	return graph;
}

void delete_graph(Graph** graph) {
	int i;
	for (i = 0; i < NODE_COUNT; ++i) {
		delete_vector((*graph)->nodes + i);
	}
	free(*graph);
	*graph = NULL;
}

void dfs(Graph* graph, int cur) {
	visited[cur] = TRUE;
	Vector* node = graph->nodes[cur];
	int adj_count = node->size;
	int i;
	for (i = 0; i < adj_count; ++i) {
		int next = node->buffer[i];
		if (!visited[next]) {
			dfs(graph, next);
		}
	}
}
