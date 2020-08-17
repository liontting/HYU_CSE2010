#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
struct avl_node {
	struct avl_node *left_child, *right_child; // 왼쪽, 오른쪽 서브 트리
	int data; // 노드 안의 값
};
struct avl_node *root;

struct avl_node* rotate_right(struct avl_node *parent) { // 오른쪽 회전 함수
	struct avl_node *child = parent->left_child; // 입력 받은 노드(부모 노드)의 왼쪽 자식을 새로 만든 노드에 넣음
	parent->left_child = child->right_child; // 부모 노드의 왼쪽 자식 자리에, 부모 노드의 왼쪽 자식의 오른쪽 서브트리를 넣음
	child->right_child = parent; // 새로 만든 노드의 오른쪽 자식 자리에, 부모 노드를 넣음
	return child; // 새로 만든 노드를 반환
}
struct avl_node* rotate_left(struct avl_node *parent) { // 왼쪽 회전 함수
	struct avl_node *child = parent->right_child; // 입력 받은 노드(부모 노드)의 오른쪽 자식을 새로 만든 노드에 넣음
	parent->right_child = child->left_child; // 부모 노드의 오른쪽 자식 자리에, 부모 노드의 오른쪽 자식의 왼쪽 서브트리를 넣음
	child->left_child = parent; // 새로 만든 노드의 왼쪽 자식 자리에, 부모 노드를 넣음
	return child; // 새로 만든 노드를 반환
}

struct avl_node* rotate_right_left(struct avl_node *parent) { // 오른쪽-왼쪽 회전 함수
	struct avl_node *child = parent->right_child; // 입력 받은 노드(부모 노드)의 오른쪽 자식을 새로 만든 노드에 넣음
	parent->right_child = rotate_right(child); // 부모 노드의 오른쪽 자식 자리에, 부모 노드의 오른쪽 자식을 오른쪽 회전한 결과 값을 넣음
	return rotate_left(parent); // 부모 노드를 왼쪽 회전한 결과값 반환
}

struct avl_node* rotate_left_right(struct avl_node *parent) { // 왼쪽-오른쪽 회전 함수
	struct avl_node *child = parent->left_child; // 입력 받은 노드(부모 노드)의 왼쪽 자식을 새로 만든 노드에 넣음
	parent->left_child = rotate_left(child);// 부모 노드의 왼쪽 자식 자리에, 부모 노드의 왼쪽 자식을 왼쪽 회전한 결과 값을 넣음
	return rotate_right(parent); // 부모 노드를 오른쪽 회전한 결과값 반환
}

int get_height(struct avl_node *node) { // 트리의 높이를 구하는 함수
	int height = 0;
	if (node != NULL) // 노드가 NULL이면 0을 반환
		height = 1 + max(get_height(node->left_child), get_height(node->right_child)); // 현재 노드의 높이 = 자식 노드의 높이 중 큰 값 + 1
	return height;
}

int get_height_diff(struct avl_node *node) { // 균형 인수를 구하는 함수
	if (node == NULL)
		return 0;
	return get_height(node->left_child) - get_height(node->right_child); // 균형 인수 = 왼쪽 서브 트리의 높이 - 오른쪽 서브 트리의 높이
}

struct avl_node* rebalance(struct avl_node **node) { // 균형을 위해 재배치하는 함수
	int height_diff = get_height_diff(*node); // 균형 인수를 구함
	if (height_diff > 1) { // 균형 인수가 1보다 클 때 (왼쪽 서브 트리의 높이가 더 클 때)
		if (get_height_diff((*node)->left_child) > 0) // 해당 노드의 왼쪽 자식의 균형 인수가 0보다 클 때 (LL타입)
			*node = rotate_right(*node); // 오른쪽 회전
		else // (LR 타입)
			*node = rotate_left_right(*node); // 왼쪽-오른쪽 회전
	}
	else if (height_diff < -1) { // 균형 인수가 -1보다 작을 때 (오른쪽 서브 트리의 높이가 더 클 때)
		if (get_height_diff((*node)->right_child) < 0) // 해당 노드의 오른쪽 자식의 균형 인수가 0보다 작을 때 (RR타입)
			*node = rotate_left(*node); // 왼쪽 회전
		else // (RL 타입)
			*node = rotate_right_left(*node); // 오른쪽-왼쪽 회전
	}
	return *node;
}

