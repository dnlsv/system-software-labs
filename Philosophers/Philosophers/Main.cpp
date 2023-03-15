#include <iostream> //подключение библиотеки iostream
#include <WinSock2.h> //подключение библиотеки WinSock2.h

using namespace std; //использование пространства имен std

DWORD thID; //создание перемменной типа DWORD
DWORD WINAPI PhilosopherThread1(LPVOID); //прототип функции потока для 1-го философа
DWORD WINAPI PhilosopherThread2(LPVOID); //прототип функции потока для 2-го философа
DWORD WINAPI PhilosopherThread3(LPVOID); //прототип функции потока для 3-го философа
DWORD WINAPI PhilosopherThread4(LPVOID); //прототип функции потока для 4-го философа
DWORD WINAPI PhilosopherThread5(LPVOID); //прототип функции потока для 5-го философа

CRITICAL_SECTION PhilosopherFork1; //создание переменной ти CRITICAL_SECTION (критическая секция) для 1-ой вилки
CRITICAL_SECTION PhilosopherFork2; //создание переменной ти CRITICAL_SECTION (критическая секция) для 2-ой вилки
CRITICAL_SECTION PhilosopherFork3; //создание переменной ти CRITICAL_SECTION (критическая секция) для 3-ой вилки
CRITICAL_SECTION PhilosopherFork4; //создание переменной ти CRITICAL_SECTION (критическая секция) для 4-ой вилки
CRITICAL_SECTION PhilosopherFork5; //создание переменной ти CRITICAL_SECTION (критическая секция) для 5-ой вилки

int main() //создание главной функции main
{
	InitializeCriticalSection(&PhilosopherFork1); //инициализация критической секции для 1-ой вилки
	InitializeCriticalSection(&PhilosopherFork2); //инициализация критической секции для 2-ой вилки
	InitializeCriticalSection(&PhilosopherFork3); //инициализация критической секции для 3-ой вилки
	InitializeCriticalSection(&PhilosopherFork4); //инициализация критической секции для 4-ой вилки
	InitializeCriticalSection(&PhilosopherFork5); //инициализация критической секции для 5-ой вилки

	while (true) //начало бесконечного цикла
	{
		srand(time(0)); //обнуление времени отсчета
		CreateThread(NULL, NULL, PhilosopherThread1, NULL, NULL, &thID); //создание потока для 1-го философа
		CreateThread(NULL, NULL, PhilosopherThread2, NULL, NULL, &thID); //создание потока для 2-го философа
		CreateThread(NULL, NULL, PhilosopherThread3, NULL, NULL, &thID); //создание потока для 3-го философа
		CreateThread(NULL, NULL, PhilosopherThread4, NULL, NULL, &thID); //создание потока для 4-го философа
		CreateThread(NULL, NULL, PhilosopherThread5, NULL, NULL, &thID); //создание потока для 5-го философа
		Sleep(5000); //поток приостанавливается на 5000 миллисекунд
		cout << endl;
	}

	return 0; //возвращение нулевого значение
}

DWORD WINAPI PhilosopherThread1(LPVOID parametr) //описание функции потока для 1-го философа
{
	cout << "Philosopher 1 sits\n";  //вывод на экран сообщения о том, что 1-ый философ сел за стол
	EnterCriticalSection(&PhilosopherFork5); //вход в критическую секцию 5-ой вилки
	EnterCriticalSection(&PhilosopherFork1); //вход в критическую секцию 1-ой вилки
	cout << "Philosopher 1 is eating\n"; //вывод на экран сообщения о том, что 1-ый философ начал есть
	Sleep(0 + rand() % 2000); //поток приостанавливается на случайное количество миллисекунд от 0 до 2000
	cout << "Philosopher 1 is leaving\n"; //вывод на экран сообщения о том, что 1-ый философ ушел из-за стола
	LeaveCriticalSection(&PhilosopherFork1); //выход из критической секции 1-ой вилки
	LeaveCriticalSection(&PhilosopherFork5); //выход из критической секции 5-ой вилки
	return 0; //возвращение нулевого значение
}

