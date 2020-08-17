#include <stdio.h>
#include <stdlib.h>
typedef struct Tree_node {
	int key;
	struct Tree_node *left;
	struct Tree_node *right;
}Tree_node;

Tree_node* CreateNode(int key) {
	Tree_node* node = (Tree_node*)malloc(sizeof(Tree_node));
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	return node;
}

void Preorder(Tree_node* node) {
	if (node == NULL)
		return;
	printf("%d ", node->key);
	Preorder(node->left);
	Preorder(node->right);
}

void Inorder(Tree_node* node) {
	if (node == NULL)
		return;
	Inorder(node->left);
	printf("%d ", node->key);
	Inorder(node->right);
}

void Postorder(Tree_node* node) {
	if (node == NULL)
		return;
	Postorder(node->left);
	Postorder(node->right);
	printf("%d ", node->key);
}

void MakeLeftSubTree(Tree_node * main, Tree_node * sub) {
	if (main->left != NULL)
		return;
	main->left = sub;
}
void MakeRightSubTree(Tree_node * main, Tree_node * sub) {
	if (main->right != NULL)
		return;
	main->right = sub;
}

int main() {
	Tree_node * t0 = CreateNode(0);
	Tree_node * t1 = CreateNode(1);
	Tree_node * t2 = CreateNode(2);
	Tree_node * t3 = CreateNode(3);
	Tree_node * t4 = CreateNode(4);
	Tree_node * t5 = CreateNode(5);
	Tree_node * t6 = CreateNode(6);
	Tree_node * t7 = CreateNode(7);
	Tree_node * t8 = CreateNode(8);
	Tree_node * t9 = CreateNode(9);
	Tree_node * t10 = CreateNode(10);
	Tree_node * t11 = CreateNode(11);
	MakeLeftSubTree(t0, t1);
	MakeLeftSubTree(t1, t3);
	MakeLeftSubTree(t3, t7);
	MakeLeftSubTree(t4, t9);
	MakeLeftSubTree(t2, t5);
	MakeLeftSubTree(t5, t11);
	MakeRightSubTree(t0, t2);
	MakeRightSubTree(t1, t4);
	MakeRightSubTree(t3, t8);
	MakeRightSubTree(t4, t10);
	MakeRightSubTree(t2, t6);
	printf("inorder : ");
	Inorder(t0);
	printf("\n");
	printf("preorder : ");
	Preorder(t0);
	printf("\n");
	printf("postorder : ");
	Postorder(t0);
	printf("\n");
	return 0;
}