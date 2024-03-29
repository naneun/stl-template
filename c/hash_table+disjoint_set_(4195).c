#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) { int t = (a); (a) = (b); (b) = t; }

#define TRUE 1
#define FALSE 0

#define HASH_TABLE_SIZE	(1000000 + 5)
#define STRING_LENGTH (20 + 5)

typedef unsigned long long ull;
typedef struct _Element Element;
typedef struct _HashTable HashTable;

struct _Element {
	int index;
	char* value;
};

struct _HashTable {
	Element* element;
};

HashTable hash_table;

int seq, parent[HASH_TABLE_SIZE];

/*
* String Utils
*/
int strcmp(const char* s1, const char* s2);
void strcpy(char* s1, const char* s2);

/*
* HashTable
*/
void init_hash_table();
ull generate_hash_value(const char* str);
void put(const char* str, int seq);
void put_element(const ull hash_value, const char* str, const int seq);
Element find(const char* str);

/*
* Disjoint-Set
*/
void init_set();
int find_root(int x);
void merge(int x, int y);

int main()
{
	init_hash_table();

	int tc;
	scanf("%d", &tc);
	while (tc--) {
		int n;
		scanf("%d", &n);

		init_set();
		
		while (n--) {
			char s[STRING_LENGTH], t[STRING_LENGTH];
			scanf("%s %s", s, t);
			
			if (find(s).value == NULL) {
				put(s, ++seq);
			}
			if (find(t).value == NULL) {
				put(t, ++seq);
			}

			Element e1 = find(s);
			Element e2 = find(t);

			int u = find_root(e1.index);
			int v = find_root(e2.index);

			if (u < v) {
				swap(u, v);
			}

			if (u != v) {
				merge(u, v);
			}

			printf("%d\n", -parent[u]);
		}
	}
}

int strcmp(const char* s1, const char* s2) {
	int i;
	for (i = 0; s1[i] || s2[i]; ++i) {
		if (s1[i] != s2[i]) {
			return s1[i] < s2[i] ? -1 : 1;
		}
	}
	return 0;
}

void strcpy(char* s1, const char* s2) {
	int i;
	for (i = 0; s2[i]; ++i) {
		s1[i] = s2[i];
	}
	s1[i] = 0;
}

void init_hash_table() {
	hash_table.element = (Element*)malloc(sizeof(Element) * (HASH_TABLE_SIZE + 1));
	hash_table.element[HASH_TABLE_SIZE].value = NULL;
	hash_table.element[HASH_TABLE_SIZE].index = -1;

	int i;
	for (i = 0; i < HASH_TABLE_SIZE; ++i) {
		hash_table.element[i].value = (char*)malloc(sizeof(char) * STRING_LENGTH);
		hash_table.element[i].value[0] = 0;
	}
}

ull generate_hash_value(const char* str) {
	ull hash_value = 5381;
	int i;
	for (i = 0; str[i]; ++i) {
		hash_value = (((hash_value << 5) + hash_value) + str[i]) % HASH_TABLE_SIZE;
	}
	return hash_value;
}

void put(const char* str, int seq) {
	ull hash_value = generate_hash_value(str);
	int count = HASH_TABLE_SIZE;
	while (hash_table.element[hash_value].value[0] && count--) {
		if (!strcmp(hash_table.element[hash_value].value, str)) {
			return;
		}
		hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
	}
	put_element(hash_value, str, seq);
}

void put_element(const ull hash_value, const char* str, const int seq) {
	strcpy(hash_table.element[hash_value].value, str);
	hash_table.element[hash_value].index = seq;
}

Element find(const char* str) {
	ull hash_value = generate_hash_value(str);
	int count = HASH_TABLE_SIZE;
	while (hash_table.element[hash_value].value[0] && count--) {
		if (!strcmp(hash_table.element[hash_value].value, str)) {
			return hash_table.element[hash_value];
		}
		hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
	}
	return hash_table.element[HASH_TABLE_SIZE];
}

void init_set() {
	seq = 0;
	int i;
	for (i = 1; i < HASH_TABLE_SIZE; ++i) {
		parent[i] = -1;
	}
}

int find_root(int x) {
	if (parent[x] < 0) {
		return x;
	}
	return parent[x] = find_root(parent[x]);
}

void merge(int x, int y) {
	if (x < y) {
		swap(x, y);
	}
	parent[x] += parent[y];
	parent[y] = x;
}
