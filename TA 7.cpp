#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <ctime>
#define MAX 500

using namespace std;

class Node
{
public:
	int data;
	Node* left;
	Node* right;	
	Node(int data)
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
};

int enter()
{
	int a;
	do {
		cin >> a;
		if (cin.fail() || a <= 0 || a > 10000)
		{
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

class Tree
{
private:
	int count;
	Node* root;
	vector<int> path;
	bool found = true;
public:
	Tree()
	{
		count = 0;
		root = nullptr;
	}
	~Tree()
	{
		Clear();
	}
	Node* GetRoot()
	{
		return root;
	}
	void AddNode(int data, Node* leaf)
	{
		if (data > leaf->data)
		{
			if (leaf->right != NULL) AddNode(data, leaf->right);
			else
			{
				leaf->right = new Node(data);
				++count;
			}
		}
		else
		{
			if (leaf->left != NULL) AddNode(data, leaf->left);
			else
			{
				leaf->left = new Node(data);
				++count;
			}
		}

	}

	void FindNodeIn(int data, Node* leaf)
	{
		if (leaf == NULL)
		{
			cout << "Елемент не знайдено" << endl;
			found = false;
		}
		else
		{
			if (data != leaf->data)
			{
				path.push_back(leaf->data);
				if (data < leaf->data)
				{
					FindNodeIn(data, leaf->left);
				}
				else
				{
					FindNodeIn(data, leaf->right);
				}
			}
			else
			{
				path.push_back(data);
				cout << "Елемент знайдено" << endl;
			}
		}
	}


	void ShowPath()
	{
		if (path.empty()) cout << "А всьо";
		else
		{
			for (auto it = path.begin(); it != path.end(); ++it)
			{
				//if (++it == path.end()) cout << *it << endl;
				cout << *it << " -> ";
			}
			cout << "кiнець" << endl;
		}
	}

	void FindNode(int data)
	{
		FindNodeIn(data, root);
		ShowPath();
		if(!found)
		{
			AddNodeNew(data);
			path.clear();
			FindNodeIn(data, root);
			ShowPath();
		}
		found = true;
		path.clear();
	}


	void AddNodeNew(int data)
	{
		if (root == NULL)
		{
			root = new Node(data);
			++count;
		}
		else AddNode(data, root);
	}

	void Show(Node* leaf)
	{
		if (!count) cout << "Дерево пусте" << endl;
		else
		{
			cout << "Елемент: " << leaf->data << endl;
			if (leaf->left != NULL)
			{
				cout << "Лiвий елемент:" << leaf->left->data << endl;
			}
			if (leaf->right != NULL)
			{
				cout << "Правий елемент:" << leaf->right->data << endl;
			}
			cout << endl;
			if (leaf->left != NULL) Show(leaf->left);
			if (leaf->right != NULL) Show(leaf->right);
		}
	}

	void Print()
	{
		Show(root);
	}

	void ClearTree(Node* leaf)
	{
		if (leaf != NULL)
		{
			if (leaf->left != NULL) ClearTree(leaf->left);
			if (leaf->right != NULL) ClearTree(leaf->right);
			delete leaf;
			--count;
		}
	}

	void Clear()
	{
		if (count) ClearTree(root);
	}
};

	
	

Tree tr;
int main()
{
	setlocale(LC_ALL, "Rus");
	int n,a,l;
	bool repeat;
	srand(time(NULL));
	char choice;
	vector<int> elem;
	cout << "Введiть кiлькiсть кораблiв" << endl;
	n = enter();
	cout << "Виберiть спосiб заповнення:\n1.Рандом\n2.Вручну" << endl;
	do {
		choice = _getch();
	} while (choice < '1' || choice>'2');
	if (choice == '1')
	{
		tr.AddNodeNew(MAX/2);
		elem.push_back(MAX/2);
		for (int i = 0; i < n - 1; ++i)
		{
			repeat = false;
			a = rand() % MAX + 1;
			for (int k : elem)
			{
				if (k == a) repeat = true;
			}
			if (repeat) --i;
			else
			{
				tr.AddNodeNew(a);
				elem.push_back(a);
			}
		}
	}
	else
	{
		for (int i = 0; i < n ; ++i)
		{
			repeat = false;
			cout << "Введiть к-ть матросiв " << i + 1 << " : " << endl;
			a = enter();
			for (int k : elem)
			{
				if (k == a) repeat = true;
			}
			if (repeat) --i;
			else
			{
				tr.AddNodeNew(a);
				elem.push_back(a);
			}
		}
	}
	tr.Print();
	cout << "Введiть скiльки кораблiв з пiратами ви хочете знайти" << endl;
	l = enter();
	for (int i = 0; i < l; ++i)
	{
		cout << "Введiть елемент " << i + 1 << " : " << endl;
		a = enter();
		tr.FindNode(a);
	}	
	system("pause");
	return 0;
}