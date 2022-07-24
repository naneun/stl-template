#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 1'000'000 + 5;

int n, arr[MAX_N];

void quick_sort(int start, int end) {
	if (start >= end) {
		return;
	}

	int left = start;
	int right = end;

	while (left <= right) {
		while (arr[left] <= arr[start]) {
			++left;
		}
		while (arr[right] > arr[start]) {
			--right;
		}
		swap(arr[left], arr[right]);
	}

	swap(arr[left], arr[right]);
	swap(arr[start], arr[right]);

	quick_sort(start, right - 1);
	quick_sort(right + 1, end);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	
	int i;
	for (i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	random_shuffle(arr, arr + n);

	quick_sort(0, n - 1);

	for (i = 0; i < n; ++i) {
		cout << arr[i] << '\n';
	}
}
