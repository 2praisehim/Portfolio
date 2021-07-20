#pragma once
#include "stdio.h"
class SocketError
{
public:
	SocketError();
	~SocketError();
	void err_quit(char *msg);
	void err_display(char *msg);
};

