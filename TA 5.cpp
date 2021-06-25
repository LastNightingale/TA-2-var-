#include <iostream>
#include <forward_list>
#include <ctime>
#include <conio.h>

#define N 15
using namespace std;

int enter() //функци€ ввода
{
	int a;
	do {
		cin >> a;
		if (cin.fail() || a <= 0 || a > 100)
		{
			//cout << a <<endl;
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "You entered wrong data, please try again" << endl;
			continue;
		}
		char c[255];
		fgets(c, 255, stdin);
		if (strlen(c) > 1) {
			cout << "You entered wrong data, please try again" << endl;
			continue;
		}
		return a;
	} while (true);
}

int HashMult(int key) //хеширование по делению
{
	int M = 16;
	double C = 0.4176;
	return trunc(M * fmod(key * C, 1));
}

int HashDivision(int key) //хеширование по делению
{
	return (key % N);
}

struct Elem 
{
	int key;
	int adr;
};

/*void Insert(int key, int adr);
int Search(int key);*/

void Insert(int key, int adr, forward_list<Elem> *HashTableDivision) //вставка элемента в таблицу
{
	Elem element;
	element.key = key;
	element.adr = adr;
	HashTableDivision[adr].push_front(element);
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	forward_list<Elem> HashTableDivision[N];
	char c, sym;
	cout << "який спосiб хешуванн€?\n1.ƒiленн€\n2.ћноженн€" << endl;
	do {
		c = _getch();
	} while (c < '1' || c>'2');
	cout << "який спосiб заповненн€ таблицi?\n1.–андом\n2.¬ручну" << endl;
	do {
		sym = _getch();
	} while (sym < '1' || sym>'2');
	system("cls");
	if (c == '1') {		
		int a;
		if (sym == '1') {
			for (int i = 0; i < N; i++)
			{
				a = rand() % 100 + 1;
				Insert(a, HashDivision(a), HashTableDivision);
				cout << "key -> " << a << " adress -> " << HashDivision(a) << endl;
			}
		}
		if (sym == '2')
		{
			int n;
			cout << "¬ведiть к-ть елемент≥в" << endl;
			n = enter();
			for (int i = 0; i < n; i++)
			{
				cout << "¬ведiть "<< i+1 <<" елемент" << endl;
				a = enter();
				Insert(a, HashDivision(a), HashTableDivision);
				cout << "key -> " << a << " adress -> " << HashDivision(a) << endl;
			}
		}
		cout << "¬ведiть ключ, €кий ви хочете знайти" << endl;
		a=enter();
		int b = HashDivision(a);
		for (auto iter : HashTableDivision[b])
		{
			if (iter.key == a)
				cout << "key -> " << iter.key << " adress -> " << iter.adr << endl;
		}
	}
	else
	{
		int a;
		if (sym == '1') {
			for (int i = 0; i < N; i++)
			{
				a = rand() % 100 + 1;
				Insert(a, HashMult(a), HashTableDivision);
				cout << "key -> " << a << " adress -> " << HashMult(a) << endl;
			}
		}
		if (sym == '2')
		{
			int n;
			cout << "¬ведiть к-ть елемент≥в" << endl;
			n = enter();
			for (int i = 0; i < n; i++)
			{
				cout << "¬ведiть " << i + 1 << " елемент" << endl;
				a = enter();
				Insert(a, HashMult(a), HashTableDivision);
				cout << "key -> " << a << " adress -> " << HashMult(a) << endl;
			}
		}
		cout << "¬ведiть ключ, €кий ви хочете знайти" << endl;
		a = enter();
		int b = HashMult(a);
		for (auto iter : HashTableDivision[b])
		{
			if (iter.key == a)
				cout << "key -> " << iter.key << " adress -> " << iter.adr << endl;
		}
	}
	system("pause");
}