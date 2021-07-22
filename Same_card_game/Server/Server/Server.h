
// Server.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "ListenSock.h"
#include "ChildSock.h"

// CServerApp:
// 이 클래스의 구현에 대해서는 Server.cpp을 참조하십시오.
//

struct Packet
	{
		char header;
		char IDlen;
		CString ID;
		CString data;
	};

class CServerApp : public CWinApp
{
public:
	CServerApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
public:
	void InitServer(void);
	void Accept(void);
	void SendData(char& header, CString& id, CString& str);
	void ReceiveData(CChildSock* ClientAddress);
	void CloseChild(void);
	void CleanUp(void);
	CListenSock* m_pServer;
	CChildSock* m_pChild;
	CTypedPtrList<CObList,CChildSock*> m_pClient;
	CString QueC;
	CString AnsC;
	void SendPicture(char& header, CString& id, CPoint& ptStart, CPoint& ptEnd);
	void SendThickness(char& header, CString& id, int& thickness);
	int ThicknessC;
	void SendColor(char& header, CString& id, int& Red, int& Green, int& Blue);
	COLORREF ColorC;
	Packet packet;
	int cnum;
	int CReadyflag;
	int snum;
};

extern CServerApp theApp;