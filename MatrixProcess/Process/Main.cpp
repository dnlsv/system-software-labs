#include <windows.h> //подключение библиотеки windows.h

int main() //создание главной функции main

{
    STARTUPINFO start = { sizeof(start) }; //создание структуры STARTUPINFO

    PROCESS_INFORMATION procinfo; //создание структуры PROCESS_INFORMATION

    TCHAR CommandLine[] = TEXT("..\\Debug\\Matrix\\Matrix.exe"); //создание массива типа TCHAR

    CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &start, &procinfo); //вызов функции создания процесса CreateProcess

    return 0; //возвращение нулевого значения
}