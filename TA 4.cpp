#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#define MAX 100000

using namespace std;

int enter()
{
	int a;
	do {
		cin >> a;
		if (cin.fail() || a < 1 || a > 100000)
		{
			//cout << a <<endl;
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "You entered wrong data, please try again" << endl;
			continue;
		}
		char c[255];
		fgets(c, 256, stdin);
		if (strlen(c) > 1) {
			cout << "You entered wrong data, please try again" << endl;
			continue;
		}
		return a;
	} while (true);
}

struct Elem
{
	int data; 
	Elem* next, * prev;
};



// черга покажчики

struct queue_item
{
	int number;
	queue_item* next;
};

class QueuePointer {
private:
	queue_item* LAST;
	queue_item* FIRST;
	int count;
public:
	QueuePointer() {
		LAST = NULL;
		FIRST = NULL;
		count = 0;
	}
	void push(int item) {		
		queue_item* new_item = new queue_item;
		new_item->number = item;
		new_item->next = NULL;
		if (LAST != NULL) {
			LAST->next = new_item;
		}
		LAST = new_item;
		if (FIRST == NULL)
			FIRST = new_item;
		count++;
	}
	void pop() {
		using namespace std;
		if (count == 1) {
			delete FIRST;
			FIRST = NULL;
			LAST = NULL;
			return;
		}
		else if (!count) {
			return;
		}
		queue_item* old = FIRST;
		FIRST = FIRST->next;
		delete old;
		count--;
	}
	void print() {
		using namespace std;
		queue_item* item = FIRST;
		while (item != NULL) {
			cout << item->number << " ";
			item = item->next;
		}
		cout << endl;
	}
};

//черга массив

class QueueArray {
private:

	int count;
	int* array;
public:
	QueueArray() {
		count = 0;
	}
	void push(int number) {
		if (!count) {
			array = new int;
			array[0] = number;
			count++;
		}
		else {
			int* old = array;
			array = new int[++count];
			for (int i = 0; i < count - 1; i++) {
				array[i] = old[i];
			}
			delete[] old;
			array[count - 1] = number;
		}
	}
	void pop() {
		int* old = array;
		array = new int[--count];
		for (int i = 0; i < count; i++) {
			array[i] = old[i + 1];
		}
		delete[] old;
	}
	void print() {
		using namespace std;
		for (int i = 0; i < count; i++) {
			cout << array[i] << " ";
		}
		cout << endl;
	}
};





int main()
{
	srand(time(NULL));
	QueuePointer queuep;
	QueueArray queuea;
	char c,sym;
	int a;
	setlocale(LC_ALL,"Rus");
	do {
		system("cls");
		cout << "Виберiть чергу\n1.Покажчик\n2.Масив" << endl;
		do {
			c = _getch();
		} while (c < '1' || c>'2');
		cout << "Виберiть спосiб заповнення\n1.Рандом\n2.Вручну" << endl;
		do {
			sym = _getch();
		} while (sym < '1' || sym>'2');
		/*switch (c)
		{
		case '1':
			cout << "Введiть число" << endl;
			cin >> a;
			queuep.push(a);
			queuep.print();
			break;
		case '2':
			queuep.pop();
			queuep.print();
			break;
		}*/
		if (c == '1')
		{
			int a;
			cout << "Скільки елементів додати в чергу" << endl;
			a = enter();
			if (sym == '1')
			{
				double start = clock();
				for (int i = 0; i < a; i++)
				{
					
					queuep.push(rand()%100+1);
					
				}
				double end = clock();
				cout << (end - start) << endl;
				queuep.print();
			}
			else
			{
				int b;
				for (int i = 0; i < a; i++)
				{
					cout << "Введiть елемент " << i + 1<< ":"<< endl;
					 b = enter();
					 queuep.push(b);
				}
				queuep.print();
			}
			cout << "Скiльки елементiв видалити?" << endl;
			a = enter();
			for (int i = 0; i < a; i++)
			{				
				queuep.pop();
			}
			queuep.print();
		}
		else
		{
			int a;
			cout << "Скільки елементів додати в чергу" << endl;
			a = enter();
			if (sym == '1')
			{
				for (int i = 0; i < a; i++)
				{
					queuea.push(rand() % 100 + 1);
				}
				queuea.print();
			}
			else
			{
				int b;
				for (int i = 0; i < a; i++)
				{
					cout << "Введiть елемент " << i + 1 << ":" << endl;
					b = enter();
					queuea.push(b);
				}
				queuea.print();
			}
			cout << "Скiльки елементiв видалити?" << endl;
			a = enter();
			for (int i = 0; i < a; i++)
			{
				queuea.pop();
			}
			queuea.print();
		}
	} while (_getch() != 27);
		system("pause");
}

