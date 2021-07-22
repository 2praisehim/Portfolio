// ScoreBoardDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Server.h"
#include "ScoreBoardDlg.h"
#include "afxdialogex.h"
#include "ServerDlg.h"

#define MAX 5

// CScoreBoardDlg 대화 상자입니다.

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


// CScoreBoardDlg 메시지 처리기입니다.


BOOL CScoreBoardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CServerDlg *dlg = (CServerDlg*)AfxGetMainWnd();//Dialog클래스 참조 선언

	int i, j;
	int Rank[MAX];
	CString RankSTR[MAX];

	for(i=0; i<MAX; i++)
	{
		Rank[i]=1;//모두 1등으로 초기화
	}

	//나보다 높은 점수가 있으면 등수 1개 증가
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
		//유저가 있으면 점수가 1이아니므로 제대로 저장
		{
			dlg->ScoreSTR[k].Format(_T("%d점"),dlg->Score[k]);
			RankSTR[k].Format(_T("%d등 :"),Rank[k]);
		}
		else//유저가 없으면 점수가 1이므로 없다고 표시
		{
			dlg->ScoreSTR[k]=_T("");
			RankSTR[k].Format(_T("없음"));
		}
	}
	//데이터를 다 띄워준다.
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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
