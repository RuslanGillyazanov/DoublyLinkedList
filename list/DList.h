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
	// Голова, хвост
	DNode *head = new DNode();

public:

	// Конструкторы
	DList(DNode *next_, DNode *pnext_, int value_);
	DList(DNode *next_, DNode *pnext_);
	DList(DNode *next_);
	DList();

	// Деструктор
	~DList();

	// Определение числа элементов в списке
	int ListNodeNumber();
	// Добавление элемента с содержимым data в начало списка
	void DListРush(int data);
	// Удаление первого элемента с возвращением его значения
	int DListРop();
	// Поиск указателя на узел с номером n
	DNode * ListgetNth(int n);
	// Поиск указателя на последний элемент списка
	DNode * ListgetLast();
	// Добавление нового элемента с содержанием data в конец списка
	void DListРushBack(int data);
	// Удаление последнего элемента из списка
	bool DListРopBack();
	// Вставка нового элемента с содержанием data после элемента с номером n или в конец списка, если элементов меньше, чем n
	void DListРushNth(int n, int data);
	// Удаление не начального элемента с номером n, n > 0
	int DListDeleteNth(int n);
	// Вывод списка
	void Print();
	// Получение ссылки на следующий узел
	DNode * getNext();
	// Получение ссылки на предыдущий узел
	DNode * getPNext();
	// Получение ключа узла
	int getKey();
};

