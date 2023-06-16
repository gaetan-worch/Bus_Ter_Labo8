// DemoTOn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "Ton.h"
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

#define IP "192.168.1.201"
#define PORT 502

#define PERIOD 250

using namespace std;

uint16_t numero_message;

void manageUser() {
	//char chosenMenu;
	//do
	//{

	//	cout << "===========Machine graveur 3D=========="  << endl;
	//	cout << "1 - Reinitialiser axes" << endl;
	//	cout << "2 - Deplacement manuel du robot" << endl;
	//	cout << "3 - Charger une nouvelle piece" << endl;
	//		cout << "0 - Quitter" << endl << endl;
	//	cout << ">";
	//	chosenMenu = _getch();
	//	switch (chosenMenu)
	//	{
	//	case '1': Reset(); break;
	//	case '2': ManualJog(); break;
	//	case '3': ChangeEngravedPiece(); break;
	//	}
	//} while (chosenMenu != '0');
}

SOCKET socket_client;
struct sockaddr_in server_address;
struct sockaddr_in response_source_address;
char received_data[1024];
int received_data_size;


void modbus_06(uint16_t* trans_id, uint16_t reg_address, uint16_t reg_value, char* message_recu)
{
	uint8_t BufferReq[12] = { 0 }; // Buffer pour message de requete
	uint8_t BufferRep[12] = { 0 }; // Buffer pour message de reponse
	*trans_id++;
	// Trame modbus headers
	BufferReq[0] = (*trans_id >> 8) & 0x00FF;
	BufferReq[1] = *trans_id & 0x00FF;
	BufferReq[2] = 0x00; // protocole id = Modbus protocole = 0
	BufferReq[3] = 0x00;
	BufferReq[4] = 0x00; // Longeur fixe 6 octets
	BufferReq[5] = 0x06;
	BufferReq[6] = 0xFF; // unit id pas utilise
	BufferReq[7] = 0x06; // function code
	// Propre au mode 06
	BufferReq[8] = (reg_address >> 8) & 0x00FF;
	BufferReq[9] = reg_address & 0x00FF;
	BufferReq[10] = (reg_value >> 8) & 0x00FF;
	BufferReq[11] = reg_value & 0x00FF;
	// Envoi de la requete
	sendto(socket_client, (char *)BufferReq, sizeof(BufferReq), 0, (struct sockaddr*)&server_address, sizeof(server_address));
	int response_source_address_length = sizeof(response_source_address);
	// Reception de la reponse
	int received = recvfrom(socket_client, message_recu, 1024, 0, (struct sockaddr*)&response_source_address, &response_source_address_length);
}

void modbus_0F(uint16_t* trans_id, uint16_t start_address, uint16_t length, uint8_t byte_cnt, uint8_t data[], char* message_recu)
{
	const uint8_t data_size = sizeof(data)/ sizeof(data[0]);
	uint8_t BufferReq[13 + data_size] = { 0 }; // Buffer pour message de requete
	uint8_t BufferRep[12] = { 0 };           // Buffer pour message de reponse
	uint16_t length_mes = 2 + data_size;
	*trans_id++;
	// Trame modbus headers
	BufferReq[0] = (*trans_id >> 8) & 0x00FF;
	BufferReq[1] = *trans_id & 0x00FF;
	BufferReq[2] = 0x00; // protocole id = Modbus protocole = 0
	BufferReq[3] = 0x00;
	BufferReq[4] = (length_mes >> 8) & 0x00FF; // Longeur fixe 6 octets
	BufferReq[5] = length_mes & 0x00FF;
	BufferReq[6] = 0xFF; // unit id pas utilise
	BufferReq[7] = 0x0F; // function code
	// Propre au mode 0F
	BufferReq[8] = (start_address >> 8) & 0x00FF;
	BufferReq[9] = start_address & 0x00FF;
	BufferReq[10] = (length >> 8) & 0x00FF;
	BufferReq[11] = length & 0x00FF;
	BufferReq[12] = byte_cnt;
	for (int i = 0; i < data_size; i++)
	{
		BufferReq[13 + i] = data[i];
	}
	// Envoi de la requete
	sendto(socket_client, (char *)BufferReq, sizeof(BufferReq), 0, (struct sockaddr*)&server_address, sizeof(server_address));
	// Reception de la reponse
	int response_source_address_length = sizeof(response_source_address);
	int recieved = recvfrom(socket_client, message_recu, sizeof(BufferRep), 0, (struct sockaddr*)&server_address, &response_source_address_length);
}

void modbus_02(uint16_t* trans_id, uint16_t reg_address, uint16_t reg_value, char* message_recu)
{
	uint8_t BufferReq[12] = { 0 };  // Buffer pour message de requete
	uint8_t BufferRep[260] = { 0 }; // Buffer pour message de reponse
	*trans_id++;
	// Trame modbus headers
	BufferReq[0] = (*trans_id >> 8) & 0x00FF;
	BufferReq[1] = *trans_id & 0xF;
	BufferReq[2] = 0x00; // protocole id = Modbus protocole = 0
	BufferReq[3] = 0x00;
	BufferReq[4] = 0x00; // Longeur fixe 6 octets
	BufferReq[5] = 0x06;
	BufferReq[6] = 0xFF; // unit id pas utilise
	BufferReq[7] = 0x02; // function code
	// Propre au mode 06
	BufferReq[8] = (reg_address >> 8) & 0x00FF;
	BufferReq[9] = reg_address & 0x00FF;
	BufferReq[10] = (reg_value >> 8) & 0x00FF;
	BufferReq[11] = reg_value & 0x00FF;
	// Envoi de la requete
	sendto(socket_client, (char *)BufferReq, sizeof(BufferReq), 0, (struct sockaddr*)&server_address, sizeof(server_address));
	// Reception de la reponse
	int response_source_address_length = sizeof(response_source_address);
	int recieved = recvfrom(socket_client, message_recu, sizeof(BufferRep), 0, (struct sockaddr*)&server_address, &response_source_address_length);
}


void envoieMessage(uint16_t* trans_id, uint16_t reg_address, uint16_t reg_value, char* message_recu, char MsgEnvoie) {
	socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &server_address.sin_addr);
	connect(socket_client, (struct sockaddr*)&server_address, sizeof(server_address));

	switch (MsgEnvoie) {
	case '4': modbus_06(trans_id, reg_address, reg_value, message_recu);
		break;
	case '1': 
		uint8_t t[1] = { 0xFF };
		modbus_0F(trans_id, 0x0000, 8, 1, t, message_recu);
		break;
	}
	closesocket(socket_client);
}

int main()
{
	WSADATA info;

	WSAStartup(MAKEWORD(2, 2), &info);


	char receive[1024] = { 0 };
	envoieMessage(&numero_message, 0x1120, 0x0000, receive, '4');
	envoieMessage(&numero_message, 0x1120, 0x0000, receive, '1');

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

