#include <iostream>

using namespace std;

const int MAX_N = 1'000'000 + 5;

int n, arr[MAX_N], brr[MAX_N];

void merge(int start, int mid, int end) {
	int left = start;
	int right = mid + 1;
	int cur = start;

	while (left <= mid && right <= end) {
		if (arr[left] <= arr[right]) {
			brr[cur++] = arr[left++];
		}
		else {
			brr[cur++] = arr[right++];
		}
	}

	while (left <= mid) {
		brr[cur++] = arr[left++];
	}
	while (right <= end) {
		brr[cur++] = arr[right++];
	}

	for (int i = start; i <= end; ++i) {
		arr[i] = brr[i];
	}
}

void merge_sort(int start, int end) {
	if (start >= end) {
		return;
	}

	int mid = (start + end) >> 1;
	merge_sort(start, mid);
	merge_sort(mid + 1, end);

	merge(start, mid, end);
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

	merge_sort(0, n - 1);

	for (i = 0; i < n; ++i) {
		cout << arr[i] << '\n';
	}
}
