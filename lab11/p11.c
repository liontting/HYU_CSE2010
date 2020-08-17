#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
struct HashTable {
	int TableSize;
	ElementType* TheLists;
};

void Insert(ElementType Key, struct HashTable *H) {
	int hash_value = Key % H->TableSize;
	for (int i = 0; i < H->TableSize; i++) {
		if (Key == H->TheLists[i]) {
			printf("Duplicated value [%d]\n", Key);
			return;
		}
	}
	if (H->TheLists[hash_value] == -1)
		H->TheLists[hash_value] = Key;
	else {
		printf("Collision for the Key [%d] has occured.\n", Key);
		while (H->TheLists[hash_value] != -1)
			hash_value = (hash_value + 1) % H->TableSize;
		H->TheLists[hash_value] = Key;
	}
}

int find(struct HashTable *H, ElementType value) {
	for (int i = 0; i < H->TableSize; i++)
		if (H->TheLists[i] == value)
			return 1;
	return 0;
}

int main(int argc, char **argv) {
	FILE *f1;
	f1 = fopen(argv[1], "r");
	int N, key, num1 = 1, num2 = 1;
	char fir[1000], sec[1000];
	struct HashTable h;

	fscanf(f1, "%d ", &N);
	fgets(fir, 1000, f1);
	strtok(fir, " ");
	while (strtok(NULL, " "))
		num1++;
	fgets(sec, 1000, f1);
	strtok(sec, " ");
	while (strtok(NULL, " "))
		num2++;
	fseek(f1, 0, SEEK_SET);

	fscanf(f1, " %d", &N);
	h.TableSize = N;
	h.TheLists = (ElementType*)malloc(N * sizeof(ElementType));
	for (int i = 0; i < N; i++)
		h.TheLists[i] = -1;

	while (num1--) {
		fscanf(f1, " %d", &key);
		Insert(key, &h);
	}

	while (num2--) {
		fscanf(f1, " %d", &key);
		if(find(&h, key))
			printf("The key [%d] exists in the list\n", key);
		else
			printf("The key [%d] doesn't exist in the list\n", key);
	}

	printf("\nHash table Print out\n");
	for (int i = 0; i < h.TableSize; i++) {
		if (h.TheLists[i] != -1)
			printf("\n<%d> => [%d]", i, h.TheLists[i]);
		else
			printf("\n<%d> =>", i);
	}
	fclose(f1);
	return 0;
}