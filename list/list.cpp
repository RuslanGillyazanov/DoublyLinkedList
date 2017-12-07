#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

typedef struct DNode
{
	DNode *next;
	DNode *pnext;
	int value;
} DNode;

class DList {

	// ������, �����
	DNode *head, *last;

public:

	// ������������
	DList(DNode *next_, DNode *pnext_, int value_);
	DList(DNode *next_, DNode *pnext_);
	DList(DNode *next_);
	DList();

	// ����������
	~DList();

	// ����������� ����� ��������� � ������
	int ListNodeNumber();
	// ���������� �������� � ���������� data � ������ ������
	void DList�ush(int data);
	// �������� ������� �������� � ������������ ��� ��������
	int DList�op();
	// ����� ��������� �� ���� � ������� n
	DNode * ListgetNth(int n);
	// ����� ��������� �� ��������� ������� ������
	DNode * ListgetLast();
	// ���������� ������ �������� � ����������� data � ����� ������
	void DList�ushBack(int data);
	// �������� ���������� �������� �� ������
	bool DList�opBack();
	// ������� ������ �������� � ����������� data ����� �������� � ������� n ��� � ����� ������, ���� ��������� ������, ��� n
	void DList�ushNth(int n, int data);
	// �������� �� ���������� �������� � ������� n, n > 0
	int DListDeleteNth(int n);
	// ����� ������
	void Print();
};

// ����������� � ����������� next, pnext, value
DList::DList(DNode *next_, DNode *pnext_, int value_) {
	head->next = next_;
	head->pnext = pnext_;
	head->value = value_;
}

DList::DList(DNode *next_, DNode *pnext_) {
	head->next = next_;
	head->pnext = pnext_;
	head->value = 0;
}

DList::DList(DNode *next_) {
	head->next = next_;
	head->pnext = NULL;
	head->value = 0;
}

DList::DList() {
	head = NULL;
}

DList::~DList() {

	// ���� �� ������ ����������
	if (!head) return;

	// � ����� ������� ��������������� �� ���������
	for (last = head->next; last; last = last->next) {
		// ���������� �� ������� ����� �.� ������ ����������
		delete last->pnext;
		head = last;
	}

	delete head;
}

int DList::ListNodeNumber() {
	// ����������� ����� ��������� � ������

	int counter = 0; // �������� � ������������� �������� �����

					 // �������� ��������� �� NULL
	while (head) {
		head = head->next;
		counter++;
	}

	return counter;
}

void DList::DList�ush(int data) {
	// ���������� �������� � ���������� data � ������ ������

	DNode *tmp = new DNode(); // �������� ������ �������� ���� DNode

	if (head == NULL) {
		tmp->value = data;
		head = tmp;
	}
	else {
		tmp->next = head; // ������� �������� ��������� �� ������ � ���� tmp
		tmp->value = data; // ���������� ���� tmp �������� data

		head->pnext = tmp; // ������� ��������� ��������� � ����, ������� �� tmp
		head = tmp; // ���������� ������ �������� ��������� head (�� tmp)
	}
}

int DList::DList�op() {
	// �������� ������� �������� � ������������ ��� ��������

	if (head == NULL) return -1;
	int val = head->value; // ���������� ����������� �� ������� ����

	if (head->next) {
		head = head->next; // ���������� ��������� *head
		free(head->pnext); // �������� ������� ����
		head->pnext = NULL; // ��������� ��������� ��������� ������� ����
	}
	else {
		free(head);
	}

	return val; // ����������� ����������� ���������� ������� ����
}

DNode * DList::ListgetNth(int n) {
	// ����� ��������� �� ���� � ������� n

	int counter = 0; // �������� � ������������� �������� �����

					 // �������� ������ ���� � ��� �������
	while (counter < n && head) {
		head = head->next;
		counter++;
	}

	return head;
}

DNode * DList::ListgetLast() {
	// ����� ��������� �� ��������� ������� ������

	if (!head) return NULL; // �������� ������� ������ � ������� NULL

							// ����������� �� ���������� �� �������� NULL
	while (head->next) {
		head = head->next;
	}

	return head;
}

