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
	printf(" 플레이어 %d 입장  \n", count);
	
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

	// 클라이언트와 데이터 통신
	while (1)
	{
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			printf("플레이어 %d 퇴장 \n");
			break;
		}
		else if (retval == 0)
			break;
		Sleep(10);

		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP /%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);
		Flag = strtok(buf, ",");

		if (!strncmp(Flag, GStart, sizeof(GStart) - 1))					//각 플레이어가 게임 시작 버튼 클릭시 게임시작
		{
			START++;
			if (START == 2)
				Start_Game();
		}
		else if (!strncmp(Flag, SELECT, sizeof(SELECT) - 1))			//5 플레이어로부터 자신의패와 기존의 open패를 각각1장씩 수신(득점일때)
		{
			Data = strtok(NULL, " ");
			SelectPae(Data, ntohs(clientaddr.sin_port));				
		}
		else if (!strncmp(Flag, NSELECT, sizeof(NSELECT) - 1))			//2-2 플레이어로부터 자신의패를 수신(득점이 아닐때)
		{
			Data = strtok(NULL, " ");
			NSelectPae(Data, ntohs(clientaddr.sin_port));
		}
		else if (!strncmp(Flag, ADD, sizeof(ADD) - 1))					//15: 플레이어가 추가 득점 할때 
		{
			Data = strtok(NULL, " ");
			Add_Score(Data, ntohs(clientaddr.sin_port));
		}
		else if (!strncmp(Flag, SELBONUS, sizeof(SELBONUS) - 1))					//15: 플레이어가 추가 득점 할때 
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




