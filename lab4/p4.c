#include <stdio.h>
#include <stdlib.h>

typedef struct CircularQueue {
	int *key;
	int front;
	int rear;
	int max_queue_size;
}CircularQueue;

void MakeEmpty(CircularQueue *Q, int max) {
	Q->key = (int*)malloc(max * sizeof(int));
	Q->front = 0;
	Q->rear = 0;
	Q->max_queue_size = max;
}

int IsEmpty(CircularQueue *Q) {
	return Q->front == Q->rear;
}

int IsFull(CircularQueue *Q) {
	return Q->front == (Q->rear + 1) % Q->max_queue_size;
}

void Dequeue(CircularQueue *Q) {
	if (IsEmpty(Q)) {
		printf("Queue is Empty\n");
		return;
	}
	Q->front = (Q->front + 1) % Q->max_queue_size;
}

void Enqueue(CircularQueue *Q, int X) {
	if (IsFull(Q)) {
		printf("Queue is full\n");
		return;
	}
	Q->rear = (Q->rear + 1) % Q->max_queue_size;
	Q->key[Q->rear] = X;
}

void PrintFirst(CircularQueue *Q) {
	if (IsEmpty(Q)) {
		printf("Queue is Empty\n");
		return;
	}
	printf("First Element : %d\n", Q->key[(Q->front + 1) % Q->max_queue_size]);
}

void PrintRear(CircularQueue *Q) {
	if (IsEmpty(Q)) {
		printf("Queue is Empty\n");
		return;
	}
	printf("Last Element : %d\n", Q->key[Q->rear]);
}

int main(int argc, char **argv)
{
	FILE *f1;
	f1 = fopen(argv[1], "r");
	CircularQueue* Q = (CircularQueue*)malloc(sizeof(CircularQueue));
	char c;
	fscanf(f1, " %c", &c);
	while (!feof(f1)) {
		int x;
		switch (c) {
		case 'e':
			fscanf(f1, " %d", &x);
			Enqueue(Q, x);
			break;
		case 'd':
			Dequeue(Q);
			break;
		case 'f':
			PrintFirst(Q);
			break;
		case 'r':
			PrintRear(Q);
			break;
		case 'n':
			fscanf(f1, " %d", &x);
			MakeEmpty(Q, x);
		}
		fscanf(f1, " %c", &c);
	}
	fclose(f1);
	return 0;
}