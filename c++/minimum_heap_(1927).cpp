#include <iostream>

using namespace std;

const int HEAP_SIZE = 100'000 + 5;

struct HEAP {

private:
	int count;
	int buffer[HEAP_SIZE];

public:
	bool empty() {
		return count == 0;
	}

	int top() {
		int ret = 0;
		if (!empty()) {
			return buffer[1];
		}
		return ret;
	}

	void push(int value) {
		int cur = ++count;
		while (cur != 1 && value < buffer[cur >> 1]) {
			buffer[cur] = buffer[cur >> 1];
			cur >>= 1;
		}
		buffer[cur] = value;
	}

	int pop() {
		int ret = 0;
		if (!empty()) {
			ret = buffer[1];
			int parent = 1, child = 2, last_pushed_value = buffer[count--];
			while (child <= count) {
				if (child < count && buffer[child] > buffer[child + 1]) {
					++child;
				}
				if (buffer[child] >= last_pushed_value) {
					break;
				}
				buffer[parent] = buffer[child];
				parent = child;
				child <<= 1;
			}
			buffer[parent] = last_pushed_value;
		}
		return ret;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	HEAP* heap = new HEAP();

	int n;
	cin >> n;
	while (n--) {
		int x;
		cin >> x;
		if (!x) {
			cout << heap->pop() << '\n';
		}
		else {
			heap->push(x);
		}
	}
}
