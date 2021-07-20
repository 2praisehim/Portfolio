#pragma once

#include "MatgoGameClientDlg.h"

// SelectPaeDlg 대화 상자입니다.

class SelectPaeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelectPaeDlg)

public:
	SelectPaeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SelectPaeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int sel[2];
	int SelectPae;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
