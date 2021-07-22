#pragma once

// CChildSock 명령 대상입니다.

class CChildSock : public CAsyncSocket
{
public:
	CChildSock();
	virtual ~CChildSock();
	virtual void OnClose(int nErrorCode);
//	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


