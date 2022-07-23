#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _Trie Trie;

struct _Trie {

	Trie* next[10];

	int end;
};

Trie* create_trie();
void delete_trie(Trie* trie);

int insert(Trie* trie, const char* str);

int find(Trie* trie, const char* str);

char str[10000 + 5][10 + 5];

int main()
{
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		Trie* trie = create_trie();

		int n;
		scanf("%d", &n);

		int i;
		for (i = 0; i < n; ++i) {
			scanf("%s", str[i]);
			insert(trie, str[i]);
		}

		int ans = TRUE;
		for (i = 0; i < n; ++i) {
			ans &= find(trie, str[i]);
		}
		printf("%s\n", ans ? "YES" : "NO");

		delete_trie(trie);
	}
}

Trie* create_trie() {
	Trie* trie = (Trie*)malloc(sizeof(Trie));
	memset(trie, 0, sizeof(Trie));
	return trie;
}

void delete_trie(Trie* trie) {
	int i;
	for (i = 0; i < 10; ++i) {
		if (trie->next[i]) {
			delete_trie(trie->next[i]);
		}
	}
	free(trie);
	*(&trie) = NULL;
}

int insert(Trie* trie, const char* str) {
	if (!(*str)) {
		return trie->end = TRUE;
	}

	Trie** next = &trie->next[*str - '0'];
	if (!(*next)) {
		*next = create_trie();
	}

	return insert(*next, str + 1);
}

int find(Trie* trie, const char* str) {
	if (!(*str)) {
		return TRUE;
	}

	if (trie->end) {
		return FALSE;
	}

	return find(trie->next[*str - '0'], str + 1);
}