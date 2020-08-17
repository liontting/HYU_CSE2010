#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

struct HeapStruct {
	int Capacity;
	int Size;
	ElementType *Elements;
};

HeapStruct* CreateHeap(int heapsize) {
	HeapStruct* heap = (HeapStruct*)malloc(sizeof(HeapStruct));
	heap->Capacity = heapsize;
	heap->Elements = (ElementType*)malloc(sizeof(ElementType)*(heapsize + 1));
	heap->Size = 0;
	return heap;
}

void Insert(HeapStruct* heap, ElementType value) {
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

ElementType DeleteMin(HeapStruct* heap) {
	int i, child;
	ElementType Min, Last;
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

void PrintHeap(HeapStruct heap) {
	int i;
	int level = 1;
	if (heap.Size == 0) {
		printf("\theap is empty\n");
		return;
	}
	for (i = 1; i <= heap.Size; i++) {
		if (i == level) {
			printf("\n");
			level *= 2;
		}
		printf("\t%d", heap.Elements[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	FILE *f1;
	f1 = fopen(argv[1], "r");
	HeapStruct* h = NULL;
	char c;
	fscanf(f1, " %c", &c);
	while (!feof(f1)) {
		if (c == 'n') {
			int x1;
			fscanf(f1, " %d", &x1);
			h = CreateHeap(x1);
		}
		else if (c == 'i') {
			ElementType x2;
			fscanf(f1, " %d", &x2);
			Insert(h, x2);
		}
		else if (c == 'd') {
			DeleteMin(h);
		}
		else if (c == 'p') {
			PrintHeap(*h);
		}
		fscanf(f1, " %c", &c);
	}
	fclose(f1);
	return 0;
}