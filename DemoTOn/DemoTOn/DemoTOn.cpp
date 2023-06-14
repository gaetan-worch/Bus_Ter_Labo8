// DemoTOn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "Ton.h"
#include <winsock2.h>
#include <WS2tcpip.h>

#define IP "192.168.1.201"
#define PORT 502

#define PERIOD 250


int main()
{
	WSADATA info;
	SOCKET socket_client;
	struct sockaddr_in server_address;
	struct sockaddr_in response_source_address;


	WSAStartup(MAKEWORD(2, 2), &info);

	socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &server_address.sin_addr);

	/*TOn timer;
	TOn_Initialize(&timer);
	for (;;)
	{
		if (TOn_IsElapsed(&timer))
		{
			printf("Tick\n");
			TOn_Start(&timer, PERIOD);
		}
	}
	printf("Hello\n");*/
}

