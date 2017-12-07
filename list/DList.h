#pragma once

typedef struct DNode
{
	DNode *next;
	DNode *pnext;
	int value;

	DNode() {
		this->next = NULL;
		this->pnext = NULL;
		this->value = 0;
	}

} DNode;

class DList
{
	// ������, �����
	DNode *head, *last = new DNode();

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
	// ��������� ������ �� ��������� ����
	DNode * getNext();
	// ��������� ������ �� ���������� ����
	DNode * getPNext();
	// ��������� ����� ����
	int getKey();
};

