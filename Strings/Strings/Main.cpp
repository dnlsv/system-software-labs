#include <iostream>

using namespace std;

bool integerFun(string, string);
int sumFun(string, string);
string concatenationFun(string, string);

int main()
{
	setlocale(LC_ALL, "rus");

	string str1, str2;

	cout << "Введите 2 строки" << endl;
	cout << endl;

	cout << "1 строка: ";
	cin >> str1;
	cout << "2 строка: ";
	cin >> str2;

	int sum;
	string str;

	cout << endl;

	if (integerFun(str1, str2))
	{
		sum = sumFun(str1, str2);
		cout << "Сумма чисел: " << sum << endl;
	}
	else
	{
		str = concatenationFun(str1, str2);
		cout << "Конкатенация строк: " << str << endl;
	}

	return 0;
}

bool integerFun(string str1, string str2)
{
	bool flag = true;
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

	return flag;
}

int sumFun(string str1, string str2)
{
	int sum, a, b;

	a = atoi(str1.c_str());
	b = atoi(str2.c_str());

	sum = a + b;

	return sum;
}

string concatenationFun(string str1, string str2)
{
	string str;

	str = str1 + str2;

	return str;
}