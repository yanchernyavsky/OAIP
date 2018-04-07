// Lab04.cpp : Defines the entry point for the console application.
//Однонаправленный список.

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Spis1 {			//--Декларация однонаправленного списка--//
	int info;			//
	Spis1 *next;		//
}*begin, *end, *t;		//Указатели на начало и конец
						//--Декларация прототипов функций пользователя--//
void Create_Spis1(Spis1**, Spis1**, int);		// Функция создания первого элемента
void View_Spis1(int, Spis1*);					// Функция просмотра двунаправленного списка
void Del_All(Spis1**);							// Функция очистки памяти
void Task(Spis1**, Spis1**);					// Функция замены местами крайних элементов
void addelem(Spis1**, Spis1**, int);
int main()
{
	int in, kod;
	Spis1 *begin = NULL;
	Spis1 *end = NULL;
	while (true) {
		cout << "\n\tCreate - 1.\n\tView   - 2.\n\tDel    - 3.\n\tTask    -5\n\tEXIT   - 0.\n\t";
		cin >> kod;
		switch (kod)
		{
		case 1:
			cout << "Info = "; cin >> in;
			Create_Spis1(&begin, &end, in);
			cout << "Create = " << in << endl;
			break;
		case 2:
			if (!begin) {
				cout << "Stack is Empty!" << endl;
				break;
			}
				t = begin;
				cout << "--SPISOK--" << endl;
			View_Spis1(kod, t);
			break;
		case 3:
			Del_All(&begin);
			cout << "Memory is Free!" << endl;
			break;
		case 4:
			cout << "Enter info: "; cin >> in;
			addelem(&begin, &end, in);
			break;
		case 5: 
			cout << "Task 4" << endl;
			Task(&begin, &end);
			break;
		case 0:
			if (begin != NULL)
				Del_All(&begin);
			return 0;						//Выход(EXIT)
			break;
		}
	}

	return 0;
}

//--Функция создания первого элемента--//
void Create_Spis1(Spis1 **b, Spis1 **e, int in) {
	Spis1 *t = new Spis1;
	t->info = in;		// Формирование информационной части
	t->next = NULL;		// Формирование адресной части
	if (*b == NULL) 		// Формирование первого элемента
		*b = *e = t;
	else {				// Добавление элемента в конец
		(*e)->next = t;
		*e = t;
	}
}

//--Функция просмотра списка--//
void View_Spis1(int kod, Spis1 *t) {
											//--Просмотр списка с начала--//
		while (t != NULL) {					//Цикл работает, пока t!=NULL
			cout << t << " " << t->info <<" " << t->next << endl;	//Выводим информационную часть текущего элемента на экран
			t = t->next;					//Переставляем текущий указатель на следующий элемент, адресс которого находится в поле next текущего элемента t (t->next)
		}
}

//--Функция освобождения памяти--//
void Del_All(Spis1 **p) {
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

void Task(Spis1 **begin, Spis1 **end) {
	Spis1 *r, *t;
	t = *begin;
	r = *begin;

	do {
		t = t->next;
	} while (t->next->next != NULL);

	*begin = *end;
	*end = r;
	
	(*begin)->next = r->next;
	(*end)->next = NULL;
	t->next = *
		end;
}

void addelem(Spis1 **b, Spis1 **e, int in) {
	Spis1 *add = NULL , *t = new Spis1;	// add - добовляемы эдемент (NULL, чтобы в конце проверить, не добовляем ли элемент в позицию, мне списка. t - временная переменная.
	bool access = false;				// access - для цикла while в начале.
	int elems = 1, pos;					// счетчик элементов и номер нужной позиции
	t->next = *b;						//	временная структура t; связываем t с структурой, находящейся в начале списка.
	*b = t;								//	устонавливаем начало списка на временной переменной t.
	do {
		cout << "Enter position: "; cin >> pos;					//	получаем номер позиции
		if (pos <= 0) cout << "Wrong position!\n\n" << endl;	//	если позиция меньше или равна 0, то access не меняем, в итоге цикл начинается с начала
		else access = true;										//	иначе access = true
	} while (!access);											//	если access == true, продолжаем выполнение функции, иначе цикл повторяется.

	while (t != NULL) {					//	пока не дойдем до конца списка:
		if (elems == 2) {				//	если дошли до 1 элемента в списке (2 элемент, т.к. создаем временное начало списка (t))
			*b = t;						//	ставим начало списка на 1 элемент 
		}

		if (elems == pos) {				//	если доходим до нужного элемента, то:
			add = new Spis1;			//	выделяем память для нового элемента, чтобы избежать ошибки
			add->info = in;				//	add(добавленный элемент). информационная часть вводится с клавиатуры.
			add->next = t->next;		//	вставляем add в нужное место. Связываем следующий элемент за add с add. 
			t->next = add;				//	связываем предыдущий элемент (перед add) с add.
			if (add->next == NULL) {	//	если после добавленного элемента идет NULL, значит он последний;
				*e = add;				//	тогда ставим конец списка на этот элемент add.
			}
		}

		t = t->next;					//	идем дальше по списку.
		elems++;						//	считаем количество элементов.
	}


	if (add == NULL) {							//	если добавленный элемент так и равен NULL
		cout << "Out of Stack!\n\n" << endl;	//	Выводим сообщение
		return addelem(b, e, in);				//	возвращаем эту же функцию в месте ввода позиции
		}

	else cout << "Element added." << endl;		//	иначе - сообщение об успехе
}