#pragma once


// CConnectDlg ��ȭ �����Դϴ�.

class CConnectDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConnectDlg();
	
	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONNECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strAddress;
	afx_msg void OnBnClickedOk();
};
