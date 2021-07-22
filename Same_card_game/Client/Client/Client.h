
// Client.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"
#include "ClientSock.h"
// �� ��ȣ�Դϴ�.


// CClientApp:
// �� Ŭ������ ������ ���ؼ��� Client.cpp�� �����Ͻʽÿ�.
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

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

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