DWORD WINAPI PhilosopherThread2(LPVOID parametr) //описание функции потока для 2-го философа
{
	cout << "Philosopher 2 sits\n"; //вывод на экран сообщения о том, что 2-ой философ сел за стол
	EnterCriticalSection(&PhilosopherFork1); //вход в критическую секцию 1-ой вилки
	EnterCriticalSection(&PhilosopherFork2); //вход в критическую секцию 2-ой вилки
	cout << "Philosopher 2 is eating\n"; //вывод на экран сообщения о том, что 2-ой философ начал есть
	Sleep(0 + rand() % 2000); //поток приостанавливается на случайное количество миллисекунд от 0 до 2000
	cout << "Philosopher 2 is leaving\n"; //вывод на экран сообщения о том, что 2-ой философ ушел из-за стола
	LeaveCriticalSection(&PhilosopherFork2); //выход из критической секции 2-ой вилки
	LeaveCriticalSection(&PhilosopherFork1); //выход из критической секции 1-ой вилки
	return 0; //возвращение нулевого значение
}

DWORD WINAPI PhilosopherThread3(LPVOID parametr) //описание функции потока для 3-го философа
{
	cout << "Philosopher 3 sits\n"; //вывод на экран сообщения о том, что 3-ий философ сел за стол
	EnterCriticalSection(&PhilosopherFork2); //вход в критическую секцию 2-ой вилки
	EnterCriticalSection(&PhilosopherFork3); //вход в критическую секцию 3-ей вилки
	cout << "Philosopher 3 is eating\n"; //вывод на экран сообщения о том, что 3-ий философ начал есть
	Sleep(0 + rand() % 2000); //поток приостанавливается на случайное количество миллисекунд от 0 до 2000
	cout << "Philosopher 3 is leaving\n"; //вывод на экран сообщения о том, что 3-ий философ ушел из-за стола
	LeaveCriticalSection(&PhilosopherFork3); //выход из критической секции 3-ей вилки
	LeaveCriticalSection(&PhilosopherFork2); //выход из критической секции 2-ой вилки
	return 0; //возвращение нулевого значение
}

DWORD WINAPI PhilosopherThread4(LPVOID parametr) //описание функции потока для 4-го философа
{
	cout << "Philosopher 4 sits\n"; //вывод на экран сообщения о том, что 4-ый филосов сел за стол
	EnterCriticalSection(&PhilosopherFork3); //вход в критическую секцию 3-ей вилки
	EnterCriticalSection(&PhilosopherFork4); //вход в критическую секцию 4-ой вилки
	cout << "Philosopher 4 is eating\n"; //вывод на экран сообщения о том, что 4-ый философ начал есть
	Sleep(0 + rand() % 2000); //поток приостанавливается на случайное количество миллисекунд от 0 до 2000
	cout << "Philosopher 4 is leaving\n"; //вывод на экран сообщения о том, что 4-ый философ ушел из-за стола
	LeaveCriticalSection(&PhilosopherFork4); //выход из критической секции 4-ой вилки
	LeaveCriticalSection(&PhilosopherFork3); //выход из критической секции 3-ей вилки
	return 0; //возвращение нулевого значение
}

DWORD WINAPI PhilosopherThread5(LPVOID parametr) //описание функции потока для 5-го философа
{
	cout << "Philosopher 5 sits\n"; //вывод на экран сообщения о том, что 5-ый философ сел за стол
	EnterCriticalSection(&PhilosopherFork4); //вход в критическую секцию 4-ой вилки
	EnterCriticalSection(&PhilosopherFork5); //вход в критическую секцию 5-ой вилки
	cout << "Philosopher 5 is eating\n"; //вывод на экран сообщения о том, что 5-ый философ начал есть
	Sleep(0 + rand() % 2000); //поток приостанавливается на случайное количество миллисекунд от 0 до 2000
	cout << "Philosopher 5 is leaving\n"; //вывод на экран сообщения о том, что 5-ый философ ушел из-за стола
	LeaveCriticalSection(&PhilosopherFork5); //выход из критической секции 5-ой вилки
	LeaveCriticalSection(&PhilosopherFork4); //выход из критической секции 4-ой вилки
	return 0; //возвращение нулевого значение
}