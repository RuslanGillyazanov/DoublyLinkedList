#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

typedef struct DNode {
	int value;
	DNode *next;
	DNode *pnext;
} DNode;

// �����������
void ListContructor(DNode **head) {
	(*head) = NULL;
}

// �������� �� �������
bool ListEmpty(DNode *head) {
	if (head == NULL) return true;
	return false;
}

// ����������� ����� ��������� � ������
int ListNodeNumber(DNode *head) {
	int counter = 0; //�������� � ������������� �������� �����

	// �������� ��������� �� NULL
	while (head) {
		head = head->next;
		counter++;
	}

	return counter;
}

// ���������� �������� � ���������� data � ������ ������
void DList�ush(DNode **head, int data) {
	DNode *tmp = new DNode; // �������� ������ �������� ���� DNode

	if ((*head) == NULL) {
		tmp->next = NULL;
		tmp->pnext = NULL;
		tmp->value = data;
		(*head) = tmp;
	}
	else {
		tmp->next = (*head); // ������� �������� ��������� �� ������ � ���� tmp
		tmp->pnext = NULL; // ������� ��������� ��������� � ���� tmp
		tmp->value = data; // ���������� ���� tmp �������� data

		(*head)->pnext = tmp; // ������� ��������� ��������� � ����, ������� �� tmp
		(*head) = tmp; // ���������� ������ �������� ��������� head (�� tmp)
	}
}

// �������� ������� �������� � ������������ ��� ��������
int DList�op(DNode *head) {

	if (head == NULL) return -1;
	int val = head->value; //���������� ����������� �� ������� ����

	if (head->next) {
		head = head->next; // ���������� ��������� *head
		free(head->pnext); // �������� ������� ����
		head->pnext = NULL; // ��������� ��������� ��������� ������� ����
	}
	else {
		free(head);
	}

	return val; //����������� ����������� ���������� ������� ����
}

// ����� ��������� �� ���� � ������� n
DNode * ListgetNth(DNode *head, int n) {

	int counter = 0; // �������� � ������������� �������� �����

	// �������� ������ ���� � ��� �������
	while (counter < n && head) {
		head = head->next;
		counter++;
	}

	return head;
}

// ����� ��������� �� ��������� ������� ������
DNode * ListgetLast(DNode *head) {

	if (!head) return NULL; //�������� ������� ������ � ������� NULL

	// ����������� �� ���������� �� �������� NULL
	while (head->next) {
		head = head->next;
	}

	return head;
}

// ���������� ������ �������� � ����������� data � ����� ������
void DList�ushBack(DNode **head, int data) {

	DNode *last = ListgetLast(*head); //����������� ��������� �� ������������ ��������� ����
	DNode *tmp = new DNode;// �������� � ��������� ������ ��� ����� ���� tmp

	tmp->next = NULL;//������ ������� ��������� � tmp
	tmp->value = data;//������ �������� � tmp

	if (last != NULL) {
		last->next = tmp; // ������ ��������� �� tmp � ���� � ���������� *last
		tmp->pnext = last; // ������ ��������� �� last � ���� � ���������� tmp->pnext
	}
	else {
		*head = tmp;
		(*head)->pnext = NULL;
	}
}

// �������� ���������� �������� �� ������ 
bool DList�opBack(DNode *head) {

	// �������� ������� ������ � ������� false
	if (!head) return false;
	
	// ����� ���������� ��������
	int nm1 = ListNodeNumber(head) - 2;

	// ������� � pr_last ��������� �� ������������� �������
	DNode *pr_last = ListgetNth(head, nm1);

	if (pr_last->next == NULL) {
		free(head);
		head = NULL;
	} // � ������ ��� ���� �������, ���� ������ ���������
	else {
		free(pr_last->next);
		pr_last->next = NULL;
	} // � ������ ���� ����� ������ ��������
	return true;
}

/* 
	������� ������ �������� � ����������� data ����� �������� � ������� n
	��� � ����� ������, ���� ��������� ������, ��� n
*/
void DList�ushNth(DNode *head, int n, int data) {

	// ����������� ����� ���������
	int  nl = ListNodeNumber(head);

	// ��������� ������, ��� n - ���������� �������� � ����� ������
	if (n > nl - 1)
		DList�ushBack(&head, data);
	else {
		// ��������� ������, ��� n - ���������� ����� ����
		DNode *tmp = new DNode; // ���������� � ��������� ������ ��� ����� ���� tmp
		DNode *pr = ListgetNth(head, n); // ����� ��������� �� ������� � ������� n 

		pr->next->pnext = tmp;
		tmp->next = pr->next; // ������� ��������� � �������� n �� tmp
		tmp->pnext = pr;
		tmp->value = data; // ������������ ��������
		pr->next = tmp; // ��������� ��������� � �������� n �� tmp
	};
}

// �������� �� ���������� �������� � ������� n, n > 0
int  DListDeleteNth(DNode *head, int n) {

	// ����������� ����� ���������
	int nl = ListNodeNumber(head); 

	// ��������� ������, ��� n+1 - ������� (-1)
	if (n > nl - 1) return -1;
	else {
		// ����� ����� nl �� ������, ��� n + 1 � �������� �� �������
		DNode *pr = ListgetNth(head, n - 1); // ���������� � ����� ��������� �� ������� � ������� n-1

		// ���������� � ������ ��������� �� ����, ��������� �� ����� n
		DNode *tmp = pr->next->next;

		free(pr->next); // �������� ���� n

		if (tmp == NULL)
			pr->next = NULL; // ����  n ��� ���������
		else {
			// ����  n � �� ��� ���������
			pr->next = tmp;//����� ������� ��������� �� ���������� ���� npr
			tmp->pnext = pr;//����� ��������� ��������� �� ����������� ���� nnx
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int menuChoiceNumber = 0; // ����� ������ ����
	int data = 0; // �������� ����
	int n = 0; // ����� ����
	int result_int;
	DNode * result_link;

	DNode *head = new DNode;

	ListContructor(&head);

	while (head) {

		cout << head << endl;
		cout << head->value << endl;
		cout << head->next << endl;
		cout << head->pnext << endl;
		cout << "-------" << endl;

		head = head->next;
	}

	system("pause");
    return 0;
}