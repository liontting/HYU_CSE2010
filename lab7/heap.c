#include <stdio.h>
#define MAX_ELEMENT 10

typedef struct {
	int heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType *h) {
	h->heap_size = 0;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_heap(HeapType *h) {
	int i;
	int level = 1;
	printf("\n===================");
	for (i = 1; i <= h->heap_size; i++) {
		if (i == level) {
			printf("\n");
			level *= 2;
		}
		printf("\t%d", h->heap[i]);
	}
	printf("\n===================");
}

void insert_max_heap(HeapType *h, int item) {
	h->heap[++h->heap_size] = item;

	int child = h->heap_size;
	int parent = child / 2;

	while (child > 1 && h->heap[parent] < h->heap[child]) {
		swap(&h->heap[parent], &h->heap[child]);
		child = parent;
		parent = child / 2;
	}
}

int delete_max_heap(HeapType *h) {
	int result = h->heap[1];

	swap(&h->heap[1], &h->heap[h->heap_size--]);

	int parent = 1;
	int child = 2;
	
	if (child + 1 <= h->heap_size)
		child = (h->heap[child] > h->heap[child + 1]) ? child : child + 1;

	while (child <= h->heap_size && h->heap[parent] < h->heap[child]) {
		swap(&h->heap[parent], &h->heap[child]);

		parent = child;
		child *= 2;

		if(child+1<=h->heap_size)
			child = (h->heap[child] > h->heap[child + 1]) ? child : child + 1;

	}
	return result;
}

int main() {
	HeapType heap;
	init(&heap);
	insert_max_heap(&heap, 10);
	insert_max_heap(&heap, 5);
	insert_max_heap(&heap, 30);
	insert_max_heap(&heap, 15);
	insert_max_heap(&heap, 25);
	print_heap(&heap);
	int d1 = delete_max_heap(&heap);
	printf("\n <del. %d > \n", d1);
	print_heap(&heap);
	return 0;
}