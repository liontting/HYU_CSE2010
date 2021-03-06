#include<stdio.h>
#define MAX_SIZE 100
int n = 9;
int list[MAX_SIZE] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

void print(int list[], int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

int partition(int v[], int left, int right) {
	int pivot, temp;
	int low, high;
	
	low = left;
	high = right + 1;
	
	pivot = list[left];

	do {
		do {
			low++;
		} while (low <= right && list[low] < pivot);

		do {
			high--;
		} while (high >= left && list[high] > pivot);

		if (low < high)
			SWAP(list[low], list[high], temp);

	} while (low < high);

	SWAP(list[left], list[high], temp);

	return high;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		print(list, 9);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

int main() {
	quick_sort(list, 0, 8);
}