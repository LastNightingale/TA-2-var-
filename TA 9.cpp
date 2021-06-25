#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#define MAX 500 //максимум в рандомайзере
#define size 200 //элементов в 3 массиве
#define firstlast 50 //элементов в 1 массиве
#define additional 70 //элементов во 2 массиве

using namespace std;


void print(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
}

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
    char choice,s,c;
    vector<int> elem; 
    cout << "Оберiть метод\n1.Бульбашки\n2.Вставка\n3.Пiдрахунок" << endl;
    do{
        choice = _getch();
    } while (choice < '1' || choice>'3');
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
    cout << endl;
    cout << "До першого сортування:" << endl;
    print(main_array, firstlast);
    //сюда старт
    if (choice == '1') bubbleSort(main_array, firstlast);
    if (choice == '2') insertSort(main_array, firstlast);
    if (choice == '3') countSort(main_array, firstlast);
    //сюда финиш
    cout << endl;
    cout << "Пiсля першого сортування:" << endl;
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
    cout << "Оберiть метод\n1.Бульбашки\n2.Вставка\n3.Пiдрахунок" << endl;
    do {
        c = _getch();
    } while (c < '1' || c >'3');
    cout << endl;
    cout << "До другого сортування:" << endl;
    print(main_array, additional);    
    //сюда старт
    if (c == '1') bubbleSort(main_array, additional);
    if (c == '2') insertSort(main_array, additional);
    if (c == '3') countSort(main_array, additional);
    //сюда финиш
    cout << endl;
    cout << "Пiсля другого сортування:" << endl;
    print(main_array, additional);
    for (int i = additional; i < size; i++)
    {
        a = rand() % additional + 1;
        main_array[i] = main_array[a];
    }
    cout << endl;
    cout << "Оберiть метод\n1.Бульбашки\n2.Вставка\n3.Пiдрахунок" << endl;
    do {
        s = _getch();
    } while (s < '1' || s >'3');
    cout << endl;
    cout << "До третього сортування:" << endl;
    print(main_array, size);    
    //сюда старт
    if (s == '1') bubbleSort(main_array, size);
    if (s == '2') insertSort(main_array, size);
    if (s == '3') countSort(main_array, size);
    //сюда финиш
    cout << endl;
    cout << "Пiсля третього сортування:" << endl;
    print(main_array, size);
    system("pause");
}