#include <iostream>

using namespace std;

class Trie {
private:
	Trie* next[10];
	int end;

public:
	Trie() {
		int i;
		for (i = 0; i < 10; ++i) {
			next[i] = NULL;
		}
		end = 0;
	}

	void delete_trie() {
		int i;
		for (i = 0; i < 10; ++i) {
			if (next[i]) {
				next[i]->delete_trie();
			}
		}
		delete(this);
	}

	bool insert(const char* str) {
		if (!(*str)) {
			return (end = true);
		}

		if (!next[*str - '0']) {
			next[*str - '0'] = new Trie();
		}

		return next[*str - '0']->insert(str + 1);
	}

	bool find(const char* str) {
		if (!(*str)) {
			return true;
		}

		if (end) {
			return false;
		}

		return next[*str - '0']->find(str + 1);
	}
};

char str[10'000 + 5][10 + 5];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc;
	cin >> tc;
	while (tc--) {
		Trie* trie = new Trie();

		int n;
		cin >> n;

		int i;
		for (i = 0; i < n; ++i) {
			cin >> str[i];
			trie->insert(str[i]);
		}

		bool ans = true;
		for (i = 0; i < n; ++i) {
			ans &= trie->find(str[i]);
		}
		cout << (ans ? "YES\n" : "NO\n");

		trie->delete_trie();
	}
}
