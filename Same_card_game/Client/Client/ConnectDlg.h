#pragma once


// CConnectDlg 대화 상자입니다.

class CConnectDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConnectDlg();
	
	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONNECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strAddress;
	afx_msg void OnBnClickedOk();
};
