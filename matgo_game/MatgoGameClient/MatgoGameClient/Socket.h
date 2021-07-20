#pragma once
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "SocketError.h"


class Socket
{
public:
	Socket();
	~Socket();
	int Connect();
	SocketError error;
	int Send(char msg[]);

};

