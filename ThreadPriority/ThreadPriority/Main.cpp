#include <iostream>
#include <WinSock2.h>

using namespace std;

string str1, str2, str;
bool flag;
int sum;

DWORD WINAPI IntegerFunction(LPVOID);
DWORD WINAPI SumFunction(LPVOID);
DWORD WINAPI ConcatenationFunction(LPVOID);
int executeTime(HANDLE);

int main()
{
    setlocale(LC_ALL, ".UTF8");

    flag = true;

    cout << "Введите две строки" << endl;
    cout << endl;

    cout << "1 строка: ";
    cin >> str1;
    cout << "2 строка: ";
    cin >> str2;

    HANDLE integerHandle = NULL, sumHandle = NULL, concatenationHandle = NULL;

    DWORD integerThread;
    integerHandle = CreateThread(NULL, NULL, IntegerFunction, NULL, NULL, &integerThread);
    SetThreadPriority(integerHandle, THREAD_PRIORITY_ABOVE_NORMAL);
    ResumeThread(integerHandle);
    Sleep(1000);

    if (flag == true)
    {
        DWORD sumThread;
        sumHandle = CreateThread(NULL, NULL, SumFunction, NULL, NULL, &sumThread);
        SetThreadPriority(sumHandle, THREAD_PRIORITY_LOWEST);
        ResumeThread(sumHandle);
        Sleep(1000);
    }
    else
    {
        DWORD concatenationThread;
        concatenationHandle = CreateThread(NULL, NULL, ConcatenationFunction, NULL, NULL, &concatenationThread);
        SetThreadPriority(concatenationHandle, THREAD_PRIORITY_IDLE);
        ResumeThread(concatenationHandle);
        Sleep(1000);
    }

    cout << endl;
    cout << "Целочисленный поток работал " << executeTime(integerHandle) << " мс" << endl;
    cout << "Поток суммы работал " << executeTime(sumHandle) << " мс" << endl;
    cout << "Поток конкатенации работал " << executeTime(concatenationHandle) << " мс" << endl;


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

int executeTime(HANDLE thread)
{
    FILETIME lpCreationTime;
    FILETIME lpExitTime;
    FILETIME lpKernelTime;
    FILETIME lpUserTime;

    SYSTEMTIME sCreationTime;
    SYSTEMTIME sExitTime;

    GetThreadTimes(thread,
        &lpCreationTime,
        &lpExitTime,
        &lpKernelTime,
        &lpUserTime);

    FileTimeToSystemTime(&lpCreationTime, &sCreationTime);
    FileTimeToSystemTime(&lpExitTime, &sExitTime);
    int startTime = sCreationTime.wSecond * 1000 + sCreationTime.wMilliseconds;
    int endTime = sExitTime.wSecond * 1000 + sExitTime.wMilliseconds;

    return endTime - startTime;
}
