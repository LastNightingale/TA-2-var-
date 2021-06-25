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
	Node* parent;
	bool isBlack;
	Node(int data, Node* parent)
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		isBlack = true;
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
			cout << "Введiть ще раз" << endl;
			continue;
		}
		char c[255];
		fgets(c, 255, stdin);
		if (strlen(c) > 1) {
			cout << "Введiть ще раз" << endl;
			continue;
		}
		return a;
	} while (true);
}

class RBTree
{
private:
	int count;
	Node* root;
	vector<int> path;
	bool found = true;
public:
	RBTree()
	{
		count = 0;
		root = nullptr;
	}
	~RBTree()
	{
		Clear();
	}

	void AddNode(int data, Node* leaf)
	{
		if (data > leaf->data)
		{
			if (leaf->right != NULL) AddNode(data, leaf->right);
			else
			{
				leaf->right = new Node(data,leaf);
				if (leaf->isBlack == true) leaf->right->isBlack = false;
				++count;
			}
		}
		else
		{
			if (leaf->left != NULL) AddNode(data, leaf->left);
			else
			{
				leaf->left = new Node(data,leaf);
				if (leaf->isBlack == true) leaf->left->isBlack = false;
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
				cout << *it << " -> ";
			}
			cout << "кiнець" << endl;
		}
	}

	void FindNode(int data)
	{
		FindNodeIn(data, root);
		ShowPath();
		if (!found)
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
			root = new Node(data,nullptr);
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