#pragma once

#include "MatgoGameClientDlg.h"

// SelectPaeDlg ��ȭ �����Դϴ�.

class SelectPaeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelectPaeDlg)

public:
	SelectPaeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SelectPaeDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int sel[2];
	int SelectPae;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
