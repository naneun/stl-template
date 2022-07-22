#include <iostream>

using namespace std;

typedef unsigned long long ull;

const int HASH_TABLE_SIZE = 1000'000 + 5;

struct Element {

public:

	string value;
	int index;

	Element() {
		value = "";
		index = 0;
	}

	Element(string value, int index) : value(value), index(index) {}

	bool operator == (const Element& obj) const {
		return value == obj.value && index == obj.index;
	}
};

Element NULL_ELEMENT;

struct HashTable {

private:

	Element element[HASH_TABLE_SIZE];

public:

	HashTable() {

	}

	ull generate_hash_value(string str) {
		ull hash_value = 5381;
		for (int i = 0; str[i]; ++i) {
			hash_value = (((hash_value << 5) + hash_value) + str[i]) % HASH_TABLE_SIZE;
		}
		return hash_value;
	}

	void put(string str, int parent) {
		ull hash_value = generate_hash_value(str);
		int count = HASH_TABLE_SIZE;
		while (!element[hash_value].value.empty() && count--) {
			if (!element[hash_value].value.compare(str)) {
				return;
			}
			hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
		}
		element[hash_value] = Element(str, parent);
	}

	Element find(string str) {
		ull hash_value = generate_hash_value(str);
		int count = HASH_TABLE_SIZE;
		while (!element[hash_value].value.empty() && count--) {
			if (!element[hash_value].value.compare(str)) {
				return element[hash_value];
			}
			hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
		}
		return NULL_ELEMENT;
	}
};

HashTable hash_table;

int seq, parent[HASH_TABLE_SIZE];

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
	if (x > y) {
		swap(x, y);
	}
	parent[x] += parent[y];
	parent[y] = x;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		init_set();
		while (n--) {
			string s, t;
			cin >> s >> t;
			if (hash_table.find(s) == NULL_ELEMENT) {
				hash_table.put(s, ++seq);
			}
			if (hash_table.find(t) == NULL_ELEMENT) {
				hash_table.put(t, ++seq);
			}

			Element e1 = hash_table.find(s);
			Element e2 = hash_table.find(t);

			int u = find_root(e1.index);
			int v = find_root(e2.index);

			if (u > v) {
				swap(u, v);
			}

			if (u != v) {
				merge(u, v);
			}

			cout << -parent[u] << '\n';
		}
	}
}
