#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _poly_node *poly_pointer; // 노드의 pointer 자료형
typedef struct _poly_node { // 노드의 정의
	int coef; // 항의 계수
	int expon; // 항의 지수
	poly_pointer link; // 다음 항(다음 노드)에 대한 포인터
} poly_node;

poly_pointer PolynomialRead() { // 다항식을 입력 받아 원형 연결 리스트로 변환하는 함수
	int i = 0, check = 2, buho = 0, num = 0, check1 = 0; // i: 입력 받은 문자열을 원형 연결리스트에 넣기 위해 검사를 할 때의 index, check: 숫자를 제외한 이전 문자가 무엇이었는지 간단히 체크(처음엔 1이 생략되고 x가 올 수 있으므로 2로 초기화), buho: 부호, num: 넣을 숫자, check1: 이전 문자가 숫자였는지 체크
	char poly[100] = { 0, }; // 다항식 문자열 입력 받는 배열
	poly_pointer header, tail;
	header = (poly_pointer)malloc(sizeof(poly_node)); // header 동적할당
	header->coef = -1;
	header->expon = -1;
	header->link = header; // 여기까지 header의 초기화
	tail = header; // tail을 header와 같은 위치로 초기화
	scanf(" %[^\n]s", poly);
	while (poly[i] != '\0') { // 다항식 문자열이 끝날 때까지
		if (poly[i] == 'x') { // 'x'를 만났을 때
			poly_pointer tmp;
			tmp = (poly_pointer)malloc(sizeof(poly_node)); // 새로 삽입할 노드 동적할당
			if (check1 == 0) // 만약 x 전에 숫자는 없었을 시, 넣을 계수의 숫자를 1로 만들어줌
				num = 1;
			if (buho == 1) // 만약 부호가 -였다면, 넣을 계수에 -를 붙여줌
				num = -num;
			tmp->coef = num; // 새로운 노드에 계수 넣음
			tmp->expon = 1; // 상수항 없는 경우를 대비해 미리 1 넣어놓음
			tmp->link = header; // 새로운 노드의 link가 header를 가리키게 함
			tail->link = tmp; // 원래 tail이던 노드의 link가 새로운 노드를 가리키게 함
			tail = tmp; // tail을 새로운 노드로 옮김
			num = 0; // 넣을 숫자를 담는 변수를 초기화
			check = 3; // x를 만났음을 표시
			check1 = 0; // 숫자가 아닌 문자를 만났음을 표시
		}
		else if (poly[i] == ' ') { // 공백을 만났을 때
			if (check == 3) // 이전 문자가 x였다면 지수는 1이므로
				num = 1;
			if (poly[i - 1] != '+' && poly[i - 1] != '-') // 띄어쓰기 전의 문자가 부호가 아니면
				tail->expon = num; // tail의 지수부분에 값을 넣음
			num = 0; // 넣을 숫자를 담는 변수를 초기화
			check1 = 0; // 숫자가 아닌 문자를 만났음을 표시
		}
		else if (poly[i] == '+' || poly[i] == '-') { // 부호를 만났을 때
			check = 2; // 부호 만났음을 표시하는 뜻으로 check 변수를 2로 설정
			if (poly[i] == '+') // +일 때
				buho = 0;
			else // -일 때
				buho = 1;
			check1 = 0; // 숫자가 아닌 문자를 만났음을 표시
		}
		else if (poly[i] != '^') { // 숫자를 만났을 때
			num = num * 10 + (poly[i] - '0'); // 문자였던 숫자를 int형 변수에 넣어줌(십의 자리 숫자가 넘어갈 수 있으니 계속 더해주는 식으로 코드를 구현)
			check1 = 1; // 숫자를 만났음을 표시
		}
		else { // ^를 만났을 때
			check = 1;
			check1 = 0; // 숫자가 아닌 문자를 만났음을 표시
		}
		i++; // 다음 문자 체크를 위한 i 증가
	}
	if (check == 3) // 만약 상수항이 없다면
		return header; // header 반환
	if (check == 1) { // 만약 지수 부분으로 끝났다면
		tail->expon = num;
		return header;
	}
	// 상수항이 있는 경우
	poly_pointer tmp;
	tmp = (poly_pointer)malloc(sizeof(poly_node)); // 새로 삽입할 노드 동적할당
	if (buho == 1) // 만약 부호가 -였다면, 넣을 계수에 -를 붙여줌
		num = -num;
	tmp->coef = num; // 새로운 노드에 계수 넣음
	tmp->expon = 0; // 차수에 0을 넣음
	tmp->link = header; // 새로운 노드의 link가 header를 가리키게 함
	tail->link = tmp; // 원래 tail이던 노드의 link가 새로운 노드를 가리키게 함
	tail = tmp; // tail을 새로운 노드로 옮김
	return header; // header 반환
}

void PolynomialWrite(poly_pointer polynomial) { // 입력한 다항식을 출력하는 함수
	poly_pointer tmp; // 출력할 노드를 방문하는 목적의 임시 포인터
	tmp = polynomial->link; // header의 다음 노드부터 시작
	// 처음에 +면 부호가 없으므로 반복문 전에 먼저 출력
	if (tmp->expon == 0) { // 상수항일 때
		if (tmp->coef > 0)
			printf("%d", tmp->coef);
		else
			printf("- %d", -tmp->coef);
	}
	else if (tmp->coef == 1) { // 계수가 1이면 계수 생략
		if (tmp->expon == 1) // 지수가 1이면 지수 생략
			printf("x ");
		else
			printf("x^%d ", tmp->expon);
	}
	else if (tmp->coef == -1) { // 계수가 -1이면 계수 생략
		if (tmp->expon == 1) // 지수가 1이면 지수 생략
			printf("-x ");
		else
			printf("-x^%d ", tmp->expon);
	}
	else { // 계수가 1이나 -1이 아닐 때
		if (tmp->expon == 1) // 지수가 1이면 지수 생략
			printf("%dx ", tmp->coef);
		else
			printf("%dx^%d ", tmp->coef, tmp->expon);
	}
	tmp = tmp->link; // 다음 노드로 이동
	for (; tmp->expon != -1; tmp = tmp->link) { // header(지수를 -1로 초기화) 전까지 다음 노드로 이동하는 반복문
		if (tmp->coef > 0) { // 계수가 양수이면
			if (tmp->expon == 0) // 상수항일 때
				printf("+ %d", tmp->coef);
			else if (tmp->expon == 1 && tmp->coef == 1) // 계수, 지수가 1이면 둘 다 생략
				printf("+ x ");
			else if (tmp->expon == 1) // 지수가 1이면 지수 생략
				printf("+ %dx ", tmp->coef);
			else if (tmp->coef == 1) // 계수가 1이면 계수 생략
				printf("+ x^%d ", tmp->expon);
			else // 상수항도 아니고 계수도 1이 아닐때
				printf("+ %dx^%d ", tmp->coef, tmp->expon);
		}
		else if (tmp->coef < 0) { // 계수가 음수이면(0일리는 없으니..)
			if (tmp->expon == 0) // 상수항일 때
				printf("- %d", -tmp->coef);
			else if (tmp->expon == 1 && tmp->coef == -1) // 계수가 -1, 지수가 1이면 둘 다 생략
				printf("- x ");
			else if (tmp->expon == 1) // 지수가 1이면 지수 생략
				printf("- %dx ", -tmp->coef);
			else if (tmp->coef == -1) // 계수가 -1이면 1 생략
				printf("- x^%d ", tmp->expon);
			else // 상수항도 아니고 계수도 -1이 아닐때
				printf("- %dx^%d ", -tmp->coef, tmp->expon);
		}
	}
}

poly_pointer mult(poly_pointer first, poly_pointer second) { // 두 다항식 a(first), b(second)의 곱을 구하여 반환하는 함수
	poly_pointer f, s, result, rtail, temp, pcheck, check; // f,s: 첫번째, 두번째 다항식의 for문을 돌릴때 쓰이는 변수, result: 곱셈 결과를 담는 변수, rtail: 곱셈 결과를 담을 때 쓰이는 꼬리부분, temp: 임시노드, pcheck, check: result에서 같은 지수를 가진 것 처리할 때 쓰이는 변수
	f = first->link;
	s = second->link;
	result = (poly_pointer)malloc(sizeof(poly_node)); // 다항식의 곱셈 결과를 담을 result 동적할당
	result->coef = -1;
	result->expon = -1;
	result->link = result;
	rtail = result; // result와 rtail 기본 설정

	for (; f->expon != -1; f = f->link) { // 첫번째 다항식 각 항 반복
		for (; s->expon != -1; s = s->link) { // 두번째 다항식 각 항 반복
			temp = (poly_pointer)malloc(sizeof(poly_node));
			temp->coef = f->coef * s->coef;
			temp->expon = f->expon + s->expon; // 임시 노드에 각 두항의 곱셈값을 넣음
			if (rtail == result) { // 만약 result에 한 개의 결과도 없다면
				temp->link = result;
				rtail->link = temp;
				rtail = temp; // 임시 값을 그냥 넣어줌
			}
			else { // 만약 result에 한 개라도 결과가 있다면
				pcheck = result; // check의 이전 노드로 쓰임
				check = result->link; // result를 검사하기 위해 만듦
				int ch = 0; // for문을 break로 탈출했는지 확인하는 용도의 변수
				for (; check->expon != -1; check = check->link) { // result에 있는 항들과 temp의 지수가 같은 것이 있는지 찾기 위해 돌리는 반복문
					if (check->expon == temp->expon) { // 만약 지수가 같다면
						check->coef += temp->coef; // result의 해당 항의 계수에 temp의 계수를 더함
						ch = 1;
						break; // 반복문 탈출
					}
					else if (check->expon < temp->expon) { // 현재 check 항보다 temp 항의 지수가 더 크다면(temp가 그 앞에 들어가야 한다.)
						temp->link = pcheck->link; // check 이전 노드의 link 정보를 temp의 link에 넣음
						pcheck->link = temp; // check 이전 노드의 link에 temp를 넣으면서 연결
						ch = 1;
						break; // 반복문 탈출
					}
					pcheck = check; // pcheck를 check의 이전 노드로 만들기 위함
				}
				if (ch == 0) { // 만약 반복문이 돌아가는 동안 break가 일어나지 않았다면
					temp->link = result;
					rtail->link = temp;
					rtail = temp; // rtail 다음에 넣고 rtail을 옮김
				}
				else if (check->coef == 0) { // 만약 계수가 0이 되었다면(지수가 같을 때만 0이 될 수 있어 break로 탈출한 경우만 가능해 check만 검사하면 됨)
					poly_pointer tmp = check; // 그 위치를 임시로 저장하고
					pcheck->link = check->link; // 이전 link에 check의 link 정보를 넣고
					if (pcheck->link == result) // 만약 그게 마지막 노드였다면
						rtail = pcheck; // rtail도 다시 설정해주고
					free(tmp); // 삭제함
				}
			}
		}
		s = second->link; // 두번째 반복문을 처음부터 다시 돌리기 위해 초기화
	}
	return result;
}