void DList::DList�ushBack(int data) {
	// ���������� ������ �������� � ����������� data � ����� ������

	DNode *last = ListgetLast(); //����������� ��������� �� ������������ ��������� ����
	DNode *tmp = new DNode; // �������� � ��������� ������ ��� ����� ���� tmp

	tmp->next = NULL; // ������ ������� ��������� � tmp
	tmp->value = data; // ������ �������� � tmp

	if (last != NULL) {
		last->next = tmp; // ������ ��������� �� tmp � ���� � ���������� *last
		tmp->pnext = last; // ������ ��������� �� last � ���� � ���������� tmp->pnext
	}
	else {
		head = tmp;
		head->pnext = NULL;
	}
}

bool DList::DList�opBack() {
	// �������� ���������� �������� �� ������ 

	// �������� ������� ������ � ������� false
	if (!head) return false;

	// ����� ���������� ��������
	int nm1 = ListNodeNumber() - 2;

	// ������� � pr_last ��������� �� ������������� �������
	DNode *pr_last = ListgetNth(nm1);

	if (pr_last->next == NULL) {
		// � ������ ��� ���� �������, ���� ������ ���������
		free(head);
		head = NULL;
	}
	else {
		// � ������ ���� ����� ������ ��������
		free(pr_last->next);
		pr_last->next = NULL;
	}

	return true;
}

void DList::DList�ushNth(int n, int data) {
	/*
	������� ������ �������� � ����������� data ����� �������� � ������� n
	��� � ����� ������, ���� ��������� ������, ��� n
	*/

	// ����������� ����� ���������
	int  nl = ListNodeNumber();

	// ��������� ������, ��� n - ���������� �������� � ����� ������
	if (n > nl - 1)
		DList�ushBack(data);
	else {
		// ��������� ������, ��� n - ���������� ����� ����

		DNode *tmp = new DNode; // ���������� � ��������� ������ ��� ����� ���� tmp
		DNode *pr = ListgetNth(n); // ����� ��������� �� ������� � ������� n 

		pr->next->pnext = tmp; // ��������� ��������� � �������� (n + 1)->pnext �� tmp
		tmp->next = pr->next; // ������� ��������� � �������� n �� tmp
		tmp->pnext = pr; // ��������� ��������� � tmp->pnext �� pr
		tmp->value = data; // ������������ ��������
		pr->next = tmp; // ��������� ��������� � �������� n �� tmp
	};
}

int DList::DListDeleteNth(int n) {
	// �������� �� ���������� �������� � ������� n, n > 0

	// ����������� ����� ���������
	int nl = ListNodeNumber();

	// ��������� ������, ��� n+1 - ������� (-1)
	if (n > nl - 1) return -1;
	else {
		// ����� ����� nl �� ������, ��� n + 1 � �������� �� �������

		// ���������� � ����� ��������� �� ������� � ������� n-1
		DNode *pr = ListgetNth(n - 1);

		// ���������� � ������ ��������� �� ����, ��������� �� ����� n
		DNode *tmp = pr->next->next;

		free(pr->next); // �������� ���� n

		if (tmp == NULL)
			pr->next = NULL; // ���� n ��� ���������
		else {
			// ���� n � �� ��� ���������
			pr->next = tmp; // ����� ������� ��������� �� ���������� ���� npr
			tmp->pnext = pr; // ����� ��������� ��������� �� ����������� ���� nnx
		}
	}
}

void DList::Print() {
	// ����� ������
	while (head) {

		cout << "�����: " << head << endl;
		cout << "��������: " << head->value << endl;
		cout << "��������� ����: " << head->next << endl;
		cout << "���������� ����: " << head->pnext << endl;
		cout << "----------------" << endl;

		head = head->next;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int data; // �������� ����
	int n; // ����� ����
	int result_int = 0; // ��������� ������ �������
	DNode * result_link = NULL; // ��������� ���������� �������

	DList DoublyLinkedList;

	// TODO: ����� ������� ��� ������ � ��������������� �������

	// ����������� ������
	DoublyLinkedList.Print();

	system("pause");
    return 0;
}