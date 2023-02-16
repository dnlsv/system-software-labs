#include <iostream>

using namespace std; //использование пространства имен std

int main()
{
	setlocale(LC_ALL, "rus"); //установка локали

	string time1, time2;
	cout << "Введите два значения времени" << endl;

	cout << endl;
	cout << "1 время: ";
	cin >> time1; //ввод первого значения времени
	cout << "2 время: ";
	cin >> time2; //ввод второго значения времени

	int hour1, hour2, minute1, minute2, second1, second2;

	second1 = atoi(time1.substr(6, 2).c_str()); //перевод часов из string в int
	second2 = atoi(time2.substr(6, 2).c_str());

	minute1 = atoi(time1.substr(3, 2).c_str()); //перевод минут из string в int
	minute2 = atoi(time2.substr(3, 2).c_str());

	hour1 = atoi(time1.substr(0, 2).c_str()); //перевод секунд из string в int
	hour2 = atoi(time2.substr(0, 2).c_str());

	int hour = 0, minute = 0, second = 0;
	
	//алгоритм расчета количества часов, минут и секунл между двумя значениями времени
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

	seconds = hour * 60 * 60 + minute * 60 + second; //расчет количества секунд между двумя значениями времени

	cout << endl << "Полное количество секунд между двумя значениями времени: " << seconds << endl;


	return 0;
}