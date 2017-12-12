#include "stdafx.h"
#include "DList.h"
#include <iostream>

DList::DList(DNode *next_, DNode *pnext_, int value_) {
	DNode *temp = new DNode;

	temp->next = next_;
	temp->pnext = pnext_;
	temp->value = value_;

	this->head = temp;
}

DList::DList(DNode *next_, DNode *pnext_) {
	DNode *temp = new DNode;

	temp->next = next_;
	temp->pnext = pnext_;
	temp->value = 0;

	this->head = temp;
}

DList::DList(DNode *next_) {
	DNode *temp = new DNode;

	temp->next = next_;
	temp->pnext = NULL;
	temp->value = 0;

	this->head = temp;
}

DList::DList() {
	DNode *temp;

	temp = NULL;

	this->head = temp;
}

DList::~DList() {

	while (head)
	{
		DNode *temp = head; // Создаем временный узел
		head = head->next; // Присваиваем ему указатель на следующий
		delete temp; // Удаляем его
	}

	head = NULL;
}

bool DList::ListEmpty() {
	// Проверка списка на пустоту
	DNode *headCurrent = head;

	if (!headCurrent) return true;

	return false;
}

int DList::ListNodeNumber() {
	// Определение числа элементов в списке

	int counter = 0; // Описание и инициализация счетчика узлов

	DNode *headCurrent = head;

	// Проверка указателя на NULL
	while (headCurrent) {
		counter++;
		headCurrent = headCurrent->next;
	}

	return counter;
}

void DList::DListРush(int data) {
	// Добавление элемента с содержимым data в начало списка

	DNode *headCurrent = head;

	DNode *tmp = new DNode(); // Создание нового элемента типа DNode

	if (headCurrent == NULL) {
		tmp->value = data; // Присваиваем новому элементу значение data
		headCurrent = tmp; // Меняем указатель узла headCurrent на tmp
	}
	else {
		tmp->next = headCurrent; // Вставка прежнего указателя на список в узел tmp
		tmp->value = data; // Присвоение узлу tmp значения data

		headCurrent->pnext = tmp; // Вставка обратного указателя в узел, стоящий за tmp
		head = tmp; // Устанавливаем узел tmp на начало списка
		headCurrent = head; // Присвоение нового значения указателю headCurrent (на head)
	}
}

int DList::DListРop() {
	// Удаление первого элемента с возвращением его значения
	DNode **headCurrent = &head;

	if (!headCurrent) return -1; // Проверка на пустоту

	int value = (*headCurrent)->value; // Извлечение содержимого из первого узла

	if ((*headCurrent)->next) {
		*headCurrent = (*headCurrent)->next; // Обновление указателя *headCurrent
		free((*headCurrent)->pnext); // Удаление первого узла
		(*headCurrent)->pnext = NULL; // Установка обратного указателя первого узла
	}
	else {
		free(*headCurrent); // Удаляем headCurrent
	}

	return value; // Возвращение содержимого удаленного первого узла
}

DNode * DList::ListgetNth(int n) {
	// Поиск указателя на узел с номером n
	DNode *headCurrent = head;

	int counter = 0; // Описание и инициализация счетчика узлов

	// Проверка номера узла и его пустоты
	while (counter < n && headCurrent) {
		headCurrent = headCurrent->next;
		counter++;
	}

	return headCurrent;
}

DNode * DList::ListgetLast() {
	// Поиск указателя на последний элемент списка
	DNode *headCurrent = head;

	if (!headCurrent) return NULL; // Проверка пустоты списка и возврат NULL

	// Перемещение по указателям до значения NULL
	while (headCurrent->next) {
		headCurrent = headCurrent->next;
	}

	return headCurrent;
}

void DList::DListРushBack(int data) {
	// Добавление нового элемента с содержанием data в конец списка

	DNode *last = ListgetLast(); //Определение указателя на существующий последний узел
	DNode *tmp = new DNode(); // Описание и выделение памяти под новый узел tmp

	tmp->value = data; // Запись значения в tmp

	if (last != NULL) {
		last->next = tmp; // Запись указателя на tmp в узел с указателем *last
		tmp->pnext = last; // Запись указателя на last в узел с указателем tmp->pnext
	}
	else {
		head = tmp; // Если элемент один записываем tmp на первое место
	}
}

bool DList::DListРopBack() {
	// Удаление последнего элемента из списка 
	DNode *headCurrent = head;

	// Проверка пустоты списка и возврат false
	if (!headCurrent) return false;

	// Номер последнего элемента
	int nm1 = ListNodeNumber() - 2;

	// Засылка в pr_last указателя на предпоследний элемент
	DNode *pr_last = ListgetNth(nm1);

	if (pr_last->next == NULL) {
		// В списке был один элемент, весь список очищается
		free(headCurrent);
		headCurrent = NULL;
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
			pr->next = tmp; // Смена прямого указателя на предыдущем узле pr
			tmp->pnext = pr; // Смена обратного указателя на последующем узле tmp
		}
	}
}

void DList::Print() {
	// Вывод списка
	DNode *headCurrent = head;

	while (headCurrent) {

		std::cout << "Адрес: " << headCurrent << std::endl;
		std::cout << "Значение: " << headCurrent->value << std::endl;
		std::cout << "Следующий узел: " << headCurrent->next << std::endl;
		std::cout << "Предыдущий узел: " << headCurrent->pnext << std::endl;
		std::cout << "----------------" << std::endl;

		headCurrent = headCurrent->next;
	}
}