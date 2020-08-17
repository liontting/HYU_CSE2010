#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

void display(TreeNode *p)
{
	if (p != NULL) {
		display(p->left);
		printf("%d ", p->key);
		display(p->right);
	}
}

TreeNode *search(TreeNode *node, int key)
{
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

void insert_node(TreeNode **root, int key)
{
	TreeNode *parNode, *curNode;
	TreeNode *newNode;
	curNode = *root;
	parNode = NULL;
	while (curNode != NULL) {
		if (key == curNode->key)
			return;
		parNode = curNode;
		if (key < curNode->key)
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}

	newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->key = key;
	newNode->left = newNode->right = NULL;

	if (parNode != NULL) {
		if (key < parNode->key)
			parNode->left = newNode;
		else
			parNode->right = newNode;
	}
	else
		*root = newNode;
}

void delete_node(TreeNode *node, int key)
{
	TreeNode *parNode, *curNode, *childNode, *succ, *succ_p;
	parNode = NULL;
	curNode = node;
	
	while (curNode != NULL && curNode->key != key) {
		parNode = curNode;
		if (key < curNode->key)
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}
	if (curNode == NULL) {
		printf("key is not in the tree\n");
		return;
	}
	
	if (curNode->left == NULL && curNode->right == NULL) {
		if (parNode->left == curNode)
			parNode->left = NULL;
		else
			parNode->right = NULL;
	} else if (curNode->left != NULL && curNode->right != NULL) {
		succ = curNode->right;
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		if (curNode->right == succ) {
			if (parNode->left == curNode)
				parNode->left = succ;
			else
				parNode->right = succ;
			succ->left = curNode->left;
		} else {
			succ_p->left = NULL;
			if (parNode->left == curNode)
				parNode->left = succ;
			else
				parNode->right = succ;
			succ->left = curNode->left;
			succ->right = curNode->right;
		}
	} else {
		if (curNode->left != NULL)
			childNode = curNode->left;
		else
			childNode = curNode->right;

		if (parNode->left == curNode)
			parNode->left = childNode;
		else
			parNode->right = childNode;
	}
	free(curNode);
}

int main() {
	TreeNode *root = NULL;
	insert_node(&root, 10);
	insert_node(&root, 5);
	insert_node(&root, 15);
	insert_node(&root, 4);
	insert_node(&root, 13);
	insert_node(&root, 17);
	insert_node(&root, 16);
	insert_node(&root, 20);
	display(root);
	if (search(root, 5) != NULL)
		printf("search success: %d\n", search(root, 5)->key);
	delete_node(root, 5);
	display(root);
	delete_node(root, 15);
	display(root);
	delete_node(root, 20);
	display(root);
	return 0;
}