#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <cmath>
#include <conio.h>

using namespace std;

vector<int> table1;
vector<int> table2;

int hashh(int k)
{
    return k % 50;
}
int hashh2(int k)
{
    return (int)(159 * fmod(k * 0.279218, 1)) + 1;
}

void insert1(int n)
{
    int k = -1;
    for (int i = 0; i < table1.size(); i += 50)
        if (hashh(n) == hashh(table1[i]))
        {
            k = i;
            break;
        }
    if (k == -1)
    {
        table1.resize(table1.size() + 50);
        table1[table1.size() - 47] = n;
        return;
    }
    for (int i = k; i < k + 47; i++)
    {
        if (table1[i] == 0)
        {
            table1[i] = n;
            break;
        }
    }
}

void insert2(int n)
{
    int k = -1;
    for (int i = 0; i < table2.size(); i += hashh2(hashh(table2[i])))
        if (hashh(n) == hashh(table2[i]))
        {
            k = i;
            break;
        }
    if (k == -1)
    {
        table2.resize(table2.size() + hashh2(hashh(n)));
        table2[table2.size() - hashh2(hashh(n))] = n;
        return;
    }
    for (int i = k; i < k + hashh2(hashh(table2[k])); i++)
    {
        if (table2[i] == 0)
        {
            table2[i] = n;
            break;
        }
    }
}

int menu()
{
    cout << "1. Add element" << endl;
    cout << "2. Delete element" << endl;
    cout << "3. Find element" << endl;
    cout << "4. Print Table 1" << endl;
    cout << "5. Print Table 2" << endl;
    cout << "0. Exit" << endl;
    int choose;
    cin >> choose;
    return choose;
}

int main()
{

    int n, temp, choose = 10, k;
    double start_time, end_time, t1 = 0, t2 = 0;
    cout << "Enter n" << endl;
    cin >> n;
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        temp = rand() % 1051;

        start_time = clock();
        insert1(temp);
        end_time = clock();
        t1 += end_time - start_time;

        start_time = clock();
        insert2(temp);
        end_time = clock();
        t2 += end_time - start_time;
    }
    while (choose != 0)
    {
        system("CLS");
        choose = menu();
        switch (choose)
        {
        case 1:
            cin >> temp;
            insert1(temp);
            insert2(temp);
            break;
        case 2:
            cin >> temp;
            for (auto i = table1.begin(); i < table1.end(); i += 47)
                if (hashh(temp) == hashh(*i))
                {
                    table1.erase(i, i + 47);
                    break;
                }
            for (auto i = table2.begin(); i < table2.end(); i += hashh2(hashh(*i)))
                if (hashh(temp) == hashh(*i))
                {
                    table2.erase(i, i + hashh2(hashh(*i)));
                    break;
                }
            break;
        case 3:
            cin >> temp;
            for (auto i = table1.begin(); i < table1.end(); i += 47)
                if (hashh(temp) == hashh(*i))
                {
                    auto f = i;
                    cout << "Hash " << hashh(*i) << ": ";
                    while (*f != 0 && f < i + 47)
                    {
                        cout << *f++ << " ";
                    }
                    break;
                }
            cout << endl;
            for (auto i = table2.begin(); i < table2.end(); i += hashh2(hashh(*i)))
                if (hashh(temp) == hashh(*i))
                {
                    auto f = i;
                    cout << "Hash " << hashh(*i) << ": ";
                    while (*f != 0 && f < i + hashh2(hashh(*i)))
                    {
                        cout << *f++ << " ";
                    }
                    break;
                }
            break;
        case 4:
            cout << "Table 1: \n";
            for (int i = 0; i < table1.size(); i += 47)
            {
                int f = i;
                if (table1[i] != 0) cout << "Hash " << hashh(table1[i]) << ": ";
                else continue;
                while (table1[f] != 0 && f < i + 47)
                    cout << table1[f++] << " ";
                cout << endl;
            }
            cout << "Time: " << t1 << endl;
            break;
        case 5:
            cout << "Table 2: \n";
            for (int i = 0; i < table2.size(); i += hashh2(hashh(table2[i])))
            {
                int f = i;
                if (table2[i] != 0) cout << "Hash " << hashh(table2[i]) << ": ";
                else continue;
                while (table2[f] != 0 && f < i + hashh2(hashh(table2[i])))
                    cout << table2[f++] << " ";
                cout << endl;
            }
            cout << "Time: " << t2 << endl;
            break;
        default:
            break;
        }
        _getch();
    }

    return 0;
}