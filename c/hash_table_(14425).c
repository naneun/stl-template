#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define HASH_TABLE_SIZE (1000000 + 5)
#define STRING_LENGTH (500 + 5)

typedef unsigned long long ull;

int strcmp(const char* s1, const char* s2);
void strcpy(char* s1, const char* s2);

typedef struct _HashTable HashTable;

struct _HashTable {

	char* value[HASH_TABLE_SIZE];
};

HashTable hash_table;

void init_hash_table();

ull generate_hash_value(const char* str);

void put(const char* str);

int find(const char* str);

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	init_hash_table();

	char s[STRING_LENGTH];
	while (n--) {
		scanf("%s", s);
		put(s);
	}

	int ans = 0;
	while (m--) {
		scanf("%s", s);
		ans += find(s);
	}
	printf("%d", ans);
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
	int i;
	for (i = 0; i < HASH_TABLE_SIZE; ++i) {
		hash_table.value[i] = (char*)malloc(sizeof(char) * STRING_LENGTH);
		hash_table.value[i][0] = 0;
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

void put(const char* str) {
	ull hash_value = generate_hash_value(str);
	int count = HASH_TABLE_SIZE;
	while (hash_table.value[hash_value][0] && count--) {
		if (!strcmp(hash_table.value[hash_value], str)) {
			return;
		}
		hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
	}
	strcpy(hash_table.value[hash_value], str);
}

int find(const char* str) {
	ull hash_value = generate_hash_value(str);
	int count = HASH_TABLE_SIZE;
	while (hash_table.value[hash_value][0] && count--) {
		if (!strcmp(hash_table.value[hash_value], str)) {
			return TRUE;
		}
		hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
	}
	return FALSE;
}
