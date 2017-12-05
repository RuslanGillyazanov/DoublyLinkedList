#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

typedef struct DNode {
	int value;
	DNode *next;
	DNode *pnext;
} DNode;

// Конструктор
void ListContructor(DNode **head) {
	(*head) = NULL;
}

// Проверка на пустоту
bool ListEmpty(DNode *head) {
	if (head == NULL) return true;
	return false;
}

// Определение числа элементов в списке
int ListNodeNumber(DNode *head) {
	int counter = 0; // Описание и инициализация счетчика узлов

	// Проверка указателя на NULL
	while (head) {
		head = head->next;
		counter++;
	}

	return counter;
}

// Добавление элемента с содержимым data в начало списка
void DListРush(DNode **head, int data) {
	DNode *tmp = new DNode; // Создание нового элемента типа DNode

	if ((*head) == NULL) {
		tmp->next = NULL;
		tmp->pnext = NULL;
		tmp->value = data;
		(*head) = tmp;
	}
	else {
		tmp->next = (*head); // Вставка прежнего указателя на список в узел tmp
		tmp->pnext = NULL; // Вставка обратного указателя в узел tmp
		tmp->value = data; // Присвоение узлу tmp значения data

		(*head)->pnext = tmp; // Вставка обратного указателя в узел, стоящий за tmp
		(*head) = tmp; // Присвоение нового значения указателю head (на tmp)
	}
}

// Удаление первого элемента с возвращением его значения
int DListРop(DNode **head) {

	if ((*head) == NULL) return -1;
	int val = (*head)->value; // Извлечение содержимого из первого узла

	if ((*head)->next) {
		(*head) = (*head)->next; // Обновление указателя *head
		free((*head)->pnext); // Удаление первого узла
		(*head)->pnext = NULL; // Установка обратного указателя первого узла
	}
	else {
		free((*head));
	}

	return val; // Возвращение содержимого удаленного первого узла
}

// Поиск указателя на узел с номером n
DNode * ListgetNth(DNode *head, int n) {

	int counter = 0; // Описание и инициализация счетчика узлов

	// Проверка номера узла и его пустоты
	while (counter < n && head) {
		head = head->next;
		counter++;
	}

	return head;
}

// Поиск указателя на последний элемент списка
DNode * ListgetLast(DNode *head) {

	if (!head) return NULL; // Проверка пустоты списка и возврат NULL

	// Перемещение по указателям до значения NULL
	while (head->next) {
		head = head->next;
	}

	return head;
}

// Добавление нового элемента с содержанием data в конец списка
void DListРushBack(DNode **head, int data) {

	DNode *last = ListgetLast(*head); //Определение указателя на существующий последний узел
	DNode *tmp = new DNode; // Описание и выделение памяти под новый узел tmp

	tmp->next = NULL; // Запись пустого указателя в tmp
	tmp->value = data; // Запись значения в tmp

	if (last != NULL) {
		last->next = tmp; // Запись указателя на tmp в узел с указателем *last
		tmp->pnext = last; // Запись указателя на last в узел с указателем tmp->pnext
	}
	else {
		*head = tmp;
		(*head)->pnext = NULL;
	}
}

// Удаление последнего элемента из списка 
bool DListРopBack(DNode *head) {

	// Проверка пустоты списка и возврат false
	if (!head) return false;
	
	// Номер последнего элемента
	int nm1 = ListNodeNumber(head) - 2;

	// Засылка в pr_last указателя на предпоследний элемент
	DNode *pr_last = ListgetNth(head, nm1);

	// В списке был один элемент, весь список очищается
	if (pr_last->next == NULL) {
		free(head);
		head = NULL;
	}
	// В списке было более одного элемента
	else {
		free(pr_last->next);
		pr_last->next = NULL;
	}

	return true;
}

/* 
	Вставка нового элемента с содержанием data после элемента с номером n
	или в конец списка, если элементов меньше, чем n
*/
void DListРushNth(DNode *head, int n, int data) {

	// Определение числа элементов
	int  nl = ListNodeNumber(head);

	// Элементов меньше, чем n - добавление элемента в конец списка
	if (n > nl - 1)
		DListРushBack(&head, data);
	else {
		// Элементов больше, чем n - добавление между ними

		DNode *tmp = new DNode; // Объявление и выделение памяти под новый узел tmp
		DNode *pr = ListgetNth(head, n); // Поиск указателя на элемент с номером n 

		pr->next->pnext = tmp; // Установка указателя с элемента (n + 1)->pnext на tmp
		tmp->next = pr->next; // Перенос указателя с элемента n на tmp
		tmp->pnext = pr; // Установка указателя с tmp->pnext на pr
		tmp->value = data; // Присваивание значения
		pr->next = tmp; // Установка указателя с элемента n на tmp
	};
}

// Удаление не начального элемента с номером n, n > 0
int  DListDeleteNth(DNode *head, int n) {

	// Определение числа элементов
	int nl = ListNodeNumber(head); 

	// Элементов меньше, чем n+1 - возврат (-1)
	if (n > nl - 1) return -1;
	else {
		// Число узлов nl не меньше, чем n + 1 – удаление из массива
		DNode *pr = ListgetNth(head, n - 1); // Объявление и поиск указателя на элемент с номером n-1

		// Объявление и расчет указателя на узел, следующий за узлом n
		DNode *tmp = pr->next->next;

		free(pr->next); // Удаление узла n

		if (tmp == NULL)
			pr->next = NULL; // Узел  n был последним
		else {
			// Узел  n – не был последним
			pr->next = tmp; // Смена прямого указателя на предыдущем узле npr
			tmp->pnext = pr; // Смена обратного указателя на последующем узле nnx
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int data; // Значение узла
	int n; // Номер узла
	int result_int; // Для результата работы функции
	DNode * result_link; // Указатель результата функции

	DNode *head = new DNode;

	ListContructor(&head);

	// TODO: Вызов функций для работы с двунаправленным списком

	// Отображение списка
	while (head) {

		cout << "Адрес: " << head << endl;
		cout << "Значение: " << head->value << endl;
		cout << "Следующий узел: " << head->next << endl;
		cout << "Предыдущий узел: " << head->pnext << endl;
		cout << "----------------" << endl;

		head = head->next;
	}

	system("pause");
    return 0;
}