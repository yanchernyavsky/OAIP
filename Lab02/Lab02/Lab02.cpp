#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

struct trip
{
	int num;
	char name[50];
	char bus[50];
	char point[50];
	float time1;
	float time2;
};

void quickSort(trip*, int, int);
int binary_search(trip*, int, int);
string add_information(string, trip*, int);
string show_information(string);
string sort_1(string, trip*, int);
string sort_2(string, trip*, int);

int main()
{
	setlocale(LC_ALL, "RUS");
	string path = "Raises.txt";
	int action = -1;

	int sz = 0;
	cout << "input size" << endl;
	cin >> sz;
	trip *trips = new trip[sz];

	while (true) {
		cout << "Выберите функцию" << endl;
		cout << "1 - Добавить информацию в файл" << endl;
		cout << "2 - Вывести информацию из файла на экран" << endl;
		cout << "3 - Поиск по времени + 1 сортировка" << endl;
		cout << "4 - Поиск по времени + 2 сортировка" << endl;
		cout << "0 - Выйти из программы" << endl;
		cin >> action;
		switch (action)
		{
		case 1: add_information(path, trips, sz); break;
		case 2: show_information(path); break;
		case 3: sort_1(path, trips, sz); break;
		case 4: sort_2(path, trips, sz); break;
		case 0: return 0;

		}
	}
	system("pause");
	return 0;
}

void quickSort(trip *trips, int left, int right) {

	int i = left, j = right;
	trip tmp;
	char pivot = trips[(left + right) / 2].punct[0];

	/* partition */

	while (i <= j) {
		while (trips[i].punct[0] < pivot)
			i++;

		while (trips[j].punct[0] > pivot)
			j--;

		if (i <= j) {

			tmp = trips[i];

			trips[i] = trips[j];

			trips[j] = tmp;

			i++;

			j--;

		}

	};

	/* recursion */

	if (left < j)

		quickSort(trips, left, j);

	if (i < right)

		quickSort(trips, i, right);

}
int binary_search(trip * trips, int sz, int time)
{
	int i = 0, j = sz - 1, m;
	while (i < j) {
		m = (i + j) / 2;
		if (trips[m].time1 < time) i = m + 1;
		else  j = m;
	}
	if (trips[i].time1 != time)
		return -1;
	else return i;

}
string add_information(string path, trip * trips, int sz)
{
	ofstream fout;
	fout.open(path, ofstream::out);
	string result = "";
	if (!fout.is_open())
	{
		cout << "Ошибка" << endl;
	}

	else
	{
		for (int i = 0; i < sz; i++) {
			{


				cout << "Trip number: ";
				cin >> trips[i].number;
				fout << "Trip number: ";
				fout << trips[i].number << "\t";
				cout << "Your destination: ";
				cin >> trips[i].punct;
				fout << "Your destination: ";
				fout << trips[i].punct << "\t";
				cout << "Bus type (big = 1, small = 2, middle = 3, superbus = 4)";
				cin >> trips[i].type;
				fout << "Bus type (big = 1, small = 2, middle = 3, superbus = 4): ";
				fout << trips[i].type << "\t";
				cout << "Enter time: ";
				cin >> trips[i].time1;
				fout << "Departure time: ";
				fout << trips[i].time1 << "\t";
				cout << "Enter time2: ";
				cin >> trips[i].time2;
				fout << "Arrival time: ";
				fout << trips[i].time2 << endl;


			}
		}
	}

	fout.close();
	return result;
}

string show_information(string path)
{
	ifstream fin;

	fin.open(path);
	string result = "";

	if (!fin.is_open())
	{
		cout << "Ошибка" << endl;
	}
	else
	{
		cout << "Файл открыт" << endl;


		string str;
		result = str;

		while (!fin.eof())
		{
			str = "";
			getline(fin, str);
			cout << str << endl;
		}

		system("pause");
	}

	fin.close();
	return result;
}

string sort_1(string path, trip * trips, int sz)
{
	ofstream fout;
	fout.open(path);
	int time = 0;
	string result = "";
	if (!fout.is_open())
	{
		cout << "Ошибка" << endl;
	}
	else {

		int m = 0;

		for (int i = 0; i < sz - 1; i++) {
			m = i;
			for (int j = i + 1; j < sz; j++)
				if (trips[j].time1 < trips[m].time1) m = j;
			trip r = trips[m];  					// Переставляем элементы
			trips[m] = trips[i];
			trips[i] = r;
		}

		cout << "And what time do you need?"; cin >> time;
		fout << "You can use: " << endl;


		int r = binary_search(trips, sz, time);

		if (r >= 0) {
			fout << "Reis: " << trips[r].number << "\t" << "Bus type: " << trips[r].type << "\t"
				<< "Arrival point: " << trips[r].punct << "\t" << "Departure time: " << trips[r].time1 << "\t" << "Arrival time: " << trips[r].time2 << endl;
		}
		else
			cout << "No trips, sorry" << endl;
	}
	string str;
	result = str;
	fout.close();
	return result;
}

string sort_2(string path, trip * trips, int sz)
{
	ofstream fout;
	fout.open(path);
	int time = 0;
	string result = "";
	if (!fout.is_open())
	{
		cout << "Ошибка" << endl;
	}
	else {


		quickSort(trips, 0, sz);


		cout << "And what time do you need?"; cin >> time;
		fout << "You can use: " << endl;
		int r = binary_search(trips, sz, time);

		if (r >= 0) {
			fout << "Reis: " << trips[r].number << "\t" << "Bus type: " << trips[r].type << "\t"
				<< "Arrival point: " << trips[r].punct << "\t" << "Departure time: " << trips[r].time1 << "\t" << "Arrival time: " << trips[r].time2 << endl;
		}
		else
			cout << "No trips, sorry" << endl;
	}
	string str;
	result = str;
	fout.close();
	return result;
}