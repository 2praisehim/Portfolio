
// MatgoGameClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMatgoGameClientApp:
// �� Ŭ������ ������ ���ؼ��� MatgoGameClient.cpp�� �����Ͻʽÿ�.
//

class CMatgoGameClientApp : public CWinApp
{
public:
	CMatgoGameClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMatgoGameClientApp theApp;