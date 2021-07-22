
// Server.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "ListenSock.h"
#include "ChildSock.h"

// CServerApp:
// �� Ŭ������ ������ ���ؼ��� Server.cpp�� �����Ͻʽÿ�.
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

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

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