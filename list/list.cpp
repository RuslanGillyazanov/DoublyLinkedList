#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "DList.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	DList q1;

	// Добавление новых узлов в конец списка
	q1.DListРushBack(10);
	q1.DListРushBack(11);
	q1.DListРushBack(12);
	q1.DListРushBack(13);

	// Удаление последнего узла из списка
	q1.DListРopBack();

	// Вставка нового узла
	q1.DListРushNth(1, 14);
	q1.DListРushNth(1, 42);
	
	// Поиск указателя на последний узел
	cout << "Указатель на последний узел: " << q1.ListgetLast() << endl;

	// Поиск указателя на узел с номером 2
	cout << "Указатель на узел с номером 2: " << q1.ListgetNth(2) << endl;

	// Удаление первого элемента с возвращением его значения:
	cout << "Удаление первого элемента с возвращением его значения:" << q1.DListРop() << endl;

	// Добавление элемента в начало списка
	q1.DListРush(9);
	q1.DListРush(8);
	q1.DListРush(100);

	// Число элементов в списке
	cout << "Число элементов в списке: " << q1.ListNodeNumber() << endl;

	// Вывод списка
	q1.Print();

	system("pause");
    return 0;
}