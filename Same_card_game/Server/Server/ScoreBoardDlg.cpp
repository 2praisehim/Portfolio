// ScoreBoardDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Server.h"
#include "ScoreBoardDlg.h"
#include "afxdialogex.h"
#include "ServerDlg.h"

#define MAX 5

// CScoreBoardDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CScoreBoardDlg, CDialog)

CScoreBoardDlg::CScoreBoardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScoreBoardDlg::IDD, pParent)
{

}

CScoreBoardDlg::~CScoreBoardDlg()
{
}

void CScoreBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScoreBoardDlg, CDialog)
END_MESSAGE_MAP()


// CScoreBoardDlg �޽��� ó�����Դϴ�.


BOOL CScoreBoardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CServerDlg *dlg = (CServerDlg*)AfxGetMainWnd();//DialogŬ���� ���� ����

	int i, j;
	int Rank[MAX];
	CString RankSTR[MAX];

	for(i=0; i<MAX; i++)
	{
		Rank[i]=1;//��� 1������ �ʱ�ȭ
	}

	//������ ���� ������ ������ ��� 1�� ����
	for(i=0; i<MAX; i++)
	{
		for(j=0; j<MAX; j++)
		{
			if(dlg->Score[i] < dlg->Score[j])
			{
				++Rank[i];				
			}
		}
	}

	for(int k=0; k<MAX; k++)
	{
		if(dlg->Score[k]!=1)
		//������ ������ ������ 1�̾ƴϹǷ� ����� ����
		{
			dlg->ScoreSTR[k].Format(_T("%d��"),dlg->Score[k]);
			RankSTR[k].Format(_T("%d�� :"),Rank[k]);
		}
		else//������ ������ ������ 1�̹Ƿ� ���ٰ� ǥ��
		{
			dlg->ScoreSTR[k]=_T("");
			RankSTR[k].Format(_T("����"));
		}
	}
	//�����͸� �� ����ش�.
	SetDlgItemText(IDC_RANK1,RankSTR[0]);
	SetDlgItemText(IDC_USER1,dlg->UserID[0]);
	SetDlgItemText(IDC_SCORE1,dlg->ScoreSTR[0]);
	SetDlgItemText(IDC_RANK2,RankSTR[1]);
	SetDlgItemText(IDC_USER2,dlg->UserID[1].Mid(1));
	SetDlgItemText(IDC_SCORE2,dlg->ScoreSTR[1]);
	SetDlgItemText(IDC_RANK3,RankSTR[2]);
	SetDlgItemText(IDC_USER3,dlg->UserID[2].Mid(1));
	SetDlgItemText(IDC_SCORE3,dlg->ScoreSTR[2]);
	SetDlgItemText(IDC_RANK4,RankSTR[3]);
	SetDlgItemText(IDC_USER4,dlg->UserID[3].Mid(1));
	SetDlgItemText(IDC_SCORE4,dlg->ScoreSTR[3]);
	SetDlgItemText(IDC_RANK5,RankSTR[4]);
	SetDlgItemText(IDC_USER5,dlg->UserID[4].Mid(1));
	SetDlgItemText(IDC_SCORE5,dlg->ScoreSTR[4]);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
