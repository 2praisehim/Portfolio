
// MatgoGameClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "Socket.h"
#include "GameFunction.h"
#include "SelectPaeDlg.h"
// CMatgoGameClientDlg ��ȭ ����
class CMatgoGameClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMatgoGameClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATGOGAMECLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic pic1;
	Socket socket;
	int *paedata;


	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	
	static UINT ThreadFirst(LPVOID _mothod);



	virtual BOOL DestroyWindow();
	afx_msg void OnClickedReadybtn();
	
	CString myscore;
	CString opscore;
	 
};
