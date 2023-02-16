#include <iostream>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

const int BUFLEN = 512;
const int PORT = 8888;

bool IntegerFunction(string, string);
int SumFunction(string, string);
string ConcatenationFunction(string, string);

int main()
{
	SOCKET sock;
	struct sockaddr_in server;
	int socket_len, recv_len;
	char buf[BUFLEN];
	string str1, str2;
	WSADATA wsa;

	socket_len = sizeof(server);

	cout << "Server is running...";
	
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "\n\nWSAStartup failed...";
		exit(EXIT_FAILURE);
	}

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		cout << "\n\nSocket failed...";
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	if (bind(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		cout << "\n\nBind failed...";
		exit(EXIT_FAILURE);
	}

	while (true) 
	{
	
		cout << "\n\nWaiting for data...";
		fflush(stdout);

		memset(buf, ' ', BUFLEN);

		if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&server, &socket_len)) == SOCKET_ERROR)
		{
			cout << "\n\nRecvfrom failed...";
			exit(EXIT_FAILURE);
		}

		buf[recv_len] = '\0';
		str1 = string(buf);
		cout << "\n1 line: " << str1;

		if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&server, &socket_len)) == SOCKET_ERROR)
		{
			cout << "\n\nRecvfrom failed...";
			exit(EXIT_FAILURE);
		}

		buf[recv_len] = '\0';
		str2 = string(buf);
		cout << "\n2 line: " << str2;

		buf[0] = IntegerFunction(str1, str2);
		buf[1] = '\0';

		if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&server, socket_len) == SOCKET_ERROR)
		{
			cout << "\n\nSendto failed...";
			exit(EXIT_FAILURE);
		}

		if (IntegerFunction(str1, str2) == true)
		{
			int sum = SumFunction(str1, str2);
			sprintf_s(buf, "%d", sum);
			if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&server, socket_len) == SOCKET_ERROR)
			{
				cout << "\n\nSendto failed...";
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			string str = ConcatenationFunction(str1, str2);
			int i = 0;
			for (i = 0; i < str.length(); i++)
				buf[i] = str.at(i);
			buf[i+1] = '\0';

			if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&server, socket_len) == SOCKET_ERROR)
			{
				cout << "\n\nSendto failed...";
				exit(EXIT_FAILURE);
			}
		}

	}

	closesocket(sock);
	WSACleanup();

	return 0;
}

bool IntegerFunction(string str1, string str2)
{
	bool flag = true;
	if (str1.at(0) == '+' || str1.at(0) == '-' || (str1.at(0) >= '0' && str1.at(0) <= '9'))
	{
		if (str2.at(0) == '+' || str2.at(0) == '-' || (str2.at(0) >= '0' && str2.at(0) <= '9'))
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

int SumFunction(string str1, string str2)
{
	int sum, a, b;

	a = atoi(str1.c_str());
	b = atoi(str2.c_str());

	sum = a + b;

	return sum;
}

string ConcatenationFunction(string str1, string str2)
{
	string str;
	str = str1 + str2;

	return str;
}