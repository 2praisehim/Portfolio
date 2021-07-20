#include "server.h"
#include "Matgo.h"
#define BUFSIZE    512


 SOCKET client[2];
 int User1;
 int User2;
 char *Flag;
 char *Data;
 char GStart[] = "start";
 char SELECT[] = "SELECT";
 char NSELECT[] = "NSELECT";
 char ADD[] = "ADD";
 char SELBONUS[] = "SELBONUS";
 char STOP[] = "STOP";
 char GOBAK[] = "GOBAK";

 struct Player player1;
 struct Player player2;
 struct Pae Cpae;

 char msg[10];
int Send_Player1(char msg[])
{
	int retval;	
	retval = send(client[0], msg, strlen(msg), 0);
	return retval;
}
int Send_Player2(char msg[])
{
	int retval;	
	retval = send(client[1], msg, strlen(msg), 0);
	return retval;
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	count++;
	printf(" �÷��̾� %d ����  \n", count);
	
	SOCKET client_sock = (SOCKET)arg;
	char buf[BUFSIZE + 1];
	SOCKADDR_IN clientaddr;
	int addrlen;
	int retval;
	sprintf(msg, "%s,%s%d","NAME", "Player", count);
	retval = send(client_sock, msg, strlen(msg), 0);
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);
	if (count == 1)
		User1 = ntohs(clientaddr.sin_port);
	else if (count == 2)
		User2 = ntohs(clientaddr.sin_port);

	// Ŭ���̾�Ʈ�� ������ ���
	while (1)
	{
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			printf("�÷��̾� %d ���� \n");
			break;
		}
		else if (retval == 0)
			break;
		Sleep(10);

		// ���� ������ ���
		buf[retval] = '\0';
		printf("[TCP /%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);
		Flag = strtok(buf, ",");

		if (!strncmp(Flag, GStart, sizeof(GStart) - 1))					//�� �÷��̾ ���� ���� ��ư Ŭ���� ���ӽ���
		{
			START++;
			if (START == 2)
				Start_Game();
		}
		else if (!strncmp(Flag, SELECT, sizeof(SELECT) - 1))			//5 �÷��̾�κ��� �ڽ����п� ������ open�и� ����1�徿 ����(�����϶�)
		{
			Data = strtok(NULL, " ");
			SelectPae(Data, ntohs(clientaddr.sin_port));				
		}
		else if (!strncmp(Flag, NSELECT, sizeof(NSELECT) - 1))			//2-2 �÷��̾�κ��� �ڽ����и� ����(������ �ƴҶ�)
		{
			Data = strtok(NULL, " ");
			NSelectPae(Data, ntohs(clientaddr.sin_port));
		}
		else if (!strncmp(Flag, ADD, sizeof(ADD) - 1))					//15: �÷��̾ �߰� ���� �Ҷ� 
		{
			Data = strtok(NULL, " ");
			Add_Score(Data, ntohs(clientaddr.sin_port));
		}
		else if (!strncmp(Flag, SELBONUS, sizeof(SELBONUS) - 1))					//15: �÷��̾ �߰� ���� �Ҷ� 
		{
			Data = strtok(NULL, " ");
			SelectBonus(Data, ntohs(clientaddr.sin_port));
		}
		else if (!strncmp(Flag, STOP, sizeof(STOP) - 1))
		{
			Stop(ntohs(clientaddr.sin_port));
		}
		else if (!strncmp(Flag, GOBAK, sizeof(GOBAK) - 1))
		{
			Stop(ntohs(clientaddr.sin_port));
		}
	}
	closesocket(client_sock);
}




