#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#define MAX 1000 //�������� � ������������
#define size 500 //��������� � 3 �������
#define firstlast 150 //��������� � 1 �������
#define additional 300 //��������� �� 2 �������

using namespace std;

void print(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
}

void qsortmod(int arr[], int b, int e)
{
    int l = b, r = e;
    int piv = arr[(l + r) / 2]; 
    while (l <= r)
    {
        while (arr[l] < piv)
            l++;
        while (arr[r] > piv)
            r--;
        if (l <= r)
            swap(arr[l++], arr[r--]);
    }
    if (b < r)
        qsortmod(arr, b, r);
    if (e > l)
        qsortmod(arr, l, e);
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
/*void qsortmod(int* arr, int left, int right)
{
    int i = left, j = right;
    int temp, pivot = arr[(left + right) / 2];

    while (i <= j)
    {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j)
        {
            if (arr[i] > arr[j]|| arr[i] == arr[j])
            {
                temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            }

            i++; j--;
        }

    };

    if (left < j) qsort(arr, left, j);
    if (i < right) qsort(arr, i, right);
}*/

/*void quickSort(int* numbers, int left, int right)
{
    int pivot; // ����������� �������
    int l_hold = left; //����� �������
    int r_hold = right; // ������ �������
    pivot = numbers[left];
    while (left < right) // ���� ������� �� ���������
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
        if (left != right) // ���� ������� �� ����������
        {
            numbers[left] = numbers[right]; // ���������� ������� [right] �� ����� ������������
            left++; // �������� ����� ������� ������
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
        if (left != right) // ���� ������� �� ����������
        {
            numbers[right] = numbers[left]; // ���������� ������� [left] �� ����� [right]
            right--; // �������� ������ ������� ������
        }
    }
    numbers[left] = pivot; // ������ ����������� ������� �� �����
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
        quickSort(numbers, left, pivot - 1);
    if (right > pivot)
        quickSort(numbers, pivot + 1, right);
}*/

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

void insertSort(int* arr, int length_array)
{
    long t, j;
    t = 0;
    if (arr[0] > arr[1])
    {
        t = arr[0];
        arr[0] = arr[1];
        arr[1] = t;

    }
    for (long i = 2; i < length_array; i++)
    {
        t = arr[i];
        j = i - 1;
        while (t < arr[j] && j>-1)
        {
            arr[j + 1] = arr[j];
            --j;
            arr[j + 1] = t;
        }
    }
}

void countSort(int array[], int length_array)
{
    int output[MAX + 1];
    int count[MAX + 1];
    int max = array[0];

    for (int i = 1; i < length_array; i++)
    {
        if (array[i] > max)
            max = array[i];
    }

    for (int i = 0; i <= max; ++i)
    {
        count[i] = 0;
    }

    for (int i = 0; i < length_array; i++)
    {
        count[array[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = length_array - 1; i >= 0; i--)
    {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i = 0; i < length_array; i++)
    {
        array[i] = output[i];
    }
}

void bubbleSort(int arr[], int length_array)
{
    int t;
    for (long a = 0; a < length_array - 1; a++)
    {
        for (long b = a + 1; b < length_array; b++)
        {
            if (arr[a] > arr[b])
            {
                t = arr[a];
                arr[a] = arr[b];
                arr[b] = t;
            }
        }
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int n, a, l;
    bool repeat;
    int main_array[size];
    //srand(time(NULL));
    char choice, s, c;
    vector<int> elem;
    for (int i = 0; i < firstlast; ++i)
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
            main_array[i] = a;
            elem.push_back(a);
        }
    }
    cout << "1.������\n2.���������\n3.�������\n4.�i��������" << endl;
    do {
        choice = _getch();
    } while (choice < '1' || choice>'4');
    cout << "�� ������� ����������:" << endl;
    print(main_array, firstlast);
    //���� �����
    if (choice == '1') qsort(main_array, 0,firstlast-1);
    if (choice == '2') bubbleSort(main_array, firstlast);
    if (choice == '3') insertSort(main_array, firstlast);
    if (choice == '4') countSort(main_array, firstlast);
    //���� �����
    cout << endl;
    cout << "�i��� ������� ����������:" << endl;
    print(main_array, firstlast);
    for (int i = firstlast; i < additional; i++)
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
            main_array[i] = a;
            elem.push_back(a);
        }
    }
    cout << endl;    
    cout << "1.������\n2.���������\n3.�������\n4.�i��������" << endl;
    do {
        c = _getch();
    } while (c < '1' || c>'4');
    cout << "�� ������� ����������:" << endl;
    print(main_array, additional);    
    //���� �����
    if (c == '1') qsort(main_array, 0, additional - 1);
    if (c == '2') bubbleSort(main_array, additional);
    if (c == '3') insertSort(main_array, additional);
    if (c == '4') countSort(main_array, additional);
    //���� �����
    cout << endl;
    cout << "�i��� ������� ����������:" << endl;
    print(main_array, additional);
    for (int i = additional; i < size; i++)
    {
        a = rand() % additional + 1;
        main_array[i] = main_array[a];
    }
    cout << endl;
    cout << "1.������(�����i������)\n2.���������\n3.�������\n4.�i��������" << endl;
    do {
        s = _getch();
    } while (s < '1' || s > '4');
    cout << endl;
    cout << "�� �������� ����������:" << endl;
    print(main_array, size);
    if (s == '1') qsortmod(main_array, 0, size-1);
    if (s == '2') bubbleSort(main_array, size);
    if (s == '3') insertSort(main_array, size);
    if (s == '4') countSort(main_array, size);
    cout << endl;
    cout << "�i��� �������� ����������:" << endl;
    print(main_array, size);
    system("pause");
}