// ConnectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Client.h"
#include "ConnectDlg.h"
#include "afxdialogex.h"


// CConnectDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConnectDlg, CDialog)

CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
	, m_strAddress(_T(""))
{

}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConnectDlg 메시지 처리기입니다.


void CConnectDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_IPADDRESS1, m_strAddress);
	CDialog::OnOK();
}
