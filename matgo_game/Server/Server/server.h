#pragma once
#include <winsock2.h>
#include <stdio.h>


void err_quit(char *msg);
void err_display(char *msg);
int Send_Player1(char msg[]);
int Send_Player2(char msg[]);
DWORD WINAPI ProcessClient(LPVOID arg);

static int count=0 ;
static int START = 0;

static int Cli_player1;
static int Cli_player2;