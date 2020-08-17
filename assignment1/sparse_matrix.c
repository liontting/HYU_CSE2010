#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50 // �ִ� ��� ũ��
typedef enum {
	head,
	entry
} tagfield; // ��� ���� ��Ʈ�� ��带 ��Ÿ���� ���� tag �ʵ�
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;
typedef struct matrix_node {
	matrix_pointer down; // column(��)�� ������ ����Ʈ�� ������ �� ���
	matrix_pointer right; // row(��)�� ������ ����Ʈ�� ������ �� ���
	tagfield tag;
	union {
		matrix_pointer next; // ��� ������ ������ �� ���
		entry_node entry;
	} u;
} matrix_node;
matrix_pointer hdnode[MAX_SIZE]; // ��� ����� �� ������ MAX_SIZE

matrix_pointer new_node(void) { // �� ��� ��带 �����Ͽ� ��ȯ�ϴ� �Լ�
	matrix_pointer temp;
	temp = (matrix_pointer)malloc(sizeof(matrix_node));
	return temp;
}

matrix_pointer mread(void) { // ����� �о� ���� ǥ������ ����, ���� ���� �迭 hdnode�� ����
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	matrix_pointer temp, last, node;
	printf("Enter the number of rows, columns, and number of nonzero terms: ");
	scanf("%d%d%d", &numRows, &numCols, &numTerms); // ���� ���� ��, ���� ��, 0�� �ƴ� ���� �� �Է�
	numHeads = (numCols > numRows) ? numCols : numRows;
	// ��� ��� ����Ʈ�� ���� ��� ��带 ����
	node = new_node(); node->tag = entry;
	node->u.entry.row = numRows;
	node->u.entry.col = numCols;
	if (!numHeads)
		node->right = node;
	else { // ��� ������ �ʱ�ȭ
		for (i = 0; i < numHeads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0]; // ���� ���� ������ ���
		for (i = 0; i < numTerms; i++) {
			printf("Enter row, column and value: ");
			scanf("%d%d%d", &row, &col, &value);
			if (row > currentRow) { // ���� ���� ����
				last->right = hdnode[currentRow];
				currentRow = row; last = hdnode[row];
			}
			temp = new_node();
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp; // �� ����Ʈ�� ����
			last = temp;
			hdnode[col]->u.next->down = temp; // �� ����Ʈ�� ����
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[currentRow]; // ������ ���� ����
		for (i = 0; i < numCols; i++) // ��� �� ����Ʈ�� ����
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < numHeads - 1; i++) // ��� ��� ������ ����
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[numHeads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}

void mwrite(matrix_pointer node) { // ����� �� �켱���� ����Ѵ�.
	int i;
	matrix_pointer temp, head = node->right;
	// ����� ����
	printf("\n numRows = %d, numCols = %d \n", node->u.entry.row, node->u.entry.col);
	printf(" The matrix by row, column, and value: \n\n");
	for (i = 0; i < node->u.entry.row; i++) { // �� �࿡ �ִ� ��Ʈ������ ���
		for (temp = head->right; temp != head; temp = temp->right)
			printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next; // ���� ��
	}
}

matrix_pointer madd(matrix_pointer m1, matrix_pointer m2) { // �� ����� ���Ͽ� ��ȯ�ϴ� �Լ�
	int resultHeads, i, currentRow, check = 0; // resultHeads: result�� ��� ��� ��, check: ���� ����� ��ġ�� ���� ���� üũ��
	matrix_pointer result = NULL, t, temp, tmp1, tmp2; // result: ������� ��� ��� ����Ʈ�� ���� ��� ���, t: result�� ��� ��� �ʱ�ȭ�� ���̴� ����, temp: ���� �Ҷ� ��� ��Ƶδ� ����, tmp1, tmp2: ���� m1, m2 ���� ��带 ���� ���� ������� ����
	matrix_pointer re_hdnode[MAX_SIZE], last, re_node; // re_hdnode[MAX_SIZE]: result ����Ʈ�� ����� ���� ���� �迭, re_node: ������� �� ��带 ����Ű�� ����
	if (m1->u.entry.col != m2->u.entry.col || m1->u.entry.row != m2->u.entry.row) {
		printf("�� ����� ũ�Ⱑ �޶� ���� �� �����ϴ�.\n");
		return NULL;
	}
	resultHeads = (m1->u.entry.col > m1->u.entry.row) ? m1->u.entry.col : m1->u.entry.row;
	result = new_node(); result->tag = entry;
	result->u.entry.row = m1->u.entry.row;
	result->u.entry.col = m1->u.entry.col;
	if (!resultHeads)
		result->right = result;
	else { // ������� ��� ������ �ʱ�ȭ
		for (i = 0; i < resultHeads; i++) {
			t = new_node();
			re_hdnode[i] = t; re_hdnode[i]->tag = head;
			re_hdnode[i]->right = t; re_hdnode[i]->u.next = t;
		}
		currentRow = 0;
		last = re_hdnode[0]; // ���� ���� ������ ���

		tmp1 = m1->right;
		tmp2 = m2->right; // m1, m2�� �ݺ����� ���� ���� �Ҵ�
		while (!(tmp1 == m1 && tmp2 == m2)) {
			if (tmp1->tag == head) { // tmp1�� ���� head�� ����
				if (tmp1->right == tmp1) { // ���� �࿡ �ٸ� ��尡 ���ٸ�
					tmp1 = tmp1->u.next; // ���� ������ �̵�
					continue; // ���� �࿡�� �ٸ� ��尡 ���� �� �����Ƿ� continue�� ��������
				}
				tmp1 = tmp1->right; // �� �࿡�� ���� ���� �̵�
			}
			if (tmp2->tag == head) { // tmp1�� ���� head�� ����
				if (tmp2->right == tmp2) {// ���� �࿡ �ٸ� ��尡 ���ٸ�
					tmp2 = tmp2->u.next; // ���� ������ �̵�
					continue; // ���� �࿡�� �ٸ� ��尡 ���� �� �����Ƿ� continue�� ��������
				}
				tmp2 = tmp2->right; // �� �࿡�� ���� ���� �̵�
			}

			if (tmp1->u.entry.row < tmp2->u.entry.row) { // tmp2�� row�� �� ũ��
				temp = tmp1; // tmp1�� �����̹Ƿ� temp�� �ְ�
				tmp1 = tmp1->right; // �������� �ѱ�
				check = 0;
			}
			else if (tmp1->u.entry.row > tmp2->u.entry.row) { // tmp1�� row�� �� ũ��
				temp = tmp2; // tmp2�� �����̹Ƿ� temp�� �ְ�
				tmp2 = tmp2->right; // �������� �ѱ�
				check = 0;
			}
			else { // tmp1, tmp2�� row�� ���ٸ�
				if (tmp1->u.entry.col < tmp2->u.entry.col) { // tmp2�� col�� �� ũ��
					temp = tmp1; // tmp1�� �����̹Ƿ� temp�� �ְ�
					tmp1 = tmp1->right; // �������� �ѱ�
					check = 0;
				}
				else if (tmp1->u.entry.col > tmp2->u.entry.col) { // tmp1�� col�� �� ũ��
					temp = tmp2; // tmp2�� �����̹Ƿ� temp�� �ְ�
					tmp2 = tmp2->right; // �������� �ѱ�
					check = 0;
				}
				else { // tmp1, tmp2�� row, col�� ���ٸ�
					temp = tmp1; // �ϴ� tmp1�� ������ �־��(���߿� ���� tmp2�� ���� ����)
					check = 1; // ��,���� ������ ǥ��
				}
			}

			if (temp->u.entry.row > currentRow) { // ���� ���� ����
				last->right = re_hdnode[currentRow];
				currentRow = temp->u.entry.row; last = re_hdnode[temp->u.entry.row];
			}
			re_node = new_node();
			re_node->tag = entry;
			re_node->u.entry.row = temp->u.entry.row;
			re_node->u.entry.col = temp->u.entry.col;
			if (check == 1) { // ��, ���� ���� ��
				re_node->u.entry.value = temp->u.entry.value + tmp2->u.entry.value; // tmp1�� ��, tmp2�� ���� ����
				tmp1 = tmp1->right;
				tmp2 = tmp2->right;
			}
			else // ��, ���� �ٸ� ��
				re_node->u.entry.value = temp->u.entry.value; // temp�ȿ� �־�� ���� ����
			last->right = re_node; // �� ����Ʈ�� ����
			last = re_node;
			re_hdnode[temp->u.entry.col]->u.next->down = re_node; // �� ����Ʈ�� ����
			re_hdnode[temp->u.entry.col]->u.next = re_node;

			if (tmp1->tag == head) // ���� head�� �� ���� �˻簡 �� �� ���̹Ƿ� ���� ������ �̵�
				tmp1 = tmp1->u.next;
			if (tmp2->tag == head)
				tmp2 = tmp2->u.next;
		}
		last->right = re_hdnode[currentRow]; // ������ ���� ����
		for (i = 0; i < result->u.entry.col; i++) // ��� �� ����Ʈ�� ����
			re_hdnode[i]->u.next->down = re_hdnode[i];
		for (i = 0; i < resultHeads - 1; i++) // ��� ��� ������ ����
			re_hdnode[i]->u.next = re_hdnode[i + 1];
		re_hdnode[resultHeads - 1]->u.next = result;
		result->right = re_hdnode[0];
	}
	return result;
}

matrix_pointer mtranspose(matrix_pointer node) { // ����� ��ġ ��ķ� ��ȯ�ϴ� �Լ�
	int resultHeads, i, currentRow; // resultHeads: result�� ��� ��� ��
	matrix_pointer result = NULL, t, temp; // result: ������� ��� ��� ����Ʈ�� ���� ��� ���, t: result�� ��� ��� �ʱ�ȭ�� ���̴� ����, temp: node�� �ݺ����� ������ �����ͷ� ����ϴ� ����
	matrix_pointer re_hdnode[MAX_SIZE], last, re_node; // re_hdnode[MAX_SIZE]: result ����Ʈ�� ����� ���� ���� �迭, re_node: ������� �� ��带 ����Ű�� ����

	resultHeads = (node->u.entry.col > node->u.entry.row) ? node->u.entry.col : node->u.entry.row;
	result = new_node(); result->tag = entry;
	result->u.entry.row = node->u.entry.col; // ��ġ�̱� ������ row�� col�� ���� �ٲ㼭 ����
	result->u.entry.col = node->u.entry.row;
	if (!resultHeads)
		result->right = result;
	else { // ������� ��� ������ �ʱ�ȭ
		for (i = 0; i < resultHeads; i++) {
			t = new_node();
			re_hdnode[i] = t; re_hdnode[i]->tag = head;
			re_hdnode[i]->right = t; re_hdnode[i]->u.next = t;
		}
		currentRow = 0;
		last = re_hdnode[0]; // ���� ���� ������ ���

		temp = node->right; // node�� �ݺ����� ������ ���� �Ҵ�
		while (!(temp == node)) {
			if (temp->tag == head) { // temp�� ���� head�� ����
				if (temp->right == temp) { // ���� �࿡ �ٸ� ��尡 ���ٸ�
					temp = temp->u.next; // ���� ������ �̵�
					continue; // ���� �࿡�� �ٸ� ��尡 ���� �� �����Ƿ� continue�� ��������
				}
				temp = temp->right; // �� �࿡�� ���� ���� �̵�
			}
			if (temp->u.entry.col > currentRow) { // ���� ���� ����
				last->right = re_hdnode[currentRow];
				currentRow = temp->u.entry.col; last = re_hdnode[temp->u.entry.col];
			}
			re_node = new_node();
			re_node->tag = entry;
			re_node->u.entry.row = temp->u.entry.col; // row�� col�� ���� �ٲ㼭 ����
			re_node->u.entry.col = temp->u.entry.row;
			re_node->u.entry.value = temp->u.entry.value;
			last->right = re_node; // �� ����Ʈ�� ����
			last = re_node;
			re_hdnode[temp->u.entry.row]->u.next->down = re_node; // �� ����Ʈ�� ����
			re_hdnode[temp->u.entry.row]->u.next = re_node;

			temp = temp->right; // ���� ��ġ�� �̵�
			if (temp->tag == head) // ���� head�� �� ���� �˻簡 �� �� ���̹Ƿ� ���� ������ �̵�
				temp = temp->u.next;
		}

		last->right = re_hdnode[currentRow]; // ������ ���� ����
		for (i = 0; i < result->u.entry.col; i++) // ��� �� ����Ʈ�� ����
			re_hdnode[i]->u.next->down = re_hdnode[i];
		for (i = 0; i < resultHeads - 1; i++) // ��� ��� ������ ����
			re_hdnode[i]->u.next = re_hdnode[i + 1];
		re_hdnode[resultHeads - 1]->u.next = result;
		result->right = re_hdnode[0];
	}
	return result;
}

matrix_pointer mmult(matrix_pointer m1, matrix_pointer m2) { // �� ����� ���� ���Ͽ� ��ȯ�ϴ� �Լ�
	int resultHeads, i, j, currentRow, row, col, value, check = 0; // resultHeads: result�� ��� ��� ��, row, col, value: ���� ���� ���� �� row, col, value ���� ��� ���� ����, check: ������ �����ϴ� �������� üũ�ϴ� ����
	matrix_pointer result = NULL, t, temp, tmp1, tmp2, tm_head1, tm_head2; // result: ������� ��� ��� ����Ʈ�� ���� ��� ���, t: result�� ��� ��� �ʱ�ȭ�� ���̴� ����, tmp1, tmp2: ���� m1, m2 ���� ��带 ���� ���� ������� ����, tm_head1, tm_head2: m1,m2�� �ݺ����� �� �� ������ ��� ��带 ��� ����
	matrix_pointer re_hdnode[MAX_SIZE], last, re_node; // re_hdnode[MAX_SIZE]: result ����Ʈ�� ����� ���� ���� �迭, re_node: ������� �� ��带 ����Ű�� ����
	if (m1->u.entry.col != m2->u.entry.row) {
		printf("ù ��° ����� ���� �� ��° ����� ���� ������ �޶� ���� �� �����ϴ�.\n");
		return NULL;
	}
	resultHeads = (m2->u.entry.col > m1->u.entry.row) ? m2->u.entry.col : m1->u.entry.row;
	result = new_node(); result->tag = entry;
	result->u.entry.row = m1->u.entry.row;
	result->u.entry.col = m2->u.entry.col;
	if (!resultHeads)
		result->right = result;
	else { // ������� ��� ������ �ʱ�ȭ
		for (i = 0; i < resultHeads; i++) {
			t = new_node();
			re_hdnode[i] = t; re_hdnode[i]->tag = head;
			re_hdnode[i]->right = t; re_hdnode[i]->u.next = t;
		}
		currentRow = 0;
		last = re_hdnode[0]; // ���� ���� ������ ���

		tm_head1 = m1->right;
		tm_head2 = m2->right; // ������ ù��° ��� ��带 ��� ����
		tmp1 = m1->right;
		tmp2 = m2->right;
		for (i = 0; i < m1->u.entry.row; i++) {
			row = 0, col = 0, value = 0;
			for (j = 0; j < m2->u.entry.col; ) { // ������ ��Ȳ�� ���� ����
				if (j == 0 && check == 0) {
					tmp1 = tm_head1->right; // �� �̵�
					tmp2 = tm_head2->down; // �� �̵�
				}

				if (tmp2->tag == head || tmp2->down == tmp2) { // �ι�° ����� �ش� ���� ��尡 ���� ��
					check = 0;
					tm_head2 = tm_head2->u.next; // ���� ��� ���� �̵�
					tmp2 = tm_head2->down; // �� ���� �ִ� ��� ��� ���� ���� �̵�
					tmp1 = tm_head1->right;
					row = 0, col = 0, value = 0;
					j++;
				}

				if (tmp1->tag == head) {
					if (tmp1->right == tmp1) { // ù��° ����� �� ��尡 ���ٸ�
						check = 0;
						break; // for�� �ϳ� Ż��
					}
					if (tm_head2->u.next != m2) {
						check = 0;
						tmp1 = tm_head1->right;
						tm_head2 = tm_head2->u.next;
						tmp2 = tm_head2->down;
						row = 0, col = 0, value = 0;
						j++;
					}
					else
						j++;
				}

				if (j >= m2->u.entry.col) // j�� ������ �Ѿ�� for�� Ż��
					break;

				if (tmp1->u.entry.col < tmp2->u.entry.row) { // ���� �ι�° ����� ���� ù��° ����� ������ ũ��
					check = 1; // �����ϴ� ������ ǥ��
					tmp1 = tmp1->right; // ù��° ����� �� ��带 ���� ���� �̵�
				}
				else if (tmp1->u.entry.col > tmp2->u.entry.row) { // ���� �ι�° ����� ���� ù��° ����� ������ ������
					check = 1; // �����ϴ� ������ ǥ��
					tmp2 = tmp2->down; // �ι�° ����� �� ��带 ���� ���� �̵�
				}
				else { // ���� �ι�° ����� ��� ù��° ����� ���� ������
					check = 1; // �����ϴ� ������ ǥ��
					if (value == 0) { // ���� ���� value�� 0�̶� ��带 ���� ������ �ȴٸ�
						row = tmp1->u.entry.row;
						col = tmp2->u.entry.col;
						value = tmp1->u.entry.value * tmp2->u.entry.value; // ���� ���� ����
						if (row > currentRow) { // ���� ���� ����
							last->right = re_hdnode[currentRow];
							currentRow = row; last = re_hdnode[row];
						}
						re_node = new_node();
						re_node->tag = entry;
						re_node->u.entry.row = row;
						re_node->u.entry.col = col;
						re_node->u.entry.value = value;
						last->right = re_node; // �� ����Ʈ�� ����
						last = re_node;
						re_hdnode[col]->u.next->down = re_node; // �� ����Ʈ�� ����
						re_hdnode[col]->u.next = re_node;
						tmp1 = tmp1->right;
						tmp2 = tmp2->down; // ���� ���� �̵�
					}
					else { // value�� 0�� �ƴ϶��
						row = tmp1->u.entry.row;
						col = tmp2->u.entry.col;
						temp = re_hdnode[row]->right; // temp�� ���� ���� ã���ְ�
						while (1) {
							if (temp->u.entry.col == col) { // ���� ���� ã�Ƽ�
								temp->u.entry.value += tmp1->u.entry.value * tmp2->u.entry.value; // �̹� ���� �ִ� ��ġ�� ���� ���� ���� ���Ѵ�.
								break;
							}
							else
								temp = temp->right; // ���ϴ� ���� ���ö����� ã�´�.
							if (temp->tag == head) // ��� ���� ���ƿ��� break�� Ż��
								break;
						}
						tmp1 = tmp1->right;
						tmp2 = tmp2->down; // ���� ���� �Ѿ��.
					}
				}
			}

			tm_head1 = tm_head1->u.next; // ù��° ����� �� �̵�
			tm_head2 = m2->right; // �ι�° ����� �ٽ� ó������ �̵�
			check = 0;
		}

		last->right = re_hdnode[currentRow]; // ������ ���� ����
		for (i = 0; i < result->u.entry.col; i++) // ��� �� ����Ʈ�� ����
			re_hdnode[i]->u.next->down = re_hdnode[i];
		for (i = 0; i < resultHeads - 1; i++) // ��� ��� ������ ����
			re_hdnode[i]->u.next = re_hdnode[i + 1];
		re_hdnode[resultHeads - 1]->u.next = result;
		result->right = re_hdnode[0];
	}
	return result;
}

void printf_menu() { // ���� �޴� ��� �Լ�
	printf("------------------------------\n");
	printf("       M    E    N    U       \n");
	printf("1. Matrix Read\n");
	printf("2. Matrix Write\n");
	printf("3. Matrix Erase\n");
	printf("4. Matrix Add\n");
	printf("5. Matrix Multiply\n");
	printf("6. Matrix Transpose\n");
	printf("7. Program Exit\n");
	printf("------------------------------\n");
	printf("You select a menu number\n");
	printf("Menu: ");
}

int main() {
	int num;
	matrix_pointer first = NULL, second = NULL;
	while (1) {
		printf_menu();
		scanf("%d", &num);
		if (num == 1) {
			printf("---------------------------\n");
			printf("ù �� °  �� �� �� �� ��  �� �� �� �� ��.\n");
			first = mread();
			printf("\n");
			printf("�� �� °  �� �� �� �� ��  �� �� �� �� ��.\n");
			second = mread();
		}
		else if (num == 2) {
			printf("---------------------------\n");
			printf("ù �� °  �� �� ��  �� ��  �� ��  �� �� . .\n");
			mwrite(first);
			printf("\n");
			printf("�� �� °  �� �� ��  �� ��  �� ��  �� �� . .\n");
			mwrite(second);
		}
		else if (num == 4) {
			printf("--------------------------------\n");
			printf("�� �� ��  �� �� ��  �� ��  �� ��  �� �� �� . .\n");
			matrix_pointer result = madd(first, second);
			mwrite(result);
		}
		else if (num == 5) {
			printf("--------------------------------\n");
			printf("�� �� ��  �� �� ��  �� ��  �� ��  �� �� �� . .\n");
			matrix_pointer result = mmult(first, second);
			mwrite(result);
		}
		else if (num == 6) {
			printf("-------------------------------------\n");
			printf("�� �� ��  �� ��  �� �� ��  �� ġ  �� �� ��  �� ȯ .\n");
			matrix_pointer result1 = mtranspose(first);
			matrix_pointer result2 = mtranspose(second);
			mwrite(result1);
			mwrite(result2);
		}
		else if (num == 7)
			break;
	}
	return 0;
}