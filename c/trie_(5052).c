#include <stdio.h>
#include <malloc.h>

#define N 10000 + 5

#define true 1
#define false 0

char str[N][11];

typedef struct _Trie Trie;

struct _Trie {
	int finish;
	Trie* next[10];
};

Trie* trie() {
	Trie* tp = (Trie*)malloc(sizeof(Trie));
	int i;
	for (i = 0; i < 10; ++i) tp->next[i] = NULL;
	tp->finish = false;
	return tp;
}

void _trie(Trie* t) {
	int i;
	for (i = 0; i < 10; ++i) if (t->next[i]) {
		_trie(t->next[i]);
		free(t->next[i]);
	}
}

void insert(Trie* t, const char* key) {
	if (*key == '\0') {
		t->finish = true;
		return;
	}
	int cur = *key - '0';
	if (t->next[cur] == NULL) t->next[cur] = trie();
	insert(t->next[cur], key + 1);
}

int find(Trie* t, const char* key) {
	if (*key == '\0') return 0;
	if (t->finish) return 1;
	int cur = *key - '0';
	return find(t->next[cur], key + 1);
}

int main(void)
{
	int tc, test_case, i, n, flg;
	scanf("%d", &tc);

	for (test_case = 0; test_case < tc; ++test_case) {
		Trie* tri = trie();

		scanf("%d", &n);

		for (i = 0; i < n; ++i) {
			scanf("%s", str[i]);
			insert(tri, str[i]);
		}

		flg = 0;

		for (i = 0; i < n; ++i) {
			if (find(tri, str[i])) {
				flg = true;
			}
		}

		puts(!flg ? "YES" : "NO");

		_trie(tri);
	}

	return 0;
}