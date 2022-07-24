#include <iostream>

using namespace std;

typedef unsigned long long ull;

const int HASH_TABLE_SIZE = 1'000'000 + 5;

class HashTable {
private:
	string value[HASH_TABLE_SIZE];

public:
	ull generate_hash_value(string str) {
		ull hash_value = 5381;
		for (int i = 0; str[i]; ++i) {
			hash_value = (((hash_value << 5) + hash_value) + str[i]) % HASH_TABLE_SIZE;
		}
		return hash_value;
	}

	void put(string str) {
		ull hash_value = generate_hash_value(str);
		int count = HASH_TABLE_SIZE;
		while (!value[hash_value].empty() && count--) {
			if (!value[hash_value].compare(str)) {
				return;
			}
			hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
		}
		value[hash_value] = str;
	}

	bool find(string str) {
		ull hash_value = generate_hash_value(str);
		int count = HASH_TABLE_SIZE;
		while (!value[hash_value].empty() && count--) {
			if (!value[hash_value].compare(str)) {
				return true;
			}
			hash_value = (hash_value + 1) % HASH_TABLE_SIZE;
		}
		return false;
	}
};

HashTable hash_table;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	string s;
	while (n--) {
		cin >> s;
		hash_table.put(s);
	}

	int ans = 0;
	while (m--) {
		cin >> s;
		ans += hash_table.find(s);
	}
	
	cout << ans;
}
