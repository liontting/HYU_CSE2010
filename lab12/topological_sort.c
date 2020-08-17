#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 10000

typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;
int* ver;
int* linknum;
int** adj_mat;

void init(QueueType *q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {
	return q->front == q->rear;
}

int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item) {
	if (is_full(q)) {
		printf("queue is full\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q) {
	if (is_empty(q)) {
		printf("queue is empty\n");
		return -1;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void graph_topological_mat(int num)
{
	QueueType q;
	init(&q);
	for (int i = 0; i < num; i++) {
		if(!linknum[i])
			enqueue(&q, i);
	}
	for (int i = 0; i < num; i++) {
		int n = dequeue(&q);
		printf("%d ", ver[n]);
		for (int j = 0; j < num; j++) {
			if (adj_mat[n][j]) {
				adj_mat[n][j] = 0;
				linknum[j]--;
				if (!linknum[j])
					enqueue(&q, j);
			}
		}
	}
}

int main(int argc, char **argv) {
	FILE *f1;
	f1 = fopen(argv[1], "r");
	int num1 = 1, num2 = 1;
	char fir[1000], sec[1000];

	fgets(fir, 1000, f1);
	strtok(fir, " ");
	while (strtok(NULL, " "))
		num1++;
	fgets(sec, 1000, f1);
	strtok(sec, " ");
	while (strtok(NULL, " "))
		num2++;
	fseek(f1, 0, SEEK_SET);

	ver = (int*)malloc(num1 * sizeof(int));
	adj_mat = (int **)malloc(num1 * sizeof(int *));
	for (int i = 0; i < num1; i++)
		adj_mat[i] = (int*)calloc(num1, sizeof(int));
	linknum = (int*)calloc(num1, sizeof(int));

	for (int i = 0; i < num1; i++) {
		fscanf(f1, "%d ", &ver[i]);
	}
	for (int i = 0; i < num2; i++) {
		int n1, n2, index1 = 0, index2 = 0;
		char c;
		fscanf(f1, "%d", &n1);
		fscanf(f1, "%c", &c);
		fscanf(f1, "%d ", &n2);
		for (int j = 0; j < num1; j++) {
			if (ver[j] == n1)
				index1 = j;
			else if (ver[j] == n2)
				index2 = j;
		}
		adj_mat[index1][index2] = 1;
		linknum[index2]++;
	}
	graph_topological_mat(num1);
	return 0;
}