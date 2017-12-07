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

	// Голова, хвост
	DNode *head, *last;

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
};

// Конструктор с параметрами next, pnext, value
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

	// Если он вообще существует
	if (!head) return;

	// В цикле пройдем последовательно по элементам
	for (last = head->next; last; last = last->next) {
		// Освобождая их соседей сзади т.е убирая предыдущие
		delete last->pnext;
		head = last;
	}

	delete head;
}

int DList::ListNodeNumber() {
	// Определение числа элементов в списке

	int counter = 0; // Описание и инициализация счетчика узлов

					 // Проверка указателя на NULL
	while (head) {
		head = head->next;
		counter++;
	}

	return counter;
}

void DList::DListРush(int data) {
	// Добавление элемента с содержимым data в начало списка

	DNode *tmp = new DNode(); // Создание нового элемента типа DNode

	if (head == NULL) {
		tmp->value = data;
		head = tmp;
	}
	else {
		tmp->next = head; // Вставка прежнего указателя на список в узел tmp
		tmp->value = data; // Присвоение узлу tmp значения data

		head->pnext = tmp; // Вставка обратного указателя в узел, стоящий за tmp
		head = tmp; // Присвоение нового значения указателю head (на tmp)
	}
}

int DList::DListРop() {
	// Удаление первого элемента с возвращением его значения

	if (head == NULL) return -1;
	int val = head->value; // Извлечение содержимого из первого узла

	if (head->next) {
		head = head->next; // Обновление указателя *head
		free(head->pnext); // Удаление первого узла
		head->pnext = NULL; // Установка обратного указателя первого узла
	}
	else {
		free(head);
	}

	return val; // Возвращение содержимого удаленного первого узла
}

DNode * DList::ListgetNth(int n) {
	// Поиск указателя на узел с номером n

	int counter = 0; // Описание и инициализация счетчика узлов

					 // Проверка номера узла и его пустоты
	while (counter < n && head) {
		head = head->next;
		counter++;
	}

	return head;
}

DNode * DList::ListgetLast() {
	// Поиск указателя на последний элемент списка

	if (!head) return NULL; // Проверка пустоты списка и возврат NULL

							// Перемещение по указателям до значения NULL
	while (head->next) {
		head = head->next;
	}

	return head;
}

void DList::DListРushBack(int data) {
	// Добавление нового элемента с содержанием data в конец списка

	DNode *last = ListgetLast(); //Определение указателя на существующий последний узел
	DNode *tmp = new DNode; // Описание и выделение памяти под новый узел tmp

	tmp->next = NULL; // Запись пустого указателя в tmp
	tmp->value = data; // Запись значения в tmp

	if (last != NULL) {
		last->next = tmp; // Запись указателя на tmp в узел с указателем *last
		tmp->pnext = last; // Запись указателя на last в узел с указателем tmp->pnext
	}
	else {
		head = tmp;
		head->pnext = NULL;
	}
}

bool DList::DListРopBack() {
	// Удаление последнего элемента из списка 

	// Проверка пустоты списка и возврат false
	if (!head) return false;

	// Номер последнего элемента
	int nm1 = ListNodeNumber() - 2;

	// Засылка в pr_last указателя на предпоследний элемент
	DNode *pr_last = ListgetNth(nm1);

	if (pr_last->next == NULL) {
		// В списке был один элемент, весь список очищается
		free(head);
		head = NULL;
	}
	else {
		// В списке было более одного элемента
		free(pr_last->next);
		pr_last->next = NULL;
	}

	return true;
}

void DList::DListРushNth(int n, int data) {
	/*
	Вставка нового элемента с содержанием data после элемента с номером n
	или в конец списка, если элементов меньше, чем n
	*/

	// Определение числа элементов
	int  nl = ListNodeNumber();

	// Элементов меньше, чем n - добавление элемента в конец списка
	if (n > nl - 1)
		DListРushBack(data);
	else {
		// Элементов больше, чем n - добавление между ними

		DNode *tmp = new DNode; // Объявление и выделение памяти под новый узел tmp
		DNode *pr = ListgetNth(n); // Поиск указателя на элемент с номером n 

		pr->next->pnext = tmp; // Установка указателя с элемента (n + 1)->pnext на tmp
		tmp->next = pr->next; // Перенос указателя с элемента n на tmp
		tmp->pnext = pr; // Установка указателя с tmp->pnext на pr
		tmp->value = data; // Присваивание значения
		pr->next = tmp; // Установка указателя с элемента n на tmp
	};
}

int DList::DListDeleteNth(int n) {
	// Удаление не начального элемента с номером n, n > 0

	// Определение числа элементов
	int nl = ListNodeNumber();

	// Элементов меньше, чем n+1 - возврат (-1)
	if (n > nl - 1) return -1;
	else {
		// Число узлов nl не меньше, чем n + 1 – удаление из массива

		// Объявление и поиск указателя на элемент с номером n-1
		DNode *pr = ListgetNth(n - 1);

		// Объявление и расчет указателя на узел, следующий за узлом n
		DNode *tmp = pr->next->next;

		free(pr->next); // Удаление узла n

		if (tmp == NULL)
			pr->next = NULL; // Узел n был последним
		else {
			// Узел n – не был последним
			pr->next = tmp; // Смена прямого указателя на предыдущем узле npr
			tmp->pnext = pr; // Смена обратного указателя на последующем узле nnx
		}
	}
}

void DList::Print() {
	// Вывод списка
	while (head) {

		cout << "Адрес: " << head << endl;
		cout << "Значение: " << head->value << endl;
		cout << "Следующий узел: " << head->next << endl;
		cout << "Предыдущий узел: " << head->pnext << endl;
		cout << "----------------" << endl;

		head = head->next;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int data; // Значение узла
	int n; // Номер узла
	int result_int = 0; // Результат работы функции
	DNode * result_link = NULL; // Указатель результата функции

	DList DoublyLinkedList;

	// TODO: Вызов функций для работы с двунаправленным списком

	// Отображение списка
	DoublyLinkedList.Print();

	system("pause");
    return 0;
}