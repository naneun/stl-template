#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0

#define VERTEX_COUNT 10000 + 5

/* VECTOR */

typedef struct _VECTOR VECTOR;

struct _VECTOR {
	int count;
	int capacity;
	int* ary;
};

VECTOR** grp;

VECTOR* alloc_vector() {
	VECTOR* vp = (VECTOR*)malloc(sizeof(VECTOR));
	vp->count = 0;
	vp->capacity = 32;
	vp->ary = (int*)malloc(sizeof(int) * vp->capacity);
	return vp;
}

void free_vector(VECTOR* v) {
	free(v->ary);
	v->ary = NULL;
}

void clear_vector(VECTOR* v) {
	free(v->ary);
	v->count = 0;
	v->capacity = 32;
	v->ary = (int*)malloc(sizeof(int) * v->capacity);
}

VECTOR** resize(int size) {
	VECTOR** vvp = (VECTOR**)malloc(sizeof(VECTOR*) * size);
	int i;
	for (i = 1; i < size; ++i) vvp[i] = alloc_vector();
	return vvp;
}

void clear_graph(VECTOR** vv) {
	int i;
	for (i = 1; i < VERTEX_COUNT; ++i) {
		clear_vector(vv[i]);
	}
}

void free_graph(VECTOR** vv, int size) {
	int i;
	for (i = 1; i < size; ++i) if (vv[i] != NULL) {
		free_vector(vv[i]);
		*(vv + i) = NULL;
	}
}

void push_back(VECTOR* v, int value) {
	if (v->count == v->capacity) {
		v->capacity <<= 1;
		v->ary = (int*)realloc(v->ary, sizeof(int) * v->capacity);
	}
	v->ary[v->count++] = value;
}

void pop_back(VECTOR* v) { v->count -= 1; }

int size(VECTOR* v) { return v->count; }

int vis[VERTEX_COUNT];

typedef int boolean;

boolean dfs(int cur) {
	vis[cur] = true;
	int i, v_siz = size(grp[cur]), next;
	for (i = 0; i < v_siz; ++i) {
		next = grp[cur]->ary[i];
		if (!vis[next]) {
			dfs(next);
		}
	}
	return true;
}

int main(void)
{	
	int i, n, m, a, b, res = 0;
	scanf("%d %d", &n, &m);

	grp = resize(n + 1);

	for (i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		push_back(grp[a], b);
		push_back(grp[b], a);
	}

	for (i = 1; i <= n; ++i) if (!vis[i]) {
		res += dfs(i);
	}

	printf("%d", res);

	free_graph(grp, n + 1);

	return 0;
}