struct avl_node* avl_add(struct avl_node** root, int new_key) { // 삽입 함수
	if (*root == NULL) { // 아무 것도 없는 경우
		*root = (struct avl_node*)malloc(sizeof(struct avl_node)); // 동적할당
		if (*root == NULL) // 동적할당 오류 시 탈출
			exit(1);
		(*root)->data = new_key; // 동적할당 된 node에 값을 넣음
		(*root)->left_child = (*root)->right_child = NULL; // 서브 트리를 NULL로 초기화
	}
	else if (new_key < (*root)->data) { // 넣을 값이 해당 노드의 값보다 작은 경우
		(*root)->left_child = avl_add(&((*root)->left_child), new_key); // 해당 노드의 왼쪽 서브 트리에 대해 재귀 함수 동작
		*root = rebalance(root); // 재배치 함수를 통해 균형을 맞춰줌
	}
	else if (new_key > (*root)->data) { // 넣을 값이 해당 노드의 값보다 큰 경우
		(*root)->right_child = avl_add(&((*root)->right_child), new_key); // 해당 노드의 오른쪽 서브 트리에 대해 재귀 함수 동작
		*root = rebalance(root); // 재배치 함수를 통해 균형을 맞춰줌
	}
	else { // 넣을 값이 해당 노드의 값과 같다면
		exit(1); // 탈출
	}
	return *root;
}

void display(struct avl_node *node) { // 트리 출력 함수
	if (node != NULL) { // inorder 형식으로 출력
		printf("(");
		display(node->left_child);
		printf("%d", node->data);
		display(node->right_child);
		printf(")");
	}
}

struct avl_node* avl_delete(struct avl_node **root, int new_key) { // 삭제 함수
	struct avl_node* tmp;
	if (root == NULL) // 노드가 없는 경우
		exit(1); // 탈출
	else if ((*root)->data > new_key) // 노드 안의 값이 삭제할 값보다 큰 경우
		(*root)->left_child = avl_delete(&((*root)->left_child), new_key); // 해당 노드의 왼쪽 서브 트리에 대해 재귀 함수 동작
	else if ((*root)->data < new_key) // 노드 안의 값이 삭제할 값보다 작은 경우
		(*root)->right_child = avl_delete(&((*root)->right_child), new_key); // 해당 노드의 오른쪽 서브 트리에 대해 재귀 함수 동작
	else if ((*root)->left_child && (*root)->right_child) { // 삭제할 값을 찾았는데 그 노드의 자식이 2개 다 있는 경우
		tmp = (*root)->right_child; // 삭제할 노드의 오른쪽 서브트리를 임시로 저장
		while (tmp->left_child != NULL) // 임시로 저장한 서브트리의 가장 (왼쪽) 작은 값을 가진 노드까지 가도록 반복문을 돌림
			tmp = tmp->left_child;
		(*root)->data = tmp->data; // 삭제할 노드에 임시로 저장한 노드의 값을 넣음
		(*root)->right_child = avl_delete(&((*root)->right_child), (*root)->data); // 삭제할 노드의 오른쪽 서브트리에서 가장 작은 값이 들어있던 노드를 재귀 함수를 통해 삭제
	}
	else { // 삭제할 값을 찾았는데 그 노드의 자식이 1개또는 0개인 경우
		tmp = (*root); // 삭제할 노드를 임시로 저장
		if ((*root)->left_child == NULL) // 삭제할 노드의 왼쪽 자식이 없는 경우
			(*root) = (*root)->right_child; // 삭제할 노드 위치에 삭제할 노드의 오른쪽 서브 트리를 넣음
		else if ((*root)->right_child == NULL) // 삭제할 노드의 오른쪽 자식이 없는 경우
			(*root) = (*root)->left_child; // 삭제할 노드 위치에 삭제할 노드의 왼쪽 서브 트리를 넣음
		free(tmp); // 삭제할 노드의 메모리 해제
	}
	*root = rebalance(root); // 재배치 함수를 통해 균형을 맞춰줌
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