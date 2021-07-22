#pragma once
#include "afxwin.h"


// CScoreBoardDlg 대화 상자입니다.

class CScoreBoardDlg : public CDialog
{
	DECLARE_DYNAMIC(CScoreBoardDlg)

public:
	CScoreBoardDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScoreBoardDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SCOREBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Score1;
	CStatic m_Score2;
	virtual BOOL OnInitDialog();
};
