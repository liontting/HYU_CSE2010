#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node
{
	ElementType element;
	Position next;
};

List MakeEmpty(List L) {
	L = (List)malloc(sizeof(struct Node));
	L->element = -1;
	L->next = NULL;
	return L;
}

int IsEmpty(List L) {
	return L->next == NULL;
}

int IsLast(Position P, List L) {
	Position cur = L;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	return P == cur;
}

Position FindPrevious(ElementType X, List L) {
	int pandan = 0;
	Position Tmp = L;
	while (Tmp->next != NULL) {
		if (Tmp->next->element == X) {
			pandan = 1;
			break;
		}
		Tmp = Tmp->next;
	}
	if (pandan == 0)
		return NULL;
	else
		return Tmp;
}

void Delete(ElementType X, List L) {
	if (FindPrevious(X, L) != NULL) {
		Position xp = NULL;
		xp = FindPrevious(X, L)->next;
		FindPrevious(X, L)->next = xp->next;
		free(xp);
	}
	else
		printf("Deletion failed: element %d is not in the list.\n", X);
}

Position Find(ElementType X, List L) {
	int pandan = 0;
	Position Tmp = L;
	while (Tmp != NULL) {
		if (Tmp->element == X) {
			pandan = 1;
			break;
		}
		Tmp = Tmp->next;
	}
	if (pandan == 0)
		return NULL;
	else
		return Tmp;
}

void Insert(ElementType X, List L, Position P) {
	if (Find(X, L) != NULL) {
		P->next = Find(X, L)->next;
		Find(X, L)->next = P;
	}
	else
		printf("Insertion(%d) Failed: element %d is not in the list.\n", P->element, X);
}

void DeleteList(List L) {	Position P = NULL, Tmp = NULL;	P = L->next;	L->next = NULL;	while (P != NULL) {		Tmp = P->next;		free(P);		P = Tmp;	}}
int main(int argc, char **argv) {
	FILE *f1;
	f1 = fopen(argv[1], "r");
	List li = (List)malloc(sizeof(struct Node));
	li = MakeEmpty(li);
	char c;
	fscanf(f1, " %c", &c);
	while (!feof(f1)) {
		if (c == 'i') {
			ElementType n1, n2;
			fscanf(f1, " %d", &n1);
			fscanf(f1, " %d", &n2);
			Position P = (Position)malloc(sizeof(struct Node));
			P->element = n1;
			Insert(n2, li, P);
		}
		else if (c == 'd') {
			ElementType n1;
			fscanf(f1, " %d", &n1);
			Delete(n1, li);
		}
		else if (c == 'f') {
			ElementType n1;
			fscanf(f1, " %d", &n1);
			if (FindPrevious(n1, li) == NULL)
				printf("Could not find %d in the list\n", n1);
			else {
				printf("Key of the previous node of %d is ", n1);
				if (FindPrevious(n1, li) == li)
					printf("header\n");
				else
					printf("%d\n", FindPrevious(n1, li)->element);
			}
		}
		else if (c == 'p') {
			Position Tmp = (Position)malloc(sizeof(struct Node));
			Tmp = li->next;
			while (!IsLast(Tmp, li)) {
				printf("Key:%d   ", Tmp->element);
				Tmp = Tmp->next;
			}
			printf("Key:%d\n", Tmp->element);
		}
		fscanf(f1, " %c", &c);
	}
	DeleteList(li);
	fclose(f1);
	return 0;
}