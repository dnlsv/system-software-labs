#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <vector>

using namespace std;

const int NUMBEROFELEMENTS = 5;

void main(void)
{
	setlocale(LC_ALL, "rus");

	HANDLE NPipe;
	DWORD BytesWritten;

	LPCTSTR path = L"\\\\.\\Pipe\\pipe1";

	if (WaitNamedPipe(path, NMPWAIT_WAIT_FOREVER) == 0)
	{
		printf("�������� ���������� � ������� %d\n",
			GetLastError());
		return;
	}

	// �������� ��������� ��
	if ((NPipe = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, (LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL)) == INVALID_HANDLE_VALUE)
	{
		printf("�������� ����� � ������� %d\n",
			GetLastError());
		return;
	}

	vector<double> vect;
	double number;

	cout << "������� " << NUMBEROFELEMENTS << " ��������� �������:" << endl;

	for (int i = 0; i < NUMBEROFELEMENTS; i++)
	{
		cin >> number;
		vect.push_back(number);
	}

	char cnum[256];
	string str = "";
	char buf[256];

	for (int i = 0; i < NUMBEROFELEMENTS; i++)
	{
		sprintf_s(cnum, "%f", vect.at(i));
		str = str + " " + cnum;
	}
	str.erase(0, 1);
	str = str + " ";

	for (int i = 0; i < str.length(); i++)
	{
		buf[i] = str.at(i);
	}
	buf[str.length()] = '\0';

	if (WriteFile(NPipe, buf, strlen(buf), &BytesWritten, NULL) == 0)
	{
		printf("������ � ���� � ������� %d\n", GetLastError());
		CloseHandle(NPipe);
		return;
	}

	printf("�������� %d ������\n", BytesWritten);

	CloseHandle(NPipe);
}
