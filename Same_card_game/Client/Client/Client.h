
// Client.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"
#include "ClientSock.h"
// 주 기호입니다.


// CClientApp:
// 이 클래스의 구현에 대해서는 Client.cpp을 참조하십시오.
//

struct Packet
	{
		char header;
		char IDlen;
		CString ID;
		CString data;
	};

class CClientApp : public CWinApp
{
public:
	CClientApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
public:
	CClientSock* m_pClient;
	void Connect(void);
	void SendData(char& header, CString& id, CString& str);
	void ReceiveData(void);
	void CloseChild(void);
	void CleanUp(void);
	CString QueS;
	CString AnsS;
	int Disconnect;
	CString StopDraw;
	void SendPicture(char& header, CString& id, CPoint& ptStart, CPoint& ptEnd);
	int ThicknessS;
	COLORREF ColorS;
	void SendThickness(char& header, CString& id, int& thickness);
	void SendColor(char& header, CString& id, int& Red, int& Green, int& Blue);
	Packet packet;
	int unum;
	int anotherC;
};

extern CClientApp theApp;