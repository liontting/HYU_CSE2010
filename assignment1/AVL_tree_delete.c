#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
struct avl_node {
	struct avl_node *left_child, *right_child; // ����, ������ ���� Ʈ��
	int data; // ��� ���� ��
};
struct avl_node *root;

struct avl_node* rotate_right(struct avl_node *parent) { // ������ ȸ�� �Լ�
	struct avl_node *child = parent->left_child; // �Է� ���� ���(�θ� ���)�� ���� �ڽ��� ���� ���� ��忡 ����
	parent->left_child = child->right_child; // �θ� ����� ���� �ڽ� �ڸ���, �θ� ����� ���� �ڽ��� ������ ����Ʈ���� ����
	child->right_child = parent; // ���� ���� ����� ������ �ڽ� �ڸ���, �θ� ��带 ����
	return child; // ���� ���� ��带 ��ȯ
}
struct avl_node* rotate_left(struct avl_node *parent) { // ���� ȸ�� �Լ�
	struct avl_node *child = parent->right_child; // �Է� ���� ���(�θ� ���)�� ������ �ڽ��� ���� ���� ��忡 ����
	parent->right_child = child->left_child; // �θ� ����� ������ �ڽ� �ڸ���, �θ� ����� ������ �ڽ��� ���� ����Ʈ���� ����
	child->left_child = parent; // ���� ���� ����� ���� �ڽ� �ڸ���, �θ� ��带 ����
	return child; // ���� ���� ��带 ��ȯ
}

struct avl_node* rotate_right_left(struct avl_node *parent) { // ������-���� ȸ�� �Լ�
	struct avl_node *child = parent->right_child; // �Է� ���� ���(�θ� ���)�� ������ �ڽ��� ���� ���� ��忡 ����
	parent->right_child = rotate_right(child); // �θ� ����� ������ �ڽ� �ڸ���, �θ� ����� ������ �ڽ��� ������ ȸ���� ��� ���� ����
	return rotate_left(parent); // �θ� ��带 ���� ȸ���� ����� ��ȯ
}

struct avl_node* rotate_left_right(struct avl_node *parent) { // ����-������ ȸ�� �Լ�
	struct avl_node *child = parent->left_child; // �Է� ���� ���(�θ� ���)�� ���� �ڽ��� ���� ���� ��忡 ����
	parent->left_child = rotate_left(child);// �θ� ����� ���� �ڽ� �ڸ���, �θ� ����� ���� �ڽ��� ���� ȸ���� ��� ���� ����
	return rotate_right(parent); // �θ� ��带 ������ ȸ���� ����� ��ȯ
}

int get_height(struct avl_node *node) { // Ʈ���� ���̸� ���ϴ� �Լ�
	int height = 0;
	if (node != NULL) // ��尡 NULL�̸� 0�� ��ȯ
		height = 1 + max(get_height(node->left_child), get_height(node->right_child)); // ���� ����� ���� = �ڽ� ����� ���� �� ū �� + 1
	return height;
}

int get_height_diff(struct avl_node *node) { // ���� �μ��� ���ϴ� �Լ�
	if (node == NULL)
		return 0;
	return get_height(node->left_child) - get_height(node->right_child); // ���� �μ� = ���� ���� Ʈ���� ���� - ������ ���� Ʈ���� ����
}

struct avl_node* rebalance(struct avl_node **node) { // ������ ���� ���ġ�ϴ� �Լ�
	int height_diff = get_height_diff(*node); // ���� �μ��� ����
	if (height_diff > 1) { // ���� �μ��� 1���� Ŭ �� (���� ���� Ʈ���� ���̰� �� Ŭ ��)
		if (get_height_diff((*node)->left_child) > 0) // �ش� ����� ���� �ڽ��� ���� �μ��� 0���� Ŭ �� (LLŸ��)
			*node = rotate_right(*node); // ������ ȸ��
		else // (LR Ÿ��)
			*node = rotate_left_right(*node); // ����-������ ȸ��
	}
	else if (height_diff < -1) { // ���� �μ��� -1���� ���� �� (������ ���� Ʈ���� ���̰� �� Ŭ ��)
		if (get_height_diff((*node)->right_child) < 0) // �ش� ����� ������ �ڽ��� ���� �μ��� 0���� ���� �� (RRŸ��)
			*node = rotate_left(*node); // ���� ȸ��
		else // (RL Ÿ��)
			*node = rotate_right_left(*node); // ������-���� ȸ��
	}
	return *node;
}

struct avl_node* avl_add(struct avl_node** root, int new_key) { // ���� �Լ�
	if (*root == NULL) { // �ƹ� �͵� ���� ���
		*root = (struct avl_node*)malloc(sizeof(struct avl_node)); // �����Ҵ�
		if (*root == NULL) // �����Ҵ� ���� �� Ż��
			exit(1);
		(*root)->data = new_key; // �����Ҵ� �� node�� ���� ����
		(*root)->left_child = (*root)->right_child = NULL; // ���� Ʈ���� NULL�� �ʱ�ȭ
	}
	else if (new_key < (*root)->data) { // ���� ���� �ش� ����� ������ ���� ���
		(*root)->left_child = avl_add(&((*root)->left_child), new_key); // �ش� ����� ���� ���� Ʈ���� ���� ��� �Լ� ����
		*root = rebalance(root); // ���ġ �Լ��� ���� ������ ������
	}
	else if (new_key > (*root)->data) { // ���� ���� �ش� ����� ������ ū ���
		(*root)->right_child = avl_add(&((*root)->right_child), new_key); // �ش� ����� ������ ���� Ʈ���� ���� ��� �Լ� ����
		*root = rebalance(root); // ���ġ �Լ��� ���� ������ ������
	}
	else { // ���� ���� �ش� ����� ���� ���ٸ�
		exit(1); // Ż��
	}
	return *root;
}

void display(struct avl_node *node) { // Ʈ�� ��� �Լ�
	if (node != NULL) { // inorder �������� ���
		printf("(");
		display(node->left_child);
		printf("%d", node->data);
		display(node->right_child);
		printf(")");
	}
}

struct avl_node* avl_delete(struct avl_node **root, int new_key) { // ���� �Լ�
	struct avl_node* tmp;
	if (root == NULL) // ��尡 ���� ���
		exit(1); // Ż��
	else if ((*root)->data > new_key) // ��� ���� ���� ������ ������ ū ���
		(*root)->left_child = avl_delete(&((*root)->left_child), new_key); // �ش� ����� ���� ���� Ʈ���� ���� ��� �Լ� ����
	else if ((*root)->data < new_key) // ��� ���� ���� ������ ������ ���� ���
		(*root)->right_child = avl_delete(&((*root)->right_child), new_key); // �ش� ����� ������ ���� Ʈ���� ���� ��� �Լ� ����
	else if ((*root)->left_child && (*root)->right_child) { // ������ ���� ã�Ҵµ� �� ����� �ڽ��� 2�� �� �ִ� ���
		tmp = (*root)->right_child; // ������ ����� ������ ����Ʈ���� �ӽ÷� ����
		while (tmp->left_child != NULL) // �ӽ÷� ������ ����Ʈ���� ���� (����) ���� ���� ���� ������ ������ �ݺ����� ����
			tmp = tmp->left_child;
		(*root)->data = tmp->data; // ������ ��忡 �ӽ÷� ������ ����� ���� ����
		(*root)->right_child = avl_delete(&((*root)->right_child), (*root)->data); // ������ ����� ������ ����Ʈ������ ���� ���� ���� ����ִ� ��带 ��� �Լ��� ���� ����
	}
	else { // ������ ���� ã�Ҵµ� �� ����� �ڽ��� 1���Ǵ� 0���� ���
		tmp = (*root); // ������ ��带 �ӽ÷� ����
		if ((*root)->left_child == NULL) // ������ ����� ���� �ڽ��� ���� ���
			(*root) = (*root)->right_child; // ������ ��� ��ġ�� ������ ����� ������ ���� Ʈ���� ����
		else if ((*root)->right_child == NULL) // ������ ����� ������ �ڽ��� ���� ���
			(*root) = (*root)->left_child; // ������ ��� ��ġ�� ������ ����� ���� ���� Ʈ���� ����
		free(tmp); // ������ ����� �޸� ����
	}
	*root = rebalance(root); // ���ġ �Լ��� ���� ������ ������
	return *root;
}

int main() {
	avl_add(&root, 7);
	avl_add(&root, 8);
	avl_add(&root, 9);
	avl_add(&root, 2);
	avl_add(&root, 1);
	avl_add(&root, 5);
	avl_add(&root, 3);
	avl_add(&root, 6);
	avl_add(&root, 4);
	display(root);
	return 0;
}