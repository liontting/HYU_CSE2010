#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct HeapStruct {
	int Capacity;
	int Size;
	int *Elements;
};

HeapStruct* CreateHeap(int heapsize) {
	HeapStruct* heap = (HeapStruct*)malloc(sizeof(HeapStruct));
	heap->Capacity = heapsize;
	heap->Elements = (int*)malloc(sizeof(int)*(heapsize + 1));
	heap->Size = 0;
	return heap;
}

void Insert(HeapStruct* heap, int value) {
	int i;
	if (heap->Capacity == heap->Size) {
		printf("\theap is full\n");
		return;
	}
	for (i = ++heap->Size; i != 1 && heap->Elements[i / 2] > value; i /= 2) {
		heap->Elements[i] = heap->Elements[i / 2];
	}
	heap->Elements[i] = value;
}

int DeleteMin(HeapStruct* heap) {
	int i, child;
	int Min, Last;
	if (heap->Size == 0) {
		printf("\theap is empty\n");
		return 0;
	}
	Min = heap->Elements[1];
	Last = heap->Elements[heap->Size--];
	for (i = 1; i * 2 <= heap->Size; i = child) {
		child = i * 2;
		if (child != heap->Size&&heap->Elements[child + 1] < heap->Elements[child])
			child++;
		if (Last > heap->Elements[child])
			heap->Elements[i] = heap->Elements[child];
		else
			break;
	}
	heap->Elements[i] = Last;
	return Min;
}

int main(int argc, char **argv) {
	FILE *f1;
	f1 = fopen(argv[1], "r");
	HeapStruct* h = NULL;
	int x, num = 0;
	h = CreateHeap(MAX_SIZE);
	while (!feof(f1)) {
		fscanf(f1, " %d", &x);
		Insert(h, x);
		num++;
	}
	printf("heap_sort:\n");
	for (int i = 0; i < num; i++)
		printf("%d\t", DeleteMin(h));
	fclose(f1);
	return 0;
}