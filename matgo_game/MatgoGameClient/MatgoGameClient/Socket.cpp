#include "stdafx.h"
#include "Socket.h"
#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9001
#define BUFSIZE    512
SOCKET sock;
int retval;
Socket::Socket()
{
	sock = NULL;
	
}


Socket::~Socket()
{
}

int Socket::Connect()
{
	

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) error.err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) error.err_quit("connect()");

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE + 1];
	char receive_buf[BUFSIZE + 1];
	int len;

	// ���� ����
	//WSACleanup();
	return 0;
}

int Socket::Send(char msg[])
{
	retval = send(sock, msg, strlen(msg), 0);
	return retval;
}


