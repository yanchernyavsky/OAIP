// Lab06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct Tree {
	int info;							// информационная часть
	Tree *left, *right;		// адресная ччасть(адрес левой и правой части)
}*root;

Tree* List(int);				// Функция формарования дерева	
void Add_List(Tree*, int);	// Функция добавления информации в нужное место
void View_Tree(Tree*, int);	// Функция просмтора дерева
Tree* Del_Info(Tree*, int);	// Функция удаления узла по заданному ключу
Tree* Min_Key(Tree*);				// Функция поиска узла с минимальным ключом
void Make_Blns(Tree**, int, int, int*);	// Построение сбаланисрованного дерева поиска
void Del_Tree(Tree*);				// Функция освобождения памяти, занятого деревом
int random(int, int*);

int main(){
	int key, n,k, i, kod, *a, r;
	Tree *tree = NULL, *p_min;
	srand(time(NULL));

	while (true) {
		cout << "\n\tRoot   - 1.\n\tAdd    - 2.\n\tView   - 3.\n\tDelInfo- 4.\n\tFind_Min-5\n\tBalance -6\n\tDelTree- 7.\n\tEXIT   - 0.\n\t";

		cin >> kod;
		switch (kod) {
		case 1:
			if (root == NULL) {
				cout << "Enter info: "; cin >> key; cout << endl;
				root = List(key);
				break;
			}
			else
				cout << "Root already exist!";
			break;

		case 2:
			if (root == NULL) {
				cout << "Create root first!" << endl;
				break;
			}
			else {
				cout << "Enter info: "; cin >> key; cout << endl;
				Add_List(root, key);
				break;
			}

		case 3:
			if (root == NULL) {
				cout << "Tree is empty!" << endl;
				break;
			}
			else {
				cout << "TREE: " << endl;
				View_Tree(root, 0);
			}
			break;

		case 4:
			cout << "Eneter element key: "; cin >> key;
			Del_Info(root, key);
			break;

		case 5: 
			cout << "Find min: " << endl;
			p_min = Min_Key(root);
			cout << p_min->info << endl;
			break;

		case 6:
			cout << "Enter size: "; cin >> k;
			a = new int[k];
			cout << "Created mas." << endl;
			for (int i = 0; i < k; i++) {
			//	a[i] = random(k, a);
				cout << "Enter " << i + 1 << " element: "; cin >> a[i];
				cout << endl;
			}
			cout << "Mas filled." << endl;
			
		for (int i = 0; i < k-1; i++)
			for (int j = i + 1; j < k; j++)
				if (a[i] > a[j]) { 		// Переставляем элементы
					r = a[i];
					a[i] = a[j];
					a[j] = r;
				}
		cout << "Mas sorted." << endl;

		Make_Blns(&root, 0, k, a);
		cout << "Success!" << endl;
		break;

		case 7: 
			Del_Tree(root);
			cout << "Clear" << endl;
			root = NULL;
			break;
			
		default:
			return 0;
		}
		
	}
	return 0;
}

Tree* List(int inf) {
	Tree *t = new Tree;				// Захват памяти
	t->info = inf;						// Формирование информационной части
	t->left = t->right = NULL;	// Формирование адресных частей
	return t;									// Возврат созданного указателя
}

void Add_List(Tree *t, int key) {
	if (t == NULL)  //То, о чем я в самом начале писал. Если дерева нет, то сеем семечко
	{
		t = new Tree; //Выделяем память под звено дерева
		t->info = key; //Записываем данные в звено
		t->left = t->right = NULL; //Подзвенья инициализируем пустотой во избежание ошибок
	}

	if (key<t->info)   //Если нововведенный элемент key меньше чем элемент key из семечка дерева, уходим влево
	{
		if (t->left != NULL) Add_List(t->left, key); //При помощи рекурсии заталкиваем элемент на свободный участок
		else //Если элемент получил свой участок, то
		{
			t->left = new Tree;  //Выделяем память левому подзвену. Именно подзвену, а не просто звену
			t->left->left = t->left->right = NULL; //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			t->left->info = key; //Записываем в левое подзвено записываемый элемент 
		}
	}

	if (key>t->info)   //Если нововведенный элемент key больше чем элемент key из семечка дерева, уходим вправо
	{
		if (t->right != NULL) Add_List(t->right, key); //При помощи рекурсии заталкиваем элемент на свободный участок
		else //Если элемент получил свой участок, то
		{
			t->right = new Tree;  //Выделяем память правому подзвену. Именно подзвену, а не просто звену
			t->right->left = t->right->right = NULL; //У правого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			t->right->info = key; //Записываем в правое подзвено записываемый элемент 
		}
	}
}

void View_Tree(Tree *p, int level) {
	string str;
	if (p) {
		View_Tree(p->right, level + 1);
		for (int i = 0; i < level; i++) {
			str = str + "   ";
		}
		cout << str << " " << p->info << endl;
		View_Tree(p->left, level + 1);
	}
}

Tree* Del_Info(Tree *root, int key) {
	Tree *Del, *Prev_Del, *R, *Prev_R;
	// Del, Prev_Del – удаляемый узел и его предыдущий (предок); 
	// R, Prev_R – элемент, на который заменяется удаленный, и его предок;
	Del = root;
	Prev_Del = NULL;
	//-------- Поиск удаляемого элемента и его предка по ключу key ---------
	while (Del != NULL && Del->info != key) {
		Prev_Del = Del;
		if (Del->info > key)  Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) {				// Элемент не найден
		cout << "NOT Key!" << endl;
		return root;
	}
	//-------------------- Поиск элемента R для замены --------------------------------
	if (Del->right == NULL) R = Del->left;
	else
		if (Del->left == NULL) R = Del->right;
		else {
			//---------------- Ищем самый правый узел в левом поддереве -----------------
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL) {
				Prev_R = R;
				R = R->right;
			}
			//----------- Нашли элемент для замены R и его предка Prev_R -------------
			if (Prev_R == Del)  R->right = Del->right;
			else {
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Prev_R;
			}
		}
		if (Del == root) root = R;			// Удаляя корень, заменяем его на R
		else
			//------- Поддерево R присоединяем к предку удаляемого узла -----------
			if (Del->info < Prev_Del->info)
				Prev_Del->left = R;				// На левую ветвь
			else	Prev_Del->right = R;				// На правую ветвь
			delete Del;
			cout << "Success!" << endl;
			return root;
}

void Del_Tree(Tree *t) {
	if (t != NULL) {
		Del_Tree(t->left); 			// На левую ветвь
		Del_Tree(t->right); 			// На правую ветвь
		delete t;
	}

}

Tree* Min_Key(Tree *p) {			// Tree* Max_Key(Tree *p) 
	while (p->left != NULL) p = p->left;	// p=p->right;
	return p;
}

void Make_Blns(Tree **p, int n, int k, int *a) {
	if (n == k) {
		*p = NULL;
		return;
	}
	else {
		int m = (n + k) / 2;
		*p = new Tree;
		(*p)->info = a[m];
		Make_Blns(&(*p)->left, n, m, a);
		Make_Blns(&(*p)->right, m + 1, k, a);
	}
}

//int random(int size, int *a) {
//	int i;
//	i = rand() % 30 + 1;
//	for (int k = 0; k < size; k++)
//	{
//		if (a[k] == i)
//			return random(size, a);
//		else {
//			return i;
//		}
//	}
//}