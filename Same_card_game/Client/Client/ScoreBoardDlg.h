#pragma once
#include "afxwin.h"


// CScoreBoardDlg ��ȭ �����Դϴ�.

class CScoreBoardDlg : public CDialog
{
	DECLARE_DYNAMIC(CScoreBoardDlg)

public:
	CScoreBoardDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CScoreBoardDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SCOREBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Score1;
	CStatic m_Score2;
	virtual BOOL OnInitDialog();
};
