#include<iostream>
#include<stdio.h>
#include<winsock2.h>
#include "ws2tcpip.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning(disable:4996)

using namespace std;

const char* SERVER = "127.0.0.1";
const int BUFLEN = 512;
const int PORT = 8888;

int main(void)
{
	struct sockaddr_in client;
	int sock, socket_len = sizeof(client), recv_len;
	char buf[BUFLEN], str1[BUFLEN], str2[BUFLEN];
	WSADATA wsa;

	cout << "Client is running...";


	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "\n\nWSAStartup failed...";
		exit(EXIT_FAILURE);
	}

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		cout << "\n\nSocket failed...";
		exit(EXIT_FAILURE);
	}

	memset((char*)&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	client.sin_addr.S_un.S_addr = inet_addr(SERVER);

	while (true)
	{
		cout << "\n\nEnter 1 line: ";
		cin >> str1;
		cout << "Enter 2 line: ";
		cin >> str2;

		if (sendto(sock, str1, strlen(str1), 0, (struct sockaddr*)&client, socket_len) == SOCKET_ERROR)
		{
			cout << "\n\nSendto failed...";
			exit(EXIT_FAILURE);
		}

		if (sendto(sock, str2, strlen(str2), 0, (struct sockaddr*)&client, socket_len) == SOCKET_ERROR)
		{
			cout << "\n\nSendto failed...";
			exit(EXIT_FAILURE);
		}

		if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&client, &socket_len)) == SOCKET_ERROR)
			cout << "\nRecvfrom failed...\n";

		buf[recv_len] = '\0';

		if (buf[0] == 0)
			cout << "String concatenation: ";
		else
			cout << "Sum of numbers: ";

		if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&client, &socket_len)) == SOCKET_ERROR)
			cout << "\nRecvfrom failed...\n";

		buf[recv_len] = '\0';

		cout << buf;
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}