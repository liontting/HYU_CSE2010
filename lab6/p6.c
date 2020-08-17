#include <stdio.h>
#include <stdlib.h>
struct Tree {
	int value;
	Tree *left;
	Tree *right;
};

Tree* insertNode(Tree *root, int key) {
	if (root == NULL) {
		root = (Tree*)malloc(sizeof(Tree));
		root->value = key;
		root->left = root->right = NULL;
	}
	else if (root->value > key)
		root->left = insertNode(root->left, key);
	else if (root->value < key)
		root->right = insertNode(root->right, key);
	else
		printf("%d is in the tree\n", key);
	return root;
}

Tree* deleteNode(Tree *root, int key) {
	Tree * Tmp;
	if (root == NULL)
		printf("%d is not in the tree\n", key);
	else if (root->value > key)
		root->left = deleteNode(root->left, key);
	else if (root->value < key)
		root->right = deleteNode(root->right, key);
	else if (root->left && root->right) {
		Tmp = root->right;
		while (Tmp->left != NULL) {
			Tmp = Tmp->left;
		}
		root->value = Tmp->value;
		root->right = deleteNode(root->right, root->value);
	}
	else {
		Tmp = root;
		if (root->left == NULL)
			root = root->right;
		else if (root->right == NULL)
			root = root->left;
		free(Tmp);
	}
	return root;
}

Tree* findNode(Tree *root, int key) {
	if (root == NULL)
		return NULL;
	if (root->value < key)
		return findNode(root->right, key);
	else if (root->value > key)
		return findNode(root->left, key);
	else
		return root;
}

void printInorder(Tree *root) {
	if (root == NULL)
		return;
	printInorder(root->left);
	printf("%d ", root->value);
	printInorder(root->right);
}

void printPreorder(Tree *root) {
	if (root == NULL)
		return;
	printf("%d ", root->value);
	printPreorder(root->left);
	printPreorder(root->right);
}

void printPostorder(Tree *root) {	if (root == NULL)
		return;	printPostorder(root->left);
	printPostorder(root->right);	printf("%d ", root->value);}

int main(int argc, char **argv) {
	FILE *f1;
	f1 = fopen(argv[1], "r");
	Tree* t = NULL;
	char c[5] = { 0, };
	while (!feof(f1)) {
		fscanf(f1, " %s", c);
		int x;
		if (c[0] == 'i') {
			fscanf(f1, " %d", &x);
			t = insertNode(t, x);
		}
		else if (c[0] == 'd') {
			fscanf(f1, " %d", &x);
			t = deleteNode(t, x);
		}
		else if (c[0] == 'f') {
			Tree* tmp;
			fscanf(f1, " %d", &x);
			tmp = findNode(t, x);
			if (tmp != NULL)
				printf("%d is in the tree\n", x);
			else
				printf("%d is not in the tree\n", x);
		}
		else if (c[0] == 'p') {
			if (c[1] == 'i') {
				printInorder(t);
				printf("\n");
			}
			else if (c[1] == 'r') {
				printPreorder(t);
				printf("\n");
			}
			else if (c[1] == 'o') {
				printPostorder(t);
				printf("\n");
			}
		}
	}
	fclose(f1);
	return 0;
}