#pragma comment(lib, "ws2_32")
#include "server.h"
#include <stdlib.h>
//#include <stdio.h>

#define SERVERPORT 9001


extern SOCKET client[2];

int cnt=0;



int main(void)
{
	int retval;
	
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	//char buf[BUFSIZE + 1];
	HANDLE hThread;
	DWORD ThreadID;

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client[cnt] = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if (cnt == 0)
			Cli_player1 = client[cnt];
		else if(cnt==1)
			Cli_player2= client[cnt];

		if (client[cnt] == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}
		
		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	
		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client[cnt],0, &ThreadID);
		if (hThread == NULL)
			printf("������ ���� ����\n");
		else
			CloseHandle(hThread);
		// Ŭ���̾�Ʈ�� ������ ���
		cnt++;
	}

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}