int divide(poly_pointer first, poly_pointer second, poly_pointer quotient, poly_pointer remainder) { // 두 다항식 a(first), b(second)에 대하여 a / b 를 구하는 함수 ( 몫과 나머지를 구함 )
	printf("a = ");
	PolynomialWrite(first);
	printf("   b = ");
	PolynomialWrite(second);
	printf("\n");
	int coef, expon; // 계산 도중 계수와 지수를 담아두는 변수
	poly_pointer f, s, temp, qtail, rtail, mu, mtail, pcheck, check;
	f = first->link;
	s = second->link;
	if (f->expon < s->expon) // 만약 두번째 다항식의 차수가 더 크다면 나누기 실패
		return 0;

	quotient = (poly_pointer)malloc(sizeof(poly_node));
	quotient->coef = -1;
	quotient->expon = -1;
	quotient->link = quotient; // 여기까지 quotient의 초기화
	qtail = quotient; // qtail을 quotient와 같은 위치로 초기화
	remainder = (poly_pointer)malloc(sizeof(poly_node));
	remainder->coef = -1;
	remainder->expon = -1;
	remainder->link = remainder; // 여기까지 remainder의 초기화
	rtail = remainder; // rtail을 remainder와 같은 위치로 초기화

	for (; f->expon != -1; f = f->link) { // remainder에 first와 같은 다항식을 넣음
		temp = (poly_pointer)malloc(sizeof(poly_node));
		temp->coef = f->coef;
		temp->expon = f->expon;
		temp->link = remainder;
		rtail->link = temp;
		rtail = temp;
	}
	/*
	일단 나머지에 f를 넣음
	나머지의 첫 항과 s의 첫 항의 비교를 통해 몫을 구하고
	s 전체와 몫을 곱해 나머지를 줄임
	나머지 중 첫 항과 s의 첫 항을 비교해서 나머지의 첫 항이 높으면
	비교를 통해 몫을 추가, 나머지를 줄임
	나머지의 첫 항이 작아질때까지 반복
	구조체 자체가 계수와 지수를 int로 만들어 놨기 때문에 나누기 할 때도 결과가 계수와 지수가 정수인 경우만 있다고 가정함
	*/
	mu = (poly_pointer)malloc(sizeof(poly_node)); // 그때그때 나눌 몫(단항식 담는 변수)
	mu->coef = -1;
	mu->expon = -1;
	mtail = (poly_pointer)malloc(sizeof(poly_node)); // 실제 단항식이 담기는 노드
	mu->link = mtail;
	mtail->link = mu;

	while (remainder->link->expon >= s->expon) { // 나머지의 지수가 나누는 second의 지수보다 작으면 종료(제일 큰 단항식부터 하나하나 몫을 구함)
		coef = remainder->link->coef / s->coef; // 몫을 구하기 위해 나머지 중 제일 큰 항의 계수 / second 중 제일 큰 항의 계수를 구한다.
		expon = remainder->link->expon - s->coef; // 몫을 구하기 위해 나머지 중 제일 큰 항의 지수 - second 중 제일 큰 항의 지수를 구한다.
		temp = (poly_pointer)malloc(sizeof(poly_node)); // 임시 변수에 몫의 정보를 담는다.
		temp->coef = coef;
		temp->expon = expon;
		temp->link = quotient; // 새로운 노드의 link가 quotient를 가리키게 함
		qtail->link = temp; // 원래 qtail이던 노드의 link가 새로운 노드를 가리키게 함
		qtail = temp; // qtail을 새로운 노드로 옮김

		mtail->coef = coef; // mu의 계수 저장
		mtail->expon = expon; // mu의 지수 저장
		poly_pointer tmp = mult(mu, second), t, pt; // tmp = 그때그때 나눌 몫(단항식)과 second의 곱, ptmp = tmp를 반복문을 돌릴때 그 이전 노드를 저장해 놓음
		pcheck = remainder; // check의 이전 노드를 저장해 놓는 변수
		check = remainder->link; // remainder for문 돌리기 위해 만든 변수
		for (; check->expon != -1; check = check->link) { // remainder에서 tmp(mu*second)를 빼주기 위한 이중 for문
			pt = tmp;
			t = tmp->link;
			for (; t->expon != -1; t = t->link) {
				if (check->expon == t->expon) { // 지수가 같을 때
					if (check->coef == t->coef) { // 계수까지 같으면
						poly_pointer tp = check; // 그 위치를 임시로 저장하고
						pcheck->link = check->link; // 이전 link에 check의 link 정보를 넣고
						if (check->link == remainder) // 만약 그게 마지막 노드였다면
							rtail = pcheck; // rtail도 다시 설정해주고
						free(tp); // 삭제함
						check = pcheck; // check를 이전 노드의 위치로 보냄
						poly_pointer tp1 = t; // tmp는 썼으므로 삭제함, 그 위치를 임시로 저장하고
						pt->link = t->link; // 이전 link에 tmp의 link 정보를 넣고
						free(tp1); // 삭제함
						t = pt->link;
						if (check->link->expon == -1 && check->expon == -1 && t->expon != -1) { // 만약에 tmp 값이 남아있는데 remainder에 남은 값이 없다면
							temp = (poly_pointer)malloc(sizeof(poly_node)); // 하나 새로 만들어줌
							temp->coef = -t->coef; // 뺄셈
							temp->expon = t->expon;
							temp->link = pcheck->link;
							pcheck->link = temp; // pcheck를 통해 연결을 잘 지어줌
							poly_pointer tp = t; // tmp는 썼으므로 삭제함, 그 위치를 임시로 저장하고
							pt->link = t->link; // 이전 link에 tmp의 link 정보를 넣고
							free(tp); // 삭제함
						}
						break;
					}
					else { // 계수는 다른 경우
						check->coef -= t->coef; // 빼준다.
						poly_pointer tp1 = t; // tmp는 썼으므로 삭제함, 그 위치를 임시로 저장하고
						pt->link = t->link; // 이전 link에 tmp의 link 정보를 넣고
						free(tp1); // 삭제함
						break;
					}
				}
				else if (check->expon < t->expon) { // 빼주는 건데 같은 지수가 없다면
					temp = (poly_pointer)malloc(sizeof(poly_node)); // 하나 새로 만들어줌
					temp->coef = -t->coef; // 뺄셈
					temp->expon = t->expon;
					temp->link = pcheck->link;
					pcheck->link = temp; // pcheck를 통해 연결을 잘 지어줌
					poly_pointer tp = t; // tmp는 썼으므로 삭제함, 그 위치를 임시로 저장하고
					pt->link = t->link; // 이전 link에 tmp의 link 정보를 넣고
					free(tp); // 삭제함
					break;
				}
				pt = t;
			}
			pcheck = check;
		}
		if (mu->expon == 0)
			break;
	}
	printf("divide 결과 (a / b)\n");
	printf("-> 몫 : ");
	PolynomialWrite(quotient);
	printf(",  나머지 : ");
	PolynomialWrite(remainder);
	printf("\n");
	return 1;
}

void eval(poly_pointer polynomial, double f) { // 다항식을 함수 f(x)로 생각하고, 정수 값 c에 대하여 f(c)의 값을 출력하는 함수
	double sum = 0; // 최종 답을 담는 변수
	double temp = 1; // 미지수 x에 f를 넣고 제곱 계산한 값을 임시로 담는 변수
	poly_pointer tmp; // 노드를 방문하는 목적의 임시 포인터
	tmp = polynomial->link; // header의 다음 노드부터 시작
	for (; tmp->expon != -1; tmp = tmp->link) { // header(지수를 -1로 초기화) 전까지 다음 노드로 이동하는 반복문
		for (int expon = tmp->expon; expon > 0; expon--) // 지수만큼 반복문 돌림
			temp *= f;
		sum = sum + tmp->coef * temp;
		temp = 1; // 임시로 담는 변수 초기화
	}
	printf("%f를 넣은 결과: %f\n", f, sum);
}

int main() {
	poly_pointer p1, p2, result, quotient = NULL, remainder = NULL;
	p1 = PolynomialRead();
	p2 = PolynomialRead();
	PolynomialWrite(p1);
	printf("\n");
	eval(p1, 0.5);
	result = mult(p1, p2);
	PolynomialWrite(result);
	printf("\n");
	if (!divide(p1, p2, quotient, remainder))
		printf("divide 실패 (a / b)\n");
	return 0;
}