#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50 // 최대 행렬 크기
typedef enum {
	head,
	entry
} tagfield; // 헤더 노드와 엔트리 노드를 나타내기 위한 tag 필드
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;
typedef struct matrix_node {
	matrix_pointer down; // column(열)의 노드들을 리스트로 연결할 때 사용
	matrix_pointer right; // row(행)의 노드들을 리스트로 연결할 때 사용
	tagfield tag;
	union {
		matrix_pointer next; // 헤드 노드들을 연결할 때 사용
		entry_node entry;
	} u;
} matrix_node;
matrix_pointer hdnode[MAX_SIZE]; // 헤드 노드의 총 개수를 MAX_SIZE

matrix_pointer new_node(void) { // 새 행렬 노드를 생성하여 반환하는 함수
	matrix_pointer temp;
	temp = (matrix_pointer)malloc(sizeof(matrix_node));
	return temp;
}

matrix_pointer mread(void) { // 행렬을 읽어 연결 표현으로 구성, 전역 보조 배열 hdnode가 사용됨
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	matrix_pointer temp, last, node;
	printf("Enter the number of rows, columns, and number of nonzero terms: ");
	scanf("%d%d%d", &numRows, &numCols, &numTerms); // 먼저 행의 수, 열의 수, 0이 아닌 항의 수 입력
	numHeads = (numCols > numRows) ? numCols : numRows;
	// 헤더 노드 리스트에 대한 헤더 노드를 생성
	node = new_node(); node->tag = entry;
	node->u.entry.row = numRows;
	node->u.entry.col = numCols;
	if (!numHeads)
		node->right = node;
	else { // 헤더 노드들을 초기화
		for (i = 0; i < numHeads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0]; // 현재 행의 마지막 노드
		for (i = 0; i < numTerms; i++) {
			printf("Enter row, column and value: ");
			scanf("%d%d%d", &row, &col, &value);
			if (row > currentRow) { // 현재 행을 종료
				last->right = hdnode[currentRow];
				currentRow = row; last = hdnode[row];
			}
			temp = new_node();
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp; // 행 리스트에 연결
			last = temp;
			hdnode[col]->u.next->down = temp; // 열 리스트에 연결
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[currentRow]; // 마지막 행을 종료
		for (i = 0; i < numCols; i++) // 모든 열 리스트를 종료
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < numHeads - 1; i++) // 모든 헤더 노드들을 연결
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[numHeads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}

void mwrite(matrix_pointer node) { // 행렬을 행 우선으로 출력한다.
	int i;
	matrix_pointer temp, head = node->right;
	// 행렬의 차원
	printf("\n numRows = %d, numCols = %d \n", node->u.entry.row, node->u.entry.col);
	printf(" The matrix by row, column, and value: \n\n");
	for (i = 0; i < node->u.entry.row; i++) { // 각 행에 있는 엔트리들을 출력
		for (temp = head->right; temp != head; temp = temp->right)
			printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next; // 다음 행
	}
}

matrix_pointer madd(matrix_pointer m1, matrix_pointer m2) { // 두 행렬을 더하여 반환하는 함수
	int resultHeads, i, currentRow, check = 0; // resultHeads: result의 헤드 노드 수, check: 같은 행렬의 위치에 있을 때를 체크함
	matrix_pointer result = NULL, t, temp, tmp1, tmp2; // result: 결과값의 헤더 노드 리스트에 대한 헤더 노드, t: result의 헤드 노드 초기화시 쓰이는 변수, temp: 덧셈 할때 잠시 담아두는 변수, tmp1, tmp2: 각각 m1, m2 안의 노드를 보기 위해 만들어진 변수
	matrix_pointer re_hdnode[MAX_SIZE], last, re_node; // re_hdnode[MAX_SIZE]: result 리스트를 만들기 위한 보조 배열, re_node: 결과값이 들어갈 노드를 가리키는 변수
	if (m1->u.entry.col != m2->u.entry.col || m1->u.entry.row != m2->u.entry.row) {
		printf("두 행렬의 크기가 달라서 더할 수 없습니다.\n");
		return NULL;
	}
	resultHeads = (m1->u.entry.col > m1->u.entry.row) ? m1->u.entry.col : m1->u.entry.row;
	result = new_node(); result->tag = entry;
	result->u.entry.row = m1->u.entry.row;
	result->u.entry.col = m1->u.entry.col;
	if (!resultHeads)
		result->right = result;
	else { // 결과값의 헤더 노드들을 초기화
		for (i = 0; i < resultHeads; i++) {
			t = new_node();
			re_hdnode[i] = t; re_hdnode[i]->tag = head;
			re_hdnode[i]->right = t; re_hdnode[i]->u.next = t;
		}
		currentRow = 0;
		last = re_hdnode[0]; // 현재 행의 마지막 노드

		tmp1 = m1->right;
		tmp2 = m2->right; // m1, m2의 반복문을 돌기 위해 할당
		while (!(tmp1 == m1 && tmp2 == m2)) {
			if (tmp1->tag == head) { // tmp1가 만약 head인 노드면
				if (tmp1->right == tmp1) { // 현재 행에 다른 노드가 없다면
					tmp1 = tmp1->u.next; // 다음 행으로 이동
					continue; // 다음 행에도 다른 노드가 없을 수 있으므로 continue로 생략해줌
				}
				tmp1 = tmp1->right; // 그 행에서 다음 열로 이동
			}
			if (tmp2->tag == head) { // tmp1가 만약 head인 노드면
				if (tmp2->right == tmp2) {// 현재 행에 다른 노드가 없다면
					tmp2 = tmp2->u.next; // 다음 행으로 이동
					continue; // 다음 행에도 다른 노드가 없을 수 있으므로 continue로 생략해줌
				}
				tmp2 = tmp2->right; // 그 행에서 다음 열로 이동
			}

			if (tmp1->u.entry.row < tmp2->u.entry.row) { // tmp2의 row가 더 크면
				temp = tmp1; // tmp1가 먼저이므로 temp에 넣고
				tmp1 = tmp1->right; // 다음으로 넘김
				check = 0;
			}
			else if (tmp1->u.entry.row > tmp2->u.entry.row) { // tmp1의 row가 더 크면
				temp = tmp2; // tmp2가 먼저이므로 temp에 넣고
				tmp2 = tmp2->right; // 다음으로 넘김
				check = 0;
			}
			else { // tmp1, tmp2의 row가 같다면
				if (tmp1->u.entry.col < tmp2->u.entry.col) { // tmp2의 col이 더 크면
					temp = tmp1; // tmp1가 먼저이므로 temp에 넣고
					tmp1 = tmp1->right; // 다음으로 넘김
					check = 0;
				}
				else if (tmp1->u.entry.col > tmp2->u.entry.col) { // tmp1의 col이 더 크면
					temp = tmp2; // tmp2가 먼저이므로 temp에 넣고
					tmp2 = tmp2->right; // 다음으로 넘김
					check = 0;
				}
				else { // tmp1, tmp2의 row, col이 같다면
					temp = tmp1; // 일단 tmp1의 정보를 넣어둠(나중에 값에 tmp2의 값을 더함)
					check = 1; // 행,열이 같음을 표시
				}
			}

			if (temp->u.entry.row > currentRow) { // 현재 행을 종료
				last->right = re_hdnode[currentRow];
				currentRow = temp->u.entry.row; last = re_hdnode[temp->u.entry.row];
			}
			re_node = new_node();
			re_node->tag = entry;
			re_node->u.entry.row = temp->u.entry.row;
			re_node->u.entry.col = temp->u.entry.col;
			if (check == 1) { // 행, 열이 같을 때
				re_node->u.entry.value = temp->u.entry.value + tmp2->u.entry.value; // tmp1의 값, tmp2의 값을 더함
				tmp1 = tmp1->right;
				tmp2 = tmp2->right;
			}
			else // 행, 열이 다를 때
				re_node->u.entry.value = temp->u.entry.value; // temp안에 넣어둔 값을 넣음
			last->right = re_node; // 행 리스트에 연결
			last = re_node;
			re_hdnode[temp->u.entry.col]->u.next->down = re_node; // 열 리스트에 연결
			re_hdnode[temp->u.entry.col]->u.next = re_node;

			if (tmp1->tag == head) // 만약 head면 그 행의 검사가 다 된 것이므로 다음 행으로 이동
				tmp1 = tmp1->u.next;
			if (tmp2->tag == head)
				tmp2 = tmp2->u.next;
		}
		last->right = re_hdnode[currentRow]; // 마지막 행을 종료
		for (i = 0; i < result->u.entry.col; i++) // 모든 열 리스트를 종료
			re_hdnode[i]->u.next->down = re_hdnode[i];
		for (i = 0; i < resultHeads - 1; i++) // 모든 헤더 노드들을 연결
			re_hdnode[i]->u.next = re_hdnode[i + 1];
		re_hdnode[resultHeads - 1]->u.next = result;
		result->right = re_hdnode[0];
	}
	return result;
}

matrix_pointer mtranspose(matrix_pointer node) { // 행렬을 전치 행렬로 변환하는 함수
	int resultHeads, i, currentRow; // resultHeads: result의 헤드 노드 수
	matrix_pointer result = NULL, t, temp; // result: 결과값의 헤더 노드 리스트에 대한 헤더 노드, t: result의 헤드 노드 초기화시 쓰이는 변수, temp: node를 반복문을 돌릴때 포인터로 사용하는 변수
	matrix_pointer re_hdnode[MAX_SIZE], last, re_node; // re_hdnode[MAX_SIZE]: result 리스트를 만들기 위한 보조 배열, re_node: 결과값이 들어갈 노드를 가리키는 변수

	resultHeads = (node->u.entry.col > node->u.entry.row) ? node->u.entry.col : node->u.entry.row;
	result = new_node(); result->tag = entry;
	result->u.entry.row = node->u.entry.col; // 전치이기 때문에 row와 col을 서로 바꿔서 넣음
	result->u.entry.col = node->u.entry.row;
	if (!resultHeads)
		result->right = result;
	else { // 결과값의 헤더 노드들을 초기화
		for (i = 0; i < resultHeads; i++) {
			t = new_node();
			re_hdnode[i] = t; re_hdnode[i]->tag = head;
			re_hdnode[i]->right = t; re_hdnode[i]->u.next = t;
		}
		currentRow = 0;
		last = re_hdnode[0]; // 현재 행의 마지막 노드

		temp = node->right; // node로 반복문을 돌리기 위해 할당
		while (!(temp == node)) {
			if (temp->tag == head) { // temp가 만약 head인 노드면
				if (temp->right == temp) { // 현재 행에 다른 노드가 없다면
					temp = temp->u.next; // 다음 행으로 이동
					continue; // 다음 행에도 다른 노드가 없을 수 있으므로 continue로 생략해줌
				}
				temp = temp->right; // 그 행에서 다음 열로 이동
			}
			if (temp->u.entry.col > currentRow) { // 현재 행을 종료
				last->right = re_hdnode[currentRow];
				currentRow = temp->u.entry.col; last = re_hdnode[temp->u.entry.col];
			}
			re_node = new_node();
			re_node->tag = entry;
			re_node->u.entry.row = temp->u.entry.col; // row와 col의 값을 바꿔서 넣음
			re_node->u.entry.col = temp->u.entry.row;
			re_node->u.entry.value = temp->u.entry.value;
			last->right = re_node; // 행 리스트에 연결
			last = re_node;
			re_hdnode[temp->u.entry.row]->u.next->down = re_node; // 열 리스트에 연결
			re_hdnode[temp->u.entry.row]->u.next = re_node;

			temp = temp->right; // 다음 위치로 이동
			if (temp->tag == head) // 만약 head면 그 행의 검사가 다 된 것이므로 다음 행으로 이동
				temp = temp->u.next;
		}

		last->right = re_hdnode[currentRow]; // 마지막 행을 종료
		for (i = 0; i < result->u.entry.col; i++) // 모든 열 리스트를 종료
			re_hdnode[i]->u.next->down = re_hdnode[i];
		for (i = 0; i < resultHeads - 1; i++) // 모든 헤더 노드들을 연결
			re_hdnode[i]->u.next = re_hdnode[i + 1];
		re_hdnode[resultHeads - 1]->u.next = result;
		result->right = re_hdnode[0];
	}
	return result;
}

matrix_pointer mmult(matrix_pointer m1, matrix_pointer m2) { // 두 행렬의 곱을 구하여 반환하는 함수
	int resultHeads, i, j, currentRow, row, col, value, check = 0; // resultHeads: result의 헤드 노드 수, row, col, value: 각각 곱셈 수행 시 row, col, value 값을 담기 위해 쓰임, check: 곱셈을 수행하는 중인지를 체크하는 변수
	matrix_pointer result = NULL, t, temp, tmp1, tmp2, tm_head1, tm_head2; // result: 결과값의 헤더 노드 리스트에 대한 헤더 노드, t: result의 헤드 노드 초기화시 쓰이는 변수, tmp1, tmp2: 각각 m1, m2 안의 노드를 보기 위해 만들어진 변수, tm_head1, tm_head2: m1,m2의 반복문을 돌 때 각각의 헤더 노드를 담는 변수
	matrix_pointer re_hdnode[MAX_SIZE], last, re_node; // re_hdnode[MAX_SIZE]: result 리스트를 만들기 위한 보조 배열, re_node: 결과값이 들어갈 노드를 가리키는 변수
	if (m1->u.entry.col != m2->u.entry.row) {
		printf("첫 번째 행렬의 열과 두 번째 행렬의 행의 개수가 달라 곱할 수 없습니다.\n");
		return NULL;
	}
	resultHeads = (m2->u.entry.col > m1->u.entry.row) ? m2->u.entry.col : m1->u.entry.row;
	result = new_node(); result->tag = entry;
	result->u.entry.row = m1->u.entry.row;
	result->u.entry.col = m2->u.entry.col;
	if (!resultHeads)
		result->right = result;
	else { // 결과값의 헤더 노드들을 초기화
		for (i = 0; i < resultHeads; i++) {
			t = new_node();
			re_hdnode[i] = t; re_hdnode[i]->tag = head;
			re_hdnode[i]->right = t; re_hdnode[i]->u.next = t;
		}
		currentRow = 0;
		last = re_hdnode[0]; // 현재 행의 마지막 노드

		tm_head1 = m1->right;
		tm_head2 = m2->right; // 각각의 첫번째 헤더 노드를 담고 시작
		tmp1 = m1->right;
		tmp2 = m2->right;
		for (i = 0; i < m1->u.entry.row; i++) {
			row = 0, col = 0, value = 0;
			for (j = 0; j < m2->u.entry.col; ) { // 증가는 상황에 따라 진행
				if (j == 0 && check == 0) {
					tmp1 = tm_head1->right; // 행 이동
					tmp2 = tm_head2->down; // 열 이동
				}

				if (tmp2->tag == head || tmp2->down == tmp2) { // 두번째 행렬의 해당 열에 노드가 없을 때
					check = 0;
					tm_head2 = tm_head2->u.next; // 다음 헤더 노드로 이동
					tmp2 = tm_head2->down; // 그 열에 있는 헤더 노드 다음 노드로 이동
					tmp1 = tm_head1->right;
					row = 0, col = 0, value = 0;
					j++;
				}

				if (tmp1->tag == head) {
					if (tmp1->right == tmp1) { // 첫번째 행렬의 행 노드가 없다면
						check = 0;
						break; // for문 하나 탈출
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

				if (j >= m2->u.entry.col) // j가 범위를 넘어서면 for문 탈출
					break;

				if (tmp1->u.entry.col < tmp2->u.entry.row) { // 만약 두번째 행렬의 행이 첫번째 행렬의 열보다 크면
					check = 1; // 곱셈하는 중임을 표시
					tmp1 = tmp1->right; // 첫번째 행렬의 열 노드를 다음 노드로 이동
				}
				else if (tmp1->u.entry.col > tmp2->u.entry.row) { // 만약 두번째 행렬의 행이 첫번째 행렬의 열보다 작으면
					check = 1; // 곱셈하는 중임을 표시
					tmp2 = tmp2->down; // 두번째 행렬의 행 노드를 다음 노드로 이동
				}
				else { // 만약 두번째 행렬의 행과 첫번째 행렬의 열이 같으면
					check = 1; // 곱셈하는 중임을 표시
					if (value == 0) { // 만약 현재 value가 0이라 노드를 새로 만들어야 된다면
						row = tmp1->u.entry.row;
						col = tmp2->u.entry.col;
						value = tmp1->u.entry.value * tmp2->u.entry.value; // 곱한 값을 넣음
						if (row > currentRow) { // 현재 행을 종료
							last->right = re_hdnode[currentRow];
							currentRow = row; last = re_hdnode[row];
						}
						re_node = new_node();
						re_node->tag = entry;
						re_node->u.entry.row = row;
						re_node->u.entry.col = col;
						re_node->u.entry.value = value;
						last->right = re_node; // 행 리스트에 연결
						last = re_node;
						re_hdnode[col]->u.next->down = re_node; // 열 리스트에 연결
						re_hdnode[col]->u.next = re_node;
						tmp1 = tmp1->right;
						tmp2 = tmp2->down; // 다음 노드로 이동
					}
					else { // value가 0이 아니라면
						row = tmp1->u.entry.row;
						col = tmp2->u.entry.col;
						temp = re_hdnode[row]->right; // temp로 같은 행을 찾아주고
						while (1) {
							if (temp->u.entry.col == col) { // 같은 열을 찾아서
								temp->u.entry.value += tmp1->u.entry.value * tmp2->u.entry.value; // 이미 값이 있던 위치에 새로 나온 값을 더한다.
								break;
							}
							else
								temp = temp->right; // 원하는 열이 나올때까지 찾는다.
							if (temp->tag == head) // 헤드 노드로 돌아오면 break로 탈출
								break;
						}
						tmp1 = tmp1->right;
						tmp2 = tmp2->down; // 다음 노드로 넘어간다.
					}
				}
			}

			tm_head1 = tm_head1->u.next; // 첫번째 행렬의 행 이동
			tm_head2 = m2->right; // 두번째 행렬은 다시 처음부터 이동
			check = 0;
		}

		last->right = re_hdnode[currentRow]; // 마지막 행을 종료
		for (i = 0; i < result->u.entry.col; i++) // 모든 열 리스트를 종료
			re_hdnode[i]->u.next->down = re_hdnode[i];
		for (i = 0; i < resultHeads - 1; i++) // 모든 헤더 노드들을 연결
			re_hdnode[i]->u.next = re_hdnode[i + 1];
		re_hdnode[resultHeads - 1]->u.next = result;
		result->right = re_hdnode[0];
	}
	return result;
}

void printf_menu() { // 메인 메뉴 출력 함수
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
			printf("첫 번 째  희 소 행 렬 을  입 력 하 세 요.\n");
			first = mread();
			printf("\n");
			printf("두 번 째  희 소 행 렬 을  입 력 하 세 요.\n");
			second = mread();
		}
		else if (num == 2) {
			printf("---------------------------\n");
			printf("첫 번 째  입 력 한  희 소  행 렬  출 력 . .\n");
			mwrite(first);
			printf("\n");
			printf("두 번 째  입 력 한  희 소  행 렬  출 력 . .\n");
			mwrite(second);
		}
		else if (num == 4) {
			printf("--------------------------------\n");
			printf("입 력 한  두 개 의  희 소  행 렬  더 하 기 . .\n");
			matrix_pointer result = madd(first, second);
			mwrite(result);
		}
		else if (num == 5) {
			printf("--------------------------------\n");
			printf("입 력 한  두 개 의  희 소  행 렬  곱 하 기 . .\n");
			matrix_pointer result = mmult(first, second);
			mwrite(result);
		}
		else if (num == 6) {
			printf("-------------------------------------\n");
			printf("입 력 한  희 소  행 렬 을  전 치  행 렬 로  변 환 .\n");
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