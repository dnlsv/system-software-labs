#include <iostream>
#include <WinSock2.h>

using namespace std;

string str1, str2, str;
bool flag;
int sum;

DWORD WINAPI IntegerFunction(LPVOID);
DWORD WINAPI SumFunction(LPVOID);
DWORD WINAPI ConcatenationFunction(LPVOID);

int main()
{
    setlocale(LC_ALL, ".UTF8");

    flag = true;

    cout << "Введите две строки" << endl;
    cout << "1 строка: ";
    cin >> str1;
    cout << "2 строка: ";
    cin >> str2;

    DWORD integerThread;
    CreateThread(NULL, NULL, IntegerFunction, NULL, NULL, &integerThread);
    Sleep(1000);

    if (flag == true)
    {
        DWORD sumThread;
        CreateThread(NULL, NULL, SumFunction, NULL, NULL, &sumThread);
        Sleep(1000);
    }
    else
    {
        DWORD concatenationThread;
        CreateThread(NULL, NULL, ConcatenationFunction, NULL, NULL, &concatenationThread);
        Sleep(1000);
    }

    if (flag == true)
        cout << endl << "Сумма чисел: " << sum << endl;
    else
        cout << endl << "Конкатенация строк: " << str << endl;


    return 0;
}

DWORD WINAPI IntegerFunction(LPVOID parametr)
{
    if (str1.at(0) == '+' || str1.at(0) == '-')
    {
        if (str2.at(0) == '+' || str2.at(0) == '-')
        {
            for (int i = 1; i < str1.length(); i++)
                if (str1.at(i) < '0' || str1.at(i) > '9')
                    flag = false;
            for (int i = 1; i < str2.length(); i++)
                if (str2.at(i) < '0' || str2.at(i) > '9')
                    flag = false;
        }
        else
            flag = false;
    }
    else
        flag = false;

    return 0;
}

DWORD WINAPI SumFunction(LPVOID parametr)
{
    int a, b;

    a = atoi(str1.c_str());
    b = atoi(str2.c_str());

    sum = a + b;

    return 0;
}

DWORD WINAPI ConcatenationFunction(LPVOID parametr)
{
    str = str1 + str2;

    return 0;
}
