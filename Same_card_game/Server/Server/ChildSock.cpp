// ChildSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Server.h"
#include "ChildSock.h"


// CChildSock

CChildSock::CChildSock()
{
}

CChildSock::~CChildSock()
{
}


// CChildSock ��� �Լ�


void CChildSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CServerApp*)AfxGetApp())->CloseChild();
	CAsyncSocket::OnClose(nErrorCode);
}


//void CChildSock::OnSend(int nErrorCode)
//{
//	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
//
//	CAsyncSocket::OnSend(nErrorCode);
//}


void CChildSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CServerApp*)AfxGetApp())->ReceiveData(this);
	CAsyncSocket::OnReceive(nErrorCode);
}
