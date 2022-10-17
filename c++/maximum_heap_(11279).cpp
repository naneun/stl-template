#include <iostream>

using namespace std;

const int MAX_HEAP_SIZE = 100'000 + 5;

int heap[MAX_HEAP_SIZE];

int heap_size;

void push(int x) {
    heap[++heap_size] = x;
    int cur = heap_size;
    while (cur != 1 && heap[cur / 2] < heap[cur]) {
        swap(heap[cur / 2], heap[cur]);
        cur /= 2;
    }
}

int pop() {
    if (heap_size == 0) {
        return 0;
    }

    int ret = heap[1];
    heap[1] = heap[heap_size--];

    int cur = 1;
    while (cur * 2 <= heap_size) {
        int next = cur * 2;
        if (next < heap_size
            && heap[next + 1] > heap[next]) {

            next += 1;
        }

        if (heap[cur] >= heap[next]) {
            break;
        }

        swap(heap[cur], heap[next]);
        cur = next;
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int i, x;
    for (i = 0; i < n; ++i) {
        cin >> x;
        if (x > 0) {
            push(x);
        }
        else {
            cout << pop() << '\n';
        }
    }
}
