#include <iostream>

using namespace std; //������������� ������������ ���� std

int main()
{
	setlocale(LC_ALL, "rus"); //��������� ������

	string time1, time2;
	cout << "������� ��� �������� �������" << endl;

	cout << endl;
	cout << "1 �����: ";
	cin >> time1; //���� ������� �������� �������
	cout << "2 �����: ";
	cin >> time2; //���� ������� �������� �������

	int hour1, hour2, minute1, minute2, second1, second2;

	second1 = atoi(time1.substr(6, 2).c_str()); //������� ����� �� string � int
	second2 = atoi(time2.substr(6, 2).c_str());

	minute1 = atoi(time1.substr(3, 2).c_str()); //������� ����� �� string � int
	minute2 = atoi(time2.substr(3, 2).c_str());

	hour1 = atoi(time1.substr(0, 2).c_str()); //������� ������ �� string � int
	hour2 = atoi(time2.substr(0, 2).c_str());

	int hour = 0, minute = 0, second = 0;
	
	//�������� ������� ���������� �����, ����� � ������ ����� ����� ���������� �������
	if (hour1 < hour2)
	{
		if (minute1 < minute2)
		{
			hour = hour2 - hour1;
			if (second1 <= second2)
			{
				minute = minute2 - minute1;
				second = second2 - second1;
			}
			if (second1 > second2)
			{
				minute = minute2 - minute1 - 1;
				second = 60 - second1 + second2;
			}
		}
		if (minute1 > minute2)
		{
			hour = hour2 - hour1 - 1;
			if (second1 <= second2)
			{
				minute = 60 - minute1 + minute2;
				second = second2 - second1;
			}
			if (second1 > second2)
			{
				minute = 60 - minute1 + minute2 - 1;
				second = 60 - second1 + second2;
			}
		}
		if (minute1 == minute2)
		{
			if (second1 <= second2)
			{
				hour = hour2 - hour1;
				second = second2 - second1;
			}
			if (second1 > second2)
			{
				hour = hour2 - hour1 - 1;
				minute = 59;
				second = 60 - second1 + second2;
			}
		}
	}
	if (hour1 > hour2)
	{
		if (minute1 > minute2)
		{
			hour = hour1 - hour2;
			if (second1 >= second2)
			{
				minute = minute1 - minute2;
				second = second1 - second2;
			}
			if (second1 < second2)
			{
				minute = minute1 - minute2 - 1;
				second = 60 - second2 + second1;
			}
		}
		if (minute1 < minute2)
		{
			hour = hour1 - hour2 - 1;
			if (second1 < second2)
			{
				minute = 60 - minute2 + minute1 - 1;
				second = 60 - second2 + second1;
			}
			if (second1 >= second2)
			{
				minute = 12 - minute2 + minute1;
				second = second1 - second2;
			}
		}
		if (minute1 == minute2)
		{
			if (second1 < second2)
			{
				hour = hour1 - hour2 - 1;
				minute = 59;
				second = 60 - second2 + second1;
			}
			if (second1 >= second2)
			{
				hour = hour1 - hour2;
				second = second1 - second2;
			}
		}
	}
	if (hour1 == hour2)
	{
		if (minute1 < minute2)
		{
			if (second1 <= second2)
			{
				minute = minute2 - minute1;
				second = second2 - second1;
			}
			if (second1 > second2)
			{
				minute = minute2 - minute1 - 1;
				second = 60 - second1 + second2;
			}
		}
		if (minute1 > minute2)
		{
			if (second1 < second2)
			{
				minute = minute1 - minute2 - 1;
				second = 60 - second2 + second1;
			}
			if (second1 >= second2)
			{
				minute = minute1 - minute2;
				second = second1 - second2;
			}
		}
		if (minute1 == minute2)
		{
			if (second1 <= second2)
				second = second2 - second1;
			if (second1 > second2)
				second = second1 - second2;
		}
	}

	int seconds;

	seconds = hour * 60 * 60 + minute * 60 + second; //������ ���������� ������ ����� ����� ���������� �������

	cout << endl << "������ ���������� ������ ����� ����� ���������� �������: " << seconds << endl;


	return 0;
}