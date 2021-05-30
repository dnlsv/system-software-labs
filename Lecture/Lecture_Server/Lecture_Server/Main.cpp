#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

void main(void)
{
    setlocale(LC_ALL, "rus");

    HANDLE NPipe;
    char buffer[256];
    DWORD NumberOfBytesRead;

    LPCTSTR path = L"\\\\.\\Pipe\\pipe1";

    // Создание ИК
    if ((NPipe = CreateNamedPipe(path,
        PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 2000, NULL)) ==
        INVALID_HANDLE_VALUE)
    {
        printf("Ошибка при создании конвейера %d\n",
            GetLastError());
        return;
    }
    printf("Сервер запущен.\n");

    if (ConnectNamedPipe(NPipe, NULL) == 0)
    {
        printf("Ошибка при установлении соединения %d\n",
            GetLastError());
        CloseHandle(NPipe);
        return;
    }

    if (ReadFile(NPipe, buffer, sizeof(buffer), &NumberOfBytesRead, NULL) <= 0)
    {
        printf("Ошибка при чтении из конвейера %d\n",
            GetLastError());
        CloseHandle(NPipe);
        return;
    }

    buffer[NumberOfBytesRead] = '\0';

    string str;
    vector<double> vect;
    for (int i = 0; i < NumberOfBytesRead; i++)
    {
        str = str + buffer[i];
        if (buffer[i] == ' ')
        {
            vect.push_back(atof(str.c_str()));
            str = "";
        }
    }

    sort(vect.begin(), vect.end());

    for (int i = 0; i < vect.size(); i++)
    {
        cout << vect.at(i) << " ";
    }


    if (DisconnectNamedPipe(NPipe) == 0)
    {
        printf("Ошибка при разрыве соединения %d\n",
            GetLastError());
        return;
    }
    CloseHandle(NPipe);
}
