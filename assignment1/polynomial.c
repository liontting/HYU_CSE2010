#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _poly_node *poly_pointer; // ����� pointer �ڷ���
typedef struct _poly_node { // ����� ����
	int coef; // ���� ���
	int expon; // ���� ����
	poly_pointer link; // ���� ��(���� ���)�� ���� ������
} poly_node;

poly_pointer PolynomialRead() { // ���׽��� �Է� �޾� ���� ���� ����Ʈ�� ��ȯ�ϴ� �Լ�
	int i = 0, check = 2, buho = 0, num = 0, check1 = 0; // i: �Է� ���� ���ڿ��� ���� ���Ḯ��Ʈ�� �ֱ� ���� �˻縦 �� ���� index, check: ���ڸ� ������ ���� ���ڰ� �����̾����� ������ üũ(ó���� 1�� �����ǰ� x�� �� �� �����Ƿ� 2�� �ʱ�ȭ), buho: ��ȣ, num: ���� ����, check1: ���� ���ڰ� ���ڿ����� üũ
	char poly[100] = { 0, }; // ���׽� ���ڿ� �Է� �޴� �迭
	poly_pointer header, tail;
	header = (poly_pointer)malloc(sizeof(poly_node)); // header �����Ҵ�
	header->coef = -1;
	header->expon = -1;
	header->link = header; // ������� header�� �ʱ�ȭ
	tail = header; // tail�� header�� ���� ��ġ�� �ʱ�ȭ
	scanf(" %[^\n]s", poly);
	while (poly[i] != '\0') { // ���׽� ���ڿ��� ���� ������
		if (poly[i] == 'x') { // 'x'�� ������ ��
			poly_pointer tmp;
			tmp = (poly_pointer)malloc(sizeof(poly_node)); // ���� ������ ��� �����Ҵ�
			if (check1 == 0) // ���� x ���� ���ڴ� ������ ��, ���� ����� ���ڸ� 1�� �������
				num = 1;
			if (buho == 1) // ���� ��ȣ�� -���ٸ�, ���� ����� -�� �ٿ���
				num = -num;
			tmp->coef = num; // ���ο� ��忡 ��� ����
			tmp->expon = 1; // ����� ���� ��츦 ����� �̸� 1 �־����
			tmp->link = header; // ���ο� ����� link�� header�� ����Ű�� ��
			tail->link = tmp; // ���� tail�̴� ����� link�� ���ο� ��带 ����Ű�� ��
			tail = tmp; // tail�� ���ο� ���� �ű�
			num = 0; // ���� ���ڸ� ��� ������ �ʱ�ȭ
			check = 3; // x�� �������� ǥ��
			check1 = 0; // ���ڰ� �ƴ� ���ڸ� �������� ǥ��
		}
		else if (poly[i] == ' ') { // ������ ������ ��
			if (check == 3) // ���� ���ڰ� x���ٸ� ������ 1�̹Ƿ�
				num = 1;
			if (poly[i - 1] != '+' && poly[i - 1] != '-') // ���� ���� ���ڰ� ��ȣ�� �ƴϸ�
				tail->expon = num; // tail�� �����κп� ���� ����
			num = 0; // ���� ���ڸ� ��� ������ �ʱ�ȭ
			check1 = 0; // ���ڰ� �ƴ� ���ڸ� �������� ǥ��
		}
		else if (poly[i] == '+' || poly[i] == '-') { // ��ȣ�� ������ ��
			check = 2; // ��ȣ �������� ǥ���ϴ� ������ check ������ 2�� ����
			if (poly[i] == '+') // +�� ��
				buho = 0;
			else // -�� ��
				buho = 1;
			check1 = 0; // ���ڰ� �ƴ� ���ڸ� �������� ǥ��
		}
		else if (poly[i] != '^') { // ���ڸ� ������ ��
			num = num * 10 + (poly[i] - '0'); // ���ڿ��� ���ڸ� int�� ������ �־���(���� �ڸ� ���ڰ� �Ѿ �� ������ ��� �����ִ� ������ �ڵ带 ����)
			check1 = 1; // ���ڸ� �������� ǥ��
		}
		else { // ^�� ������ ��
			check = 1;
			check1 = 0; // ���ڰ� �ƴ� ���ڸ� �������� ǥ��
		}
		i++; // ���� ���� üũ�� ���� i ����
	}
	if (check == 3) // ���� ������� ���ٸ�
		return header; // header ��ȯ
	if (check == 1) { // ���� ���� �κ����� �����ٸ�
		tail->expon = num;
		return header;
	}
	// ������� �ִ� ���
	poly_pointer tmp;
	tmp = (poly_pointer)malloc(sizeof(poly_node)); // ���� ������ ��� �����Ҵ�
	if (buho == 1) // ���� ��ȣ�� -���ٸ�, ���� ����� -�� �ٿ���
		num = -num;
	tmp->coef = num; // ���ο� ��忡 ��� ����
	tmp->expon = 0; // ������ 0�� ����
	tmp->link = header; // ���ο� ����� link�� header�� ����Ű�� ��
	tail->link = tmp; // ���� tail�̴� ����� link�� ���ο� ��带 ����Ű�� ��
	tail = tmp; // tail�� ���ο� ���� �ű�
	return header; // header ��ȯ
}

void PolynomialWrite(poly_pointer polynomial) { // �Է��� ���׽��� ����ϴ� �Լ�
	poly_pointer tmp; // ����� ��带 �湮�ϴ� ������ �ӽ� ������
	tmp = polynomial->link; // header�� ���� ������ ����
	// ó���� +�� ��ȣ�� �����Ƿ� �ݺ��� ���� ���� ���
	if (tmp->expon == 0) { // ������� ��
		if (tmp->coef > 0)
			printf("%d", tmp->coef);
		else
			printf("- %d", -tmp->coef);
	}
	else if (tmp->coef == 1) { // ����� 1�̸� ��� ����
		if (tmp->expon == 1) // ������ 1�̸� ���� ����
			printf("x ");
		else
			printf("x^%d ", tmp->expon);
	}
	else if (tmp->coef == -1) { // ����� -1�̸� ��� ����
		if (tmp->expon == 1) // ������ 1�̸� ���� ����
			printf("-x ");
		else
			printf("-x^%d ", tmp->expon);
	}
	else { // ����� 1�̳� -1�� �ƴ� ��
		if (tmp->expon == 1) // ������ 1�̸� ���� ����
			printf("%dx ", tmp->coef);
		else
			printf("%dx^%d ", tmp->coef, tmp->expon);
	}
	tmp = tmp->link; // ���� ���� �̵�
	for (; tmp->expon != -1; tmp = tmp->link) { // header(������ -1�� �ʱ�ȭ) ������ ���� ���� �̵��ϴ� �ݺ���
		if (tmp->coef > 0) { // ����� ����̸�
			if (tmp->expon == 0) // ������� ��
				printf("+ %d", tmp->coef);
			else if (tmp->expon == 1 && tmp->coef == 1) // ���, ������ 1�̸� �� �� ����
				printf("+ x ");
			else if (tmp->expon == 1) // ������ 1�̸� ���� ����
				printf("+ %dx ", tmp->coef);
			else if (tmp->coef == 1) // ����� 1�̸� ��� ����
				printf("+ x^%d ", tmp->expon);
			else // ����׵� �ƴϰ� ����� 1�� �ƴҶ�
				printf("+ %dx^%d ", tmp->coef, tmp->expon);
		}
		else if (tmp->coef < 0) { // ����� �����̸�(0�ϸ��� ������..)
			if (tmp->expon == 0) // ������� ��
				printf("- %d", -tmp->coef);
			else if (tmp->expon == 1 && tmp->coef == -1) // ����� -1, ������ 1�̸� �� �� ����
				printf("- x ");
			else if (tmp->expon == 1) // ������ 1�̸� ���� ����
				printf("- %dx ", -tmp->coef);
			else if (tmp->coef == -1) // ����� -1�̸� 1 ����
				printf("- x^%d ", tmp->expon);
			else // ����׵� �ƴϰ� ����� -1�� �ƴҶ�
				printf("- %dx^%d ", -tmp->coef, tmp->expon);
		}
	}
}

poly_pointer mult(poly_pointer first, poly_pointer second) { // �� ���׽� a(first), b(second)�� ���� ���Ͽ� ��ȯ�ϴ� �Լ�
	poly_pointer f, s, result, rtail, temp, pcheck, check; // f,s: ù��°, �ι�° ���׽��� for���� ������ ���̴� ����, result: ���� ����� ��� ����, rtail: ���� ����� ���� �� ���̴� �����κ�, temp: �ӽó��, pcheck, check: result���� ���� ������ ���� �� ó���� �� ���̴� ����
	f = first->link;
	s = second->link;
	result = (poly_pointer)malloc(sizeof(poly_node)); // ���׽��� ���� ����� ���� result �����Ҵ�
	result->coef = -1;
	result->expon = -1;
	result->link = result;
	rtail = result; // result�� rtail �⺻ ����

	for (; f->expon != -1; f = f->link) { // ù��° ���׽� �� �� �ݺ�
		for (; s->expon != -1; s = s->link) { // �ι�° ���׽� �� �� �ݺ�
			temp = (poly_pointer)malloc(sizeof(poly_node));
			temp->coef = f->coef * s->coef;
			temp->expon = f->expon + s->expon; // �ӽ� ��忡 �� ������ �������� ����
			if (rtail == result) { // ���� result�� �� ���� ����� ���ٸ�
				temp->link = result;
				rtail->link = temp;
				rtail = temp; // �ӽ� ���� �׳� �־���
			}
			else { // ���� result�� �� ���� ����� �ִٸ�
				pcheck = result; // check�� ���� ���� ����
				check = result->link; // result�� �˻��ϱ� ���� ����
				int ch = 0; // for���� break�� Ż���ߴ��� Ȯ���ϴ� �뵵�� ����
				for (; check->expon != -1; check = check->link) { // result�� �ִ� �׵�� temp�� ������ ���� ���� �ִ��� ã�� ���� ������ �ݺ���
					if (check->expon == temp->expon) { // ���� ������ ���ٸ�
						check->coef += temp->coef; // result�� �ش� ���� ����� temp�� ����� ����
						ch = 1;
						break; // �ݺ��� Ż��
					}
					else if (check->expon < temp->expon) { // ���� check �׺��� temp ���� ������ �� ũ�ٸ�(temp�� �� �տ� ���� �Ѵ�.)
						temp->link = pcheck->link; // check ���� ����� link ������ temp�� link�� ����
						pcheck->link = temp; // check ���� ����� link�� temp�� �����鼭 ����
						ch = 1;
						break; // �ݺ��� Ż��
					}
					pcheck = check; // pcheck�� check�� ���� ���� ����� ����
				}
				if (ch == 0) { // ���� �ݺ����� ���ư��� ���� break�� �Ͼ�� �ʾҴٸ�
					temp->link = result;
					rtail->link = temp;
					rtail = temp; // rtail ������ �ְ� rtail�� �ű�
				}
				else if (check->coef == 0) { // ���� ����� 0�� �Ǿ��ٸ�(������ ���� ���� 0�� �� �� �־� break�� Ż���� ��츸 ������ check�� �˻��ϸ� ��)
					poly_pointer tmp = check; // �� ��ġ�� �ӽ÷� �����ϰ�
					pcheck->link = check->link; // ���� link�� check�� link ������ �ְ�
					if (pcheck->link == result) // ���� �װ� ������ ��忴�ٸ�
						rtail = pcheck; // rtail�� �ٽ� �������ְ�
					free(tmp); // ������
				}
			}
		}
		s = second->link; // �ι�° �ݺ����� ó������ �ٽ� ������ ���� �ʱ�ȭ
	}
	return result;
}

int divide(poly_pointer first, poly_pointer second, poly_pointer quotient, poly_pointer remainder) { // �� ���׽� a(first), b(second)�� ���Ͽ� a / b �� ���ϴ� �Լ� ( ��� �������� ���� )
	printf("a = ");
	PolynomialWrite(first);
	printf("   b = ");
	PolynomialWrite(second);
	printf("\n");
	int coef, expon; // ��� ���� ����� ������ ��Ƶδ� ����
	poly_pointer f, s, temp, qtail, rtail, mu, mtail, pcheck, check;
	f = first->link;
	s = second->link;
	if (f->expon < s->expon) // ���� �ι�° ���׽��� ������ �� ũ�ٸ� ������ ����
		return 0;

	quotient = (poly_pointer)malloc(sizeof(poly_node));
	quotient->coef = -1;
	quotient->expon = -1;
	quotient->link = quotient; // ������� quotient�� �ʱ�ȭ
	qtail = quotient; // qtail�� quotient�� ���� ��ġ�� �ʱ�ȭ
	remainder = (poly_pointer)malloc(sizeof(poly_node));
	remainder->coef = -1;
	remainder->expon = -1;
	remainder->link = remainder; // ������� remainder�� �ʱ�ȭ
	rtail = remainder; // rtail�� remainder�� ���� ��ġ�� �ʱ�ȭ

	for (; f->expon != -1; f = f->link) { // remainder�� first�� ���� ���׽��� ����
		temp = (poly_pointer)malloc(sizeof(poly_node));
		temp->coef = f->coef;
		temp->expon = f->expon;
		temp->link = remainder;
		rtail->link = temp;
		rtail = temp;
	}
	/*
	�ϴ� �������� f�� ����
	�������� ù �װ� s�� ù ���� �񱳸� ���� ���� ���ϰ�
	s ��ü�� ���� ���� �������� ����
	������ �� ù �װ� s�� ù ���� ���ؼ� �������� ù ���� ������
	�񱳸� ���� ���� �߰�, �������� ����
	�������� ù ���� �۾��������� �ݺ�
	����ü ��ü�� ����� ������ int�� ����� ���� ������ ������ �� ���� ����� ����� ������ ������ ��츸 �ִٰ� ������
	*/
	mu = (poly_pointer)malloc(sizeof(poly_node)); // �׶��׶� ���� ��(���׽� ��� ����)
	mu->coef = -1;
	mu->expon = -1;
	mtail = (poly_pointer)malloc(sizeof(poly_node)); // ���� ���׽��� ���� ���
	mu->link = mtail;
	mtail->link = mu;

	while (remainder->link->expon >= s->expon) { // �������� ������ ������ second�� �������� ������ ����(���� ū ���׽ĺ��� �ϳ��ϳ� ���� ����)
		coef = remainder->link->coef / s->coef; // ���� ���ϱ� ���� ������ �� ���� ū ���� ��� / second �� ���� ū ���� ����� ���Ѵ�.
		expon = remainder->link->expon - s->coef; // ���� ���ϱ� ���� ������ �� ���� ū ���� ���� - second �� ���� ū ���� ������ ���Ѵ�.
		temp = (poly_pointer)malloc(sizeof(poly_node)); // �ӽ� ������ ���� ������ ��´�.
		temp->coef = coef;
		temp->expon = expon;
		temp->link = quotient; // ���ο� ����� link�� quotient�� ����Ű�� ��
		qtail->link = temp; // ���� qtail�̴� ����� link�� ���ο� ��带 ����Ű�� ��
		qtail = temp; // qtail�� ���ο� ���� �ű�

		mtail->coef = coef; // mu�� ��� ����
		mtail->expon = expon; // mu�� ���� ����
		poly_pointer tmp = mult(mu, second), t, pt; // tmp = �׶��׶� ���� ��(���׽�)�� second�� ��, ptmp = tmp�� �ݺ����� ������ �� ���� ��带 ������ ����
		pcheck = remainder; // check�� ���� ��带 ������ ���� ����
		check = remainder->link; // remainder for�� ������ ���� ���� ����
		for (; check->expon != -1; check = check->link) { // remainder���� tmp(mu*second)�� ���ֱ� ���� ���� for��
			pt = tmp;
			t = tmp->link;
			for (; t->expon != -1; t = t->link) {
				if (check->expon == t->expon) { // ������ ���� ��
					if (check->coef == t->coef) { // ������� ������
						poly_pointer tp = check; // �� ��ġ�� �ӽ÷� �����ϰ�
						pcheck->link = check->link; // ���� link�� check�� link ������ �ְ�
						if (check->link == remainder) // ���� �װ� ������ ��忴�ٸ�
							rtail = pcheck; // rtail�� �ٽ� �������ְ�
						free(tp); // ������
						check = pcheck; // check�� ���� ����� ��ġ�� ����
						poly_pointer tp1 = t; // tmp�� �����Ƿ� ������, �� ��ġ�� �ӽ÷� �����ϰ�
						pt->link = t->link; // ���� link�� tmp�� link ������ �ְ�
						free(tp1); // ������
						t = pt->link;
						if (check->link->expon == -1 && check->expon == -1 && t->expon != -1) { // ���࿡ tmp ���� �����ִµ� remainder�� ���� ���� ���ٸ�
							temp = (poly_pointer)malloc(sizeof(poly_node)); // �ϳ� ���� �������
							temp->coef = -t->coef; // ����
							temp->expon = t->expon;
							temp->link = pcheck->link;
							pcheck->link = temp; // pcheck�� ���� ������ �� ������
							poly_pointer tp = t; // tmp�� �����Ƿ� ������, �� ��ġ�� �ӽ÷� �����ϰ�
							pt->link = t->link; // ���� link�� tmp�� link ������ �ְ�
							free(tp); // ������
						}
						break;
					}
					else { // ����� �ٸ� ���
						check->coef -= t->coef; // ���ش�.
						poly_pointer tp1 = t; // tmp�� �����Ƿ� ������, �� ��ġ�� �ӽ÷� �����ϰ�
						pt->link = t->link; // ���� link�� tmp�� link ������ �ְ�
						free(tp1); // ������
						break;
					}
				}
				else if (check->expon < t->expon) { // ���ִ� �ǵ� ���� ������ ���ٸ�
					temp = (poly_pointer)malloc(sizeof(poly_node)); // �ϳ� ���� �������
					temp->coef = -t->coef; // ����
					temp->expon = t->expon;
					temp->link = pcheck->link;
					pcheck->link = temp; // pcheck�� ���� ������ �� ������
					poly_pointer tp = t; // tmp�� �����Ƿ� ������, �� ��ġ�� �ӽ÷� �����ϰ�
					pt->link = t->link; // ���� link�� tmp�� link ������ �ְ�
					free(tp); // ������
					break;
				}
				pt = t;
			}
			pcheck = check;
		}
		if (mu->expon == 0)
			break;
	}
	printf("divide ��� (a / b)\n");
	printf("-> �� : ");
	PolynomialWrite(quotient);
	printf(",  ������ : ");
	PolynomialWrite(remainder);
	printf("\n");
	return 1;
}

void eval(poly_pointer polynomial, double f) { // ���׽��� �Լ� f(x)�� �����ϰ�, ���� �� c�� ���Ͽ� f(c)�� ���� ����ϴ� �Լ�
	double sum = 0; // ���� ���� ��� ����
	double temp = 1; // ������ x�� f�� �ְ� ���� ����� ���� �ӽ÷� ��� ����
	poly_pointer tmp; // ��带 �湮�ϴ� ������ �ӽ� ������
	tmp = polynomial->link; // header�� ���� ������ ����
	for (; tmp->expon != -1; tmp = tmp->link) { // header(������ -1�� �ʱ�ȭ) ������ ���� ���� �̵��ϴ� �ݺ���
		for (int expon = tmp->expon; expon > 0; expon--) // ������ŭ �ݺ��� ����
			temp *= f;
		sum = sum + tmp->coef * temp;
		temp = 1; // �ӽ÷� ��� ���� �ʱ�ȭ
	}
	printf("%f�� ���� ���: %f\n", f, sum);
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
		printf("divide ���� (a / b)\n");
	return 0;
}