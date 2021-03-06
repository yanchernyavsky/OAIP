// Lab04.cpp : Defines the entry point for the console application.
//Двунаправленный список

#include "stdafx.h"
#include <iostream>

using namespace std;
						
struct Spis2 {			//--Декларация двунаправленного списка--//
	int info;			//
	Spis2 *prev, *next;	//
}*begin, *end, *t;		//Указатели на начало и конец
												//--Декларация прототипов функций пользователя--//
void Create_Spis2(Spis2**, Spis2**, int);		// Функция создания первого элемента
void Add_Spis2(int, Spis2**, Spis2**, int);		// Функция добавления элемента
void View_Spis2(int, Spis2*);					// Функция просмотра двунаправленного списка
void Del_All(Spis2**);							// Функция очистки памяти
void Task(Spis2**, Spis2**);					// Функция замены местами крайних элементов 
void Del_3(Spis2*&, Spis2*&);				// Удаление каждого 3 элемента в списке

int main()
{
	int in, kod;
	char Str[2][10] = { "Begin", "End" };
	Spis2 *begin = NULL;	
	Spis2 *end = NULL;
	while (true) {
		cout << "\n\tCreate - 1.\n\tAdd    - 2.\n\tView   - 3.\n\tDel    - 4.\n\tTask   - 5.\n\tDel3ed - 6.\n\tEXIT   - 0.\n\t";
		cin >> kod;
		switch (kod)
		{
		case 1:
			if (begin != NULL) {					//Если создаем новый список, должны освободить память, занятую предыдущим
				cout << "Clear Memory!" << endl;
				break;
			}
			cout << "Begin Info = "; cin >> in;
			Create_Spis2(&begin, &end, in);
			cout << "Create Begin = " << begin->info << endl;
			break;
		case 2: 
			cout << "Info = "; cin >> in;
			cout << "Add Begin - 0, Add End - 1: "; cin >> kod;
			Add_Spis2(kod, &begin, &end, in);
			if (kod == 0) t = begin;
			else t = end;
			cout << "Add to " << Str[kod] << " " << t->info << endl;
			break;
		case 3: 
			if (!begin) {
				cout << "Stack is Emty!" << endl;
				break;
			}
			cout << "View Begin - 0, View End - 1: "; cin >> kod;
			if (kod == 0) {
				t = begin;
				cout << "--Begin--" << endl;
			}
			else {
				t = end;
				cout << "--End--" << endl;
			}
			View_Spis2(kod, t);
			break;
		case 4:
			Del_All(&begin);
			cout << "Memory is Free!" << endl;
			break;
		case 5:
			if (begin == NULL) {
				cout << "Spis is Empty!" << endl;
				break;
			}
			Task(&begin, &end);
			cout << "--Task 4--" << endl;
			break;

		case 6:
			Del_3(begin, end);
			cout << "Deleted every 3ed object" << endl;
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
void Create_Spis2(Spis2 **begin, Spis2 **end, int in){
	Spis2 *t = new Spis2;				//Захват памяти для элемента
	t->info = in;						//Формируем информационную часть
	t->next = t->prev = NULL;			//Формируем адрессные части
	*begin = *end = t;					//Устанавливаем указатели начала и конца на первый элемент списка
}

//--Функция добавления элементов в список--//
void Add_Spis2(int kod, Spis2 **begin, Spis2 **end, int in) {
	Spis2 *t = new Spis2;				//Захват памятм для элемента
	t->info = in;						//Формируем информационную часть
	switch (kod) {
	case 0:								//--Добавление элемента в начало списка--//
		t->prev = NULL;					//Предыдущего нет
		t->next = *begin;				//Связываем новый элемент с первым
		(*begin)->prev = t;				//Изменяем адрес prev бывшего первого 
		*begin = t;						//Переставляем указатель begin на новый 
		break;
	case 1:								//--Добавление элемента в конец списка--//
		t->next = NULL;					//Следующего нет
		t->prev = *end;					//Связываем новый с последним
		(*end)->next = t;				//Изменяем адрес next бывшего последнего
		*end = t;						//Изменяем указатель end
	}
}

//--Функция просмотра списка--//
void View_Spis2(int kod, Spis2 *t) {
	switch (kod) {
	case 0:									//--Просмотр списка с начала--//
		while (t != NULL) {					//Цикл работает, пока t!=NULL
			cout << " " << t->info << endl;	//Выводим информационную часть текущего элемента на экран
			t = t->next;					//Переставляем текущий указатель на следующий элемент, адресс которого находится в поле next текущего элемента t (t->next)
		}
		break;
	case 1:									//--Просмотр списка с конца--//
		while (t != NULL) {					//Цикл работает, пока t!=NULL
			cout << " " << t->info << endl;	//Выводим информационную часть текущего элемента на экран
			t = t->prev;					//Переставляем текущий указатель на предыдущий элемент, адресс которого находится в поле prev текущего элемента t (t->prev)
		}
		break;
	}
}

//--Функция освобождения памяти--//
void Del_All(Spis2 **p) {
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

void Task(Spis2 **b, Spis2 **e) {
	Spis2 *t1, *t2;
	t1 = *b, t2 = *e;

	(t1->next)->prev = t2;
	(t2->prev)->next = t1;

	t1->prev = t2->prev;
	t2->next = t1->next;

	t1->next = NULL;
	t2->prev = NULL;

	*b = t2;
	*e = t1;

}

void Del_3(Spis2 *&b, Spis2 *&e) {
	
	Spis2 *t1 = b;
	Spis2 *t = new Spis2;

	while (t1->next != NULL)
	{
		if (t1->next->next == NULL) {
			return;
		}
		t = t1->next->next;
		if (t == e) {
			e = t->prev;
			e->next = NULL;
			delete t;
			return;
		}
		(t->prev)->next = t->next;
		(t->next)->prev = t->prev;
		t1 = t1->next->next;
	}

}