#include <stdio.h>
#include <malloc.h>

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

boolean find(const char* str) {
	ull hash_value = get_hash_value(str);
	int c = TABLE_SIZE;
	while (hb[hash_value].key[0] != 0 && c--) {
		if (!strcmp(hb[hash_value].key, str)) return true;
		hash_value = (hash_value + 1) % TABLE_SIZE;
	}
	return false;
}

boolean insert(const char* str) {
	ull hash_value = get_hash_value(str);
	int c = TABLE_SIZE;
	while (hb[hash_value].key[0] != 0 && c--) {
		if (!strcmp(hb[hash_value].key, str)) return false;
		hash_value = (hash_value + 1) % TABLE_SIZE;
	}
	strcpy(hb[hash_value].key, str);
	return true;
}

int main(void)
{
	int n, m, res = 0;
	scanf("%d %d", &n, &m);

	char str[STRING_LENGTH];

	int i;
	for (i = 0; i < n; ++i) {
		scanf("%s", str);
		insert(str);
	}
	
	for (i = 0; i < m; ++i) {
		scanf("%s", str);
		if (find(str)) {
			++res;
		}
	}

	printf("%d", res);

	return 0;
}
