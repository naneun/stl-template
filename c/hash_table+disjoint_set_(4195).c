#include <stdio.h>
#include <malloc.h>

#define swap(a, b) { int t = (a); (a) = (b); (b) = t; }

#define TABLE_SIZE 100000 + 5
#define STRING_LENGTH 500 + 5

#define true 1
#define false 0

/* string function */

int strcmp(const char* s1, const char* s2) {
	int i;
	for (i = 0; s1[i] || s2[i]; ++i) if (s1[i] != s2[i]) {
		return s1[i] < s2[i] ? -1 : 1;
	}
	return 0;
}

void strcpy(char* des, const char* src) {
	int i;
	for (i = 0; src[i]; ++i) des[i] = src[i];
	des[i] = '\0';
}

/* hash table */

typedef struct _HASH_TABLE HASH_TABLE;

struct _HASH_TABLE {
	char key[STRING_LENGTH];
	int group_id;
};

HASH_TABLE hb[TABLE_SIZE];

typedef unsigned long long ull;

ull get_hash_value(const char* str) {
	ull hash = 5381;
	int i;
	for (i = 0; str[i]; ++i) {
		hash = (((hash << 5) + hash) + str[i]) % TABLE_SIZE;
	}
	return hash % TABLE_SIZE;
}

typedef int boolean;

boolean get_data(const char* str) {
	ull hash_value = get_hash_value(str);
	int c = TABLE_SIZE;
	while (hb[hash_value].key[0] != 0 && c--) {
		if (!strcmp(hb[hash_value].key, str)) return hb[hash_value].group_id;
		hash_value = (hash_value + 1) % TABLE_SIZE;
	}
	return false;
}

boolean insert(const char* str, int id) {
	ull hash_value = get_hash_value(str);
	int c = TABLE_SIZE;
	while (hb[hash_value].key[0] != 0 && c--) {
		if (!strcmp(hb[hash_value].key, str)) return false;
		hash_value = (hash_value + 1) % TABLE_SIZE;
	}
	strcpy(hb[hash_value].key, str);
	hb[hash_value].group_id = id;
	return true;
}

/* union find */

int parent[TABLE_SIZE], size[TABLE_SIZE], id;

void init() {
	int i;
	for (i = 1; i < TABLE_SIZE; ++i) {
		parent[i] = i;
		size[i] = 1;
	}
	id = 1;
}

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void merge(int x, int y) {
	parent[y] = x;
	size[x] += size[y];
}

int main(void)
{
	int i, j, k, tc, test_case, n;

	char s1[STRING_LENGTH], s2[STRING_LENGTH];

	scanf("%d", &tc);

	for (test_case = 0; test_case < tc; ++test_case) {
		scanf("%d", &n);

		init();

		for (i = 0; i < n; ++i) {
			scanf("%s %s", s1, s2);
			if (!get_data(s1)) insert(s1, id++);
			if (!get_data(s2)) insert(s2, id++);

			j = get_data(s1);
			k = get_data(s2);

			j = find(j), k = find(k);

			if (j > k) swap(j, k);

			if (j != k) merge(j, k);
			
			printf("%d\n", size[j]);
		}
	}

	return 0;
}