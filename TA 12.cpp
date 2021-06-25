#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <iomanip>

#define size 100
#define MAX 100000
#define NBUCKET 100
#define INTERVAL 1000
#define sorted 10 //количество элементов чтобы отсортировать квиксортом
#define notrepeated 50 //количество элементов которые не повторятся(или повторятся, но не факт)

using namespace std;

void print(int* a, int n) 
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d\t", a[i]);
}
void radix_sort(int* a, int n) {
	int i, b[size], m = 0, exp = 1;
	for (i = 0; i < n; i++) {
		if (a[i] > m)
			m = a[i];
	}
	while (m / exp > 0) {
		int box[size] = { 0 };
		for (i = 0; i < n; i++)
			box[a[i] / exp % size]++;
		for (i = 1; i < size; i++)
			box[i] += box[i - 1];
		for (i = n - 1; i >= 0; i--)
			b[--box[a[i] / exp % size]] = a[i];
		for (i = 0; i < n; i++)
			a[i] = b[i];
		exp *= size;
	}
}


struct Node {
	int data;
	struct Node* next;
};

void BucketSort(int arr[]);
struct Node* InsertionSort(struct Node* list);
void print(int arr[]);
void printBuckets(struct Node* list);
int getBucketIndex(int value);

void BucketSort(int arr[]) {
	int i, j;
	struct Node** buckets;

	buckets = (struct Node**)malloc(sizeof(struct Node*) * NBUCKET);

	for (i = 0; i < NBUCKET; ++i) {
		buckets[i] = NULL;

	}

	for (i = 0; i < size; ++i) {
		struct Node* current;
		int pos = getBucketIndex(arr[i]);
		current = (struct Node*)malloc(sizeof(struct Node));
		current->data = arr[i];
		current->next = buckets[pos];
		buckets[pos] = current;
	}	

	for (i = 0; i < NBUCKET; ++i) {
		buckets[i] = InsertionSort(buckets[i]);
	}	

	for (j = 0, i = 0; i < NBUCKET; ++i) {
		struct Node* node;
		node = buckets[i];
		while (node) {
			arr[j++] = node->data;
			node = node->next;
		}
	}

	for (i = 0; i < NBUCKET; ++i) {
		struct Node* node;
		node = buckets[i];
		while (node) {
			struct Node* tmp;
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
	free(buckets);
	return;
}

void qsort(int* arr, int left, int right)
{
	int i = left, j = right;
	int temp, pivot = arr[(left + right) / 2];

	while (i <= j)
	{
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;

		if (i <= j)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
			}

			i++; j--;
		}

	};

	if (left < j) qsort(arr, left, j);
	if (i < right) qsort(arr, i, right);
}

struct Node* InsertionSort(struct Node* list) {
	struct Node* k, * nodeList;

	if (list == 0 || list->next == 0) {
		return list;
	}

	nodeList = list;
	k = list->next;
	nodeList->next = 0;
	while (k != 0) {
		struct Node* ptr;
		if (nodeList->data > k->data) {
			struct Node* tmp;
			tmp = k;
			k = k->next;
			tmp->next = nodeList;
			nodeList = tmp;
			continue;
		}

		for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
			if (ptr->next->data > k->data)
				break;
		}

		if (ptr->next != 0) {
			struct Node* tmp;
			tmp = k;
			k = k->next;

			tmp->next = ptr->next;
			ptr->next = tmp;
			continue;
		}
		else {
			ptr->next = k;
			k = k->next;
			ptr->next->next = 0;
			continue;
		}
	}
	return nodeList;
}

int getBucketIndex(int value) {
	return value / INTERVAL;
}

// Print buckets
void print(int ar[]) {
	int i;
	for (i = 0; i < size; ++i) {
		cout << setw(3) << ar[i];
	}
	cout << endl;
}

void printBuckets(struct Node* list) {

	struct Node* cur = list;
	while (cur) {
		cout << setw(3) << cur->data;
		cur = cur->next;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	int n, a, l;
	bool repeat;
	int main_array[size];
	srand(time(NULL));
	char choice, s, c;
	vector<int> elem;
	//для теста 1
	for (int i = 0; i < size; ++i) // вставка без повторов
	{
		repeat = false;
		a = rand() % MAX + 1000;
		for (int k : elem)
		{
			if (k == a) repeat = true;
		}
		if (repeat) --i;
		else
		{
			main_array[i] = a;
			elem.push_back(a);
		}
	} 

	//для теста 2
	//qsort(main_array, 0, sorted-1); // для сортировки какого-то процента массива, sorted определяет количество
	
	//для теста 3
	/*for (int i = 0; i < notrepeated; ++i) // какая-то часть элементов
	{
		a = rand() % MAX + 1000;
	    main_array[i] = a;
	}
	for (int i = notrepeated; i < size; i++) //чтобы элементы повторялись
	{
		a = rand() % (notrepeated - 1) + 1;
		main_array[i] = main_array[a];
	}*/

	cout << "1.LSD\n2.Кошик" << endl;
	do
	{
		s = _getch();
	} while (s < '1' || s > '2');
	cout << "Масив до сортування:" << endl;
	print(&main_array[0], size);
	cout << endl;	
	if (s == '1') radix_sort(&main_array[0], size);
	else BucketSort(main_array);
	cout << "\nМасив пiсля сортування" << endl;
	print(&main_array[0], size);
	cout << endl;
	system("pause");
	return 0;
}
