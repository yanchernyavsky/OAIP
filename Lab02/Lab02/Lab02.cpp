#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


struct time
{
	int tm_min;		//минуты, 0-59
	int tm_hour;	//часы, 0-23
};
struct trip
{
	int num;
	int busType;
	char point[50];
	time time1;
	time time2;
};

string add_information(string, trip*, int);
string show_information(string);
void linearSearch(trip*, int);

int main()
{
	setlocale(LC_ALL, "RUS");
	string path = "trip.txt";
	int cod, size;

	cout << "Введите размер: ";
	cin >> size; cout << endl;

	trip *trips = new trip[size];

	while (true) {
		cout << "Выберите функцию: \n" << endl;

		cout << "\t 1 - Добавить информацию в файл\n" << endl;

		cout << "\t 2 - Вывести информацию из файла на экран\n" << endl;

		cout << "\t 3 - Линейный поиск\n" << endl;

		cout << "\t ELSE - Выйти из программы" << endl;
		cin >> cod; cout << endl;

		switch (cod)
		{
		case 1: add_information(path, trips, size); 
			break;
		case 2: show_information(path);
			break;
		case 3: linearSearch(trips, size);
			break;
		default: return 0;
		}
	}
	return 0;
}

string add_information(string path, trip *trips, int size)
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
		for (int i = 0; i < size; i++) {
			do {
				cout << "Номер поездки: ";
				cin >> trips[i].num;
				if (trips[i].num <= 0) cout << "Wrong number!" << endl;
			} while (trips[i].num <= 0);
				fout << "Номер поездки: " << trips[i].num << "\t";
			
			cout << "Пункт назначения: ";
			cin >> trips[i].point;
			fout << "Пункт назначения: " << trips[i].point << "\t";

			do {
				cout << "Тип автобуса (Большой = 1, Средний = 2, Маленький = 3, 2-ух этажный = 4): ";
				cin >> trips[i].busType;
				switch (trips[i].busType) {
				case 1: fout << "Тип автобуса: Большой\t";
					break;
				case 2: fout << "Тип автобуса: Средний\t";
					break;
				case 3: fout << "Тип автобуса: Маленький\t";
					break;
				case 4: fout << "Тип автобуса: 2-ух этажный\t";
					break;
				default: cout << "Wrong type!" << endl;
				}
			} while (trips[i].busType < 1 && trips[i].busType > 4);

			do {
				cout << "Введите время отъезда: " << endl << "\t Часы: ";
				cin >> trips[i].time1.tm_hour;
				cout << "\t Минуты: ";
				cin >> trips[i].time1.tm_min;
				if (trips[i].time1.tm_hour < 0 || trips[i].time1.tm_hour > 23 || trips[i].time1.tm_min < 0 || trips[i].time1.tm_min > 59) {
					cout << "Wrong Time!" << endl;
				}
			} while (trips[i].time1.tm_hour < 0 || trips[i].time1.tm_hour > 23 || trips[i].time1.tm_min < 0 || trips[i].time1.tm_min > 59);
				fout << "Время отъезда: " << trips[i].time1.tm_hour << ":" << trips[i].time1.tm_min << "\t";
			
			do {
				cout << "Введите время прибытия: " << endl << "\t Часы: ";
				cin >> trips[i].time2.tm_hour;
				cout << "\t Минуты: ";
				cin >> trips[i].time2.tm_min;
				if (trips[i].time2.tm_hour < 0 || trips[i].time2.tm_hour > 23 || trips[i].time2.tm_min < 0 || trips[i].time2.tm_min > 59) {
					cout << "Wrong Time!" << endl;
				}
			} while (trips[i].time2.tm_hour < 0 || trips[i].time2.tm_hour > 23 || trips[i].time2.tm_min < 0 || trips[i].time2.tm_min > 59);
				fout << "Время прибытия: " << trips[i].time2.tm_hour << ":" << trips[i].time2.tm_min << "\t";
		}
	}
	cout << endl;
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
		cout << "Файл открыт\n" << endl;

		string str;
		result = str;

		while (!fin.eof())
		{
			str = "";
			getline(fin, str);
			cout << str << endl;
		}
	}
	fin.close();
	return result;
}

void linearSearch(trip *trips, int size) {
	int i_key = 0, kod = 0;
	time f_key;
	cout << "Время прибытия: " << endl;
	cout << "Часы: "; cin >> f_key.tm_hour;
	cout << "Минуты: "; cin >> f_key.tm_min;
	cout << endl;

	for (int i = 0; i < size; i++)
		if (trips[i].time2.tm_hour == f_key.tm_hour && trips[i].time2.tm_min == f_key.tm_min) {
			kod = 1;
			i_key = i;
			cout << "Номер поездки: " << trips[i_key].num << "\t";
			cout << "Пункт назначения: " << trips[i_key].point << "\t";
			switch (trips[i_key].busType) {
			case 1: cout << "Тип автобуса: Большой\t";
				break;
			case 2: cout << "Тип автобуса: Средний\t";
				break;
			case 3: cout << "Тип автобуса: Маленький\t";
				break;
			case 4: cout << "Тип автобуса: 2-ух этажный\t";
				break;
			default: cout << "Wrong type!" << endl;
			}
			cout << "Время отправления: " << trips[i_key].time1.tm_hour << ":" << trips[i_key].time1.tm_min << "\t";
			cout << "Время прибытия: " << trips[i_key].time2.tm_hour << ":" << trips[i_key].time2.tm_min << endl;
		}
	cout << endl;
	if (kod == 0) {
		cout << "Рейсов не найдено\n" << endl;
		return;
	}
}

