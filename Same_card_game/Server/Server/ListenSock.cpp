// ListenSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Server.h"
#include "ListenSock.h"


// CListenSock

CListenSock::CListenSock()
{
}

CListenSock::~CListenSock()
{
}


// CListenSock ��� �Լ�


void CListenSock::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CServerApp*)AfxGetApp())->Accept();
	CAsyncSocket::OnAccept(nErrorCode);
}
