#include <iostream>
#include <iomanip>

using namespace std;

//Алгоритм "решето Сундарама"
int sundaram(int n)
{
	int* a = new int[n];
	int i, j, k;

	memset(a, 0, sizeof(int) * n);

	for (i = 1; 3 * i + 1 < n; i++)
	{
		for (j = 1; (k = i + j + 2 * i * j) < n && j <= i; j++)
			a[k] = 1;
	}

	for (i = n - 1; i >= 1; i--)
		if (a[i] == 0)
		{
			return (2 * i + 1);
			break;
		}
	delete[] a;
}

//Алгоритм Евклида
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}

int main()
{
	cout << "Key generation..." << endl << endl;

	srand((unsigned)time(NULL));
	int p = rand() % 100;
	int q = rand() % 100;

	int p_simple = sundaram(p);
	int q_simple = sundaram(q);

	int n = p_simple * q_simple;
	int m = (p_simple - 1) * (q_simple - 1);

	int d, d_simple = 0;
	while (d_simple != 1)
	{
		d = rand() % 100;
		d_simple = gcd(d, m);
	}

	int e = 0, e_simple = 0;
	while (e_simple != 1)
	{
		e += 1;
		e_simple = (e * d) % m;
	}

	cout << "(" << setw(5) << e << ", " << setw(5) << n << ") - Open key" << endl;
	cout << "(" << setw(5) << d << ", " << setw(5) << n << ") - Secret key" << endl;

	string text;
	cout << endl << "Enter the text: ";
	cin >> text;

	int* crypto_text = new  int[text.length()];
	int* text_decrypt = new int[text.length()];

	int b = 301;
	int c;

	cout << endl << setw(5) << "Text" << setw(7) << "ASCII"
		<< setw(14) << "Crypto text" << setw(14)
		<< "ASCIIdecrypt" << setw(14) << "Text decrypt" << endl
		<< "-------------------------------------------------------" << endl;

	//ci = (mj^e)%n.

	for (unsigned int j = 0; j < text.length(); j++)
	{
		c = 1;
		int i = 0;
		int ASCIIcode = (static_cast<int>(text.at(j))) + b;

		while (i < e)
		{
			c = c * ASCIIcode;
			c = c % n;
			i++;
		}

		crypto_text[j] = c;
		b += 1;
	}

	b = 301;

	//mi = (ci ^ d) % n

	for (unsigned int j = 0; j < text.length(); j++)
	{
		m = 1;
		int i = 0;

		while (i < d)
		{
			m = m * crypto_text[j];
			m = m % n;
			i++;
		}
		m = m - b;
		text_decrypt[j] = m;
		b += 1;
	}

	for (unsigned int j = 0; j < text.length(); j++)
	{
		cout << setw(5) << text.at(j) << setw(7) << static_cast<int>(text.at(j)) << setw(14)
			<< crypto_text[j] << setw(14) << text_decrypt[j] << setw(14) << static_cast<char>(text_decrypt[j]) << endl;
	}

	delete[] crypto_text;
	delete[] text_decrypt;

	return 0;
}