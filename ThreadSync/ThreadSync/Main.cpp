#include <iostream>
#include <WinSock2.h>

using namespace std;

DWORD thID;
DWORD WINAPI PhilosopherThread1(LPVOID);
DWORD WINAPI PhilosopherThread2(LPVOID);
DWORD WINAPI PhilosopherThread3(LPVOID);
DWORD WINAPI PhilosopherThread4(LPVOID);
DWORD WINAPI PhilosopherThread5(LPVOID);

CRITICAL_SECTION PhilosopherFork1;
CRITICAL_SECTION PhilosopherFork2;
CRITICAL_SECTION PhilosopherFork3;
CRITICAL_SECTION PhilosopherFork4;
CRITICAL_SECTION PhilosopherFork5;

int main()
{

    InitializeCriticalSection(&PhilosopherFork1);
    InitializeCriticalSection(&PhilosopherFork2);
    InitializeCriticalSection(&PhilosopherFork3);
    InitializeCriticalSection(&PhilosopherFork4);
    InitializeCriticalSection(&PhilosopherFork5);

    while (true)
    {
        srand(time(0));
        CreateThread(NULL, NULL, PhilosopherThread1, NULL, NULL, &thID);
        CreateThread(NULL, NULL, PhilosopherThread2, NULL, NULL, &thID);
        CreateThread(NULL, NULL, PhilosopherThread3, NULL, NULL, &thID);
        CreateThread(NULL, NULL, PhilosopherThread4, NULL, NULL, &thID);
        CreateThread(NULL, NULL, PhilosopherThread5, NULL, NULL, &thID);
        Sleep(5000000);
    }

    return 0;
}

DWORD WINAPI PhilosopherThread1(LPVOID parametr)
{
    cout << "Philosopher 1 sits\n";
    EnterCriticalSection(&PhilosopherFork5);
    EnterCriticalSection(&PhilosopherFork1);
    cout << "Philosopher 1 is eating\n";
    Sleep(0 + rand() % 2000);
    cout << "Philosopher 1 is leaving\n";
    LeaveCriticalSection(&PhilosopherFork1);
    LeaveCriticalSection(&PhilosopherFork5);
    return 0;
}

DWORD WINAPI PhilosopherThread2(LPVOID parametr)
{
    cout << "Philosopher 2 sits\n";
    EnterCriticalSection(&PhilosopherFork1);
    EnterCriticalSection(&PhilosopherFork2);
    cout << "Philosopher 2 is eating\n";
    Sleep(0 + rand() % 2000);
    cout << "Philosopher 2 is leaving\n";
    LeaveCriticalSection(&PhilosopherFork2);
    LeaveCriticalSection(&PhilosopherFork1);
    return 0;
}

DWORD WINAPI PhilosopherThread3(LPVOID parametr)
{
    cout << "Philosopher 3 sits\n";
    EnterCriticalSection(&PhilosopherFork2);
    EnterCriticalSection(&PhilosopherFork3);
    cout << "Philosopher 3 is eating\n";
    Sleep(0 + rand() % 2000);
    cout << "Philosopher 3 is leaving\n";
    LeaveCriticalSection(&PhilosopherFork3);
    LeaveCriticalSection(&PhilosopherFork2);
    return 0;
}

DWORD WINAPI PhilosopherThread4(LPVOID parametr)
{
    cout << "Philosopher 4 sits\n";
    EnterCriticalSection(&PhilosopherFork3);
    EnterCriticalSection(&PhilosopherFork4);
    cout << "Philosopher 4 is eating\n";
    Sleep(0 + rand() % 2000);
    cout << "Philosopher 4 is leaving\n";
    LeaveCriticalSection(&PhilosopherFork4);
    LeaveCriticalSection(&PhilosopherFork3);
    return 0;
}

DWORD WINAPI PhilosopherThread5(LPVOID parametr)
{
    cout << "Philosopher 5 sits\n";
    EnterCriticalSection(&PhilosopherFork4);
    EnterCriticalSection(&PhilosopherFork5);
    cout << "Philosopher 5 is eating\n";
    Sleep(0 + rand() % 2000);
    cout << "Philosopher 5 is leaving\n";
    LeaveCriticalSection(&PhilosopherFork5);
    LeaveCriticalSection(&PhilosopherFork4);
    return 0;
}
