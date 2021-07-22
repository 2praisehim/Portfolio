#pragma once

// CListenSock 명령 대상입니다.

class CListenSock : public CAsyncSocket
{
public:
	CListenSock();
	virtual ~CListenSock();
	virtual void OnAccept(int nErrorCode);
};


