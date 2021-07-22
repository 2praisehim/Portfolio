// ScoreBoardDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Client.h"
#include "ScoreBoardDlg.h"
#include "afxdialogex.h"
#include "ClientDlg.h"

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
	DDX_Control(pDX, IDC_SCORE1, m_Score1);
	DDX_Control(pDX, IDC_SCORE2, m_Score2);
}


BEGIN_MESSAGE_MAP(CScoreBoardDlg, CDialog)
END_MESSAGE_MAP()


// CScoreBoardDlg �޽��� ó�����Դϴ�.


BOOL CScoreBoardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CClientDlg *dlg = (CClientDlg*)AfxGetMainWnd();//DialogŬ���� ���� ����

	int i, j;
	int Rank[MAX];
	CString RankSTR[MAX];

	for(i=0; i<MAX; i++)
	{
		Rank[i]=1;//��� 1������ �ʱ�ȭ
	}

	//������ ���� ������ ������ +1
	for(i=0; i<MAX; i++)
	{
		for(j=0; j<MAX; j++)
		{
			if(dlg->UserScore[i] < dlg->UserScore[j])
			{
				++Rank[i];				
			}
		}
	}

	for(int k=0; k<MAX; k++)
	{
		if(dlg->UserScore[k]!=1)
		{
			dlg->UserScoreSTR[k].Format(_T("%d��"),dlg->UserScore[k]);
			RankSTR[k].Format(_T("%d�� :"),Rank[k]);
		}
		else
		{
			dlg->UserScoreSTR[k]=_T("");
			RankSTR[k].Format(_T("����"));
		}
	}
	SetDlgItemText(IDC_RANK1,RankSTR[0]);
	SetDlgItemText(IDC_USER1,dlg->UserID[0]);
	SetDlgItemText(IDC_SCORE1,dlg->UserScoreSTR[0]);
	SetDlgItemText(IDC_RANK2,RankSTR[1]);
	SetDlgItemText(IDC_USER2,dlg->UserID[1]);
	SetDlgItemText(IDC_SCORE2,dlg->UserScoreSTR[1]);
	SetDlgItemText(IDC_RANK3,RankSTR[2]);
	SetDlgItemText(IDC_USER3,dlg->UserID[2]);
	SetDlgItemText(IDC_SCORE3,dlg->UserScoreSTR[2]);
	SetDlgItemText(IDC_RANK4,RankSTR[3]);
	SetDlgItemText(IDC_USER4,dlg->UserID[3]);
	SetDlgItemText(IDC_SCORE4,dlg->UserScoreSTR[3]);
	SetDlgItemText(IDC_RANK5,RankSTR[4]);
	SetDlgItemText(IDC_USER5,dlg->UserID[4]);
	SetDlgItemText(IDC_SCORE5,dlg->UserScoreSTR[4]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
