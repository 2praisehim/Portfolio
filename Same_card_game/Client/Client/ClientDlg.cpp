
// ClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "ScoreBoardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg ��ȭ ����




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
	, m_QuestionC(_T(""))
	, m_LineThickness(0)
	, m_AnswerC(_T(""))
	, m_ScoreC(0)
	, ScoreC(_T("0"))
	, m_Mode(0)
	, pen_flag(false)
	, timerC(0)
	, StartTimeC(0)
	, EndTimeC(0)
	, m_Thickness(0)
	, m_cpDraw(0)
	, b(0)
	, m_ServerQ(_T(""))
	, Clear(_T(""))
	, m_CID(_T(""))
	, myturn(0)
	, gameturn(0)
	, circle(0)
{
	m_Mode=0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_color=RGB(0,0,0);
	m_Thickness=1;
	b=0;
	m_ScoreC=0;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_QUESTION, m_QuestionC);
	DDX_Control(pDX, IDC_LINECOLOR, m_ColorButton);
	DDX_Control(pDX, IDC_SPIN, m_ctrSpin);
	DDX_Text(pDX, IDC_LINETHICKNESS, m_LineThickness);
	DDV_MinMaxInt(pDX, m_LineThickness, 0, 50);
	DDX_Text(pDX, IDC_ANSWER, m_AnswerC);
	DDX_Control(pDX, IDC_SCORE, m_TextC);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_CLIENTID, m_CID);
	DDX_Control(pDX, IDC_TIME_PROGRESS, m_GameTimebar);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CClientDlg::OnClickedConnect)
	ON_BN_CLICKED(IDC_SEND, &CClientDlg::OnClickedSend)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LINECOLOR, &CClientDlg::OnBnClickedLinecolor)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, &CClientDlg::OnDeltaposSpin)
	ON_BN_CLICKED(IDC_QUESTIONMODE, &CClientDlg::OnBnClickedQuestionmode)
	ON_BN_CLICKED(IDC_ANSWERMODE, &CClientDlg::OnBnClickedAnswermode)
	ON_BN_CLICKED(IDC_BUTTON_ANSWER, &CClientDlg::OnBnClickedButtonAnswer)
	ON_BN_CLICKED(IDC_BUTTON_QUESTION, &CClientDlg::OnBnClickedButtonQuestion)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CClientDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_RECONNECT, &CClientDlg::OnBnClickedReconnect)
	ON_BN_CLICKED(IDC_READY, &CClientDlg::OnBnClickedReady)
END_MESSAGE_MAP()


// CClientDlg �޽��� ó����

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData();
	m_ctrSpin.SetRange(1,20);//���β� ���� ����
	UDACCEL accels[]={{0,1}};//�β� 1�� ����
	m_ctrSpin.SetAccel(1,accels);
	m_ctrSpin.SetPos(1);//���� ��Ʈ���� ���� ��ġ�� ����

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_RECONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_READY)->EnableWindow(FALSE);
	m_TextC.SetWindowTextW(ScoreC);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnClickedConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemTextW(IDC_CLIENTID,m_CID);	//Editcontrol�� ���� ID���� �޾ƿ�
	TCHAR *tchr;
	CString str=_T("");
	if(m_CID.IsEmpty())		//�г����� �������� ��
		AfxMessageBox(_T("ID�� �Է����ּ���"));
	else	//�г����� ������ ��
	{
		if(m_CID.GetLength()>=10)	//�г����� 10�� �̻��϶�
		{
			AfxMessageBox(_T("ID�� 10�� ������ �������ּ���"));
			SetDlgItemText(IDC_CLIENTID,_T(""));	//Editĭ ����
			m_CID=_T("");	//�г��� ���� �ʱ�ȭ
		}
		else
		{
			int NotEnglish=0;
			for(int i=0;i<m_CID.GetLength();i++)	//�г��ӿ� ��� �ƴѰ� �ִ��� �Ǻ�
			{
				str=m_CID.Mid(i,1);
				tchr=(TCHAR*)(LPCTSTR)str;
				if(!IsCharAlpha(*tchr))
					NotEnglish++;					//������ ��������
				
			}
			if(NotEnglish>0)	//�г��ӿ� ��� ���� ��
			{
				AfxMessageBox(_T("ID�� �������θ� ���ּ���"));
				SetDlgItemText(IDC_CLIENTID,_T(""));	//Editĭ ����
				m_CID=_T("");	//�г��� ���� �ʱ�ȭ
			}
			else	//���� �� ��
				((CClientApp*)AfxGetApp())->Connect();		//����õ�
			
		}
	}
}


void CClientDlg::OnClickedSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strData;
	h='M';
	GetDlgItemText(IDC_DATA, strData);//ä�õ����� �޾ƿ�
	((CClientApp*)AfxGetApp())->SendData(h,m_CID,strData);//ä�� ������ ����
	SetDlgItemText(IDC_DATA,_T(""));
}


void CClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	pen_flag=TRUE;//���콺�� �������¸� ��Ÿ��
	SetCapture(); //���콺 �޼����� ��� ĸ��
	m_cpDraw=point;//���� ��ġ�� m_cpDraw�� �����Ѵ�.

	if(m_Mode==1)//������������϶�
	{
		if(!m_QuestionC.IsEmpty())//������ ����������
		{	
			h='P';
			((CClientApp*)AfxGetApp())->SendPicture(h,m_CID,point, point);
			//���� ��ġ�� ����
			DrawPicture(m_cpDraw, point);//�׸��� �׸���.
			m_cpDraw=point;//���� ��ġ �ٽ�����
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CClientDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	pen_flag = FALSE;
	ReleaseCapture();//���콺 �޼��� ĸ�ĸ� �ߴ��Ѵ�.

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CClientDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_Mode==1)//������������϶�
	{
		if(!m_QuestionC.IsEmpty())//������ �������� ��
		{
			Clear=_T("");
			h='E';
			((CClientApp*)AfxGetApp())->SendData(h,m_CID,Clear);
			//������������϶��� ȭ���������� ��ȣ�� ������.
			PictureClear();//ȭ�� �����
		}
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CClientDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	h='P';
	if(m_Mode==1)//�������� ����϶�
	{
		if(!m_QuestionC.IsEmpty())//������ �����Ǿ�߸� �׸��� �׸��� �ְ� ����
		{
			if(pen_flag)//���콺�� ���������϶�
			{
				h='P';
				((CClientApp*)AfxGetApp())->SendPicture(h,m_CID,m_cpDraw, point);
				//��ġ�� �����Ѵ�.
				DrawPicture(m_cpDraw, point);//�׸��� �׸���.
				m_cpDraw=point;//���� ��ġ �ٽ�����
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientApp *App=(CClientApp*)AfxGetApp();//AppŬ���� ����
	timerC=CTime::GetCurrentTime(); //���� �ð��� ����
	if(nIDEvent==1)
	{
		int pos=m_GameTimebar.GetPos();	// Progress�� ��ġ�� �����´�
		if(pos>0)	//���ѽð��� �����ִٸ�
		{
			pos--;	//�ð��� ���ҽ�Ŵ
			m_GameTimebar.SetPos(pos);
		}
		else	//���ѽð� 3���� ������
		{
			KillTimer(1);//Ÿ�̸Ӹ� ������.
			++gameturn;
			if(gameturn>App->unum)//������ ������ �������� �ѰԵǸ� 0���� �ʱ�ȭ
			{
				gameturn=0;
				++circle;//���Ӽ����� �Ѽ�Ŭ ���� ��Ŭ���� ����
			}
			if(circle!=2)
			{
				if(m_Mode==1)//���� ��������� ��
					AfxMessageBox(_T("���ѽð��� �������ϴ�."));
				else if(m_Mode==2)//���� ���߱� ����� ��
					AfxMessageBox(_T("���ѽð��ȿ� ������ ������ ���Ͽ����ϴ� ��"));
				if(gameturn==myturn)
					OnBnClickedQuestionmode();	//������ ���
				else
					OnBnClickedAnswermode();	//������ ���
			}
			else
			{
				if(m_Mode==1)//���� ��������� ��
				{
					AfxMessageBox(_T("���ѽð��� �������ϴ�."));
					int finishflag=7;
					CString str;
					h='F';
					str.Format(_T("%d"),finishflag);
					App->SendData(h,m_CID,str);//���Ӽ����� 3������ �� ������ �� ������ ����� ��û��
					FinishGame();
				}
				else if(m_Mode==2)//���� ���߱� ����� ��
					AfxMessageBox(_T("���ѽð��ȿ� ������ ������ ���Ͽ����ϴ� ��"));
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CClientDlg::OnBnClickedLinecolor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_color=m_ColorButton.GetColor();//�� �����Ѱ� ���� ����
	int R, G, B;
	h='L';
	//���� ����� ������ R,G,B���� �޾ƿ´�.
	R=GetRValue(m_color);
	G=GetGValue(m_color);
	B=GetBValue(m_color);
	((CClientApp*)AfxGetApp())->SendColor(h,m_CID,R,G,B);
	//�޾ƿ� R,G,B���� Ŭ���̾�Ʈ���� ������.
}


void CClientDlg::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	h='T';
	if(pNMUpDown->iDelta > 0)	//������ư ��������
	{
		if(m_Thickness >= 20)
			return;
			
		m_Thickness ++;		//���� 1�ܰ� �β�������.
		((CClientApp*)AfxGetApp())->SendThickness(h,m_CID,m_Thickness);
		//���β��� �ٲ𶧸��� �������� ����
	}
	else						//���ҹ�ư ��������
	{
		if(m_Thickness <=1)
			return;
		
		m_Thickness --;		//���� 1�ܰ� �������.
		((CClientApp*)AfxGetApp())->SendThickness(h,m_CID,m_Thickness);
		//���β��� �ٲ𶧸��� �������� ����
	}

	*pResult = 0;
}


void CClientDlg::OnBnClickedQuestionmode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Mode=1;
	PictureClear();//ȭ�������
	SetDlgItemText(IDC_ANSWER,_T(""));//����� �����
	m_AnswerC.Empty();//���亯�� �ʱ�ȭ
	b=0;//���� �ʱ�ȭ
	COLORREF black=(0,0,0);
	m_ColorButton.SetColor(black);//�÷���ư�� ���� ���������� �ʱ�ȭ
	m_color=m_ColorButton.GetColor();//�� �����Ѱ� ���� ����
	m_Thickness=1;//���β� �ʱ�ȭ
	KillTimer(1);//���ٲ�� Ÿ�̸� ����
	StartTimeC=0;//����,����ð� �ʱ�ȭ
	EndTimeC=0;
	m_GameTimebar.SetRange(0,0);//���ѽð� �ʱ�ȭ
	AfxMessageBox(_T("�������� ����Դϴ�.\r\n������ ���� �������ּ���!"));
}


void CClientDlg::OnBnClickedAnswermode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CClientApp *App=(CClientApp *)AfxGetApp();//AppŬ���� ����
	m_Mode=2;
	PictureClear();//ȭ�������
	SetDlgItemText(IDC_QUESTION,_T(""));//������ �����
	m_QuestionC.Empty();//�������� �ʱ�ȭ
	b=0;//���� �ʱ�ȭ
	App->ColorS=(0,0,0);//���������� �ʱ�ȭ
	m_ColorButton.SetColor(App->ColorS);//�÷���ư�� ���� ���������� �ʱ�ȭ
	App->ThicknessS=1;//���β� �ʱ�ȭ
	KillTimer(1);//���ٲ�� Ÿ�̸� ����
	StartTimeC=0;//����,����ð� �ʱ�ȭ
	EndTimeC=0;
	m_GameTimebar.SetRange(0,0);//���ѽð� �ʱ�ȭ
	AfxMessageBox(_T("������߱� ����Դϴ�.\r\n������ �׸� �׸��� ���߼���!"));
}


void CClientDlg::OnBnClickedButtonAnswer()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_Mode==0)//��弱�� ������ ����, ���� ���� ���� ���ϰ� ����
	{
		AfxMessageBox(_T("��带 �������ּ���."));
		SetDlgItemText(IDC_ANSWER,_T(""));//����� ����
		m_AnswerC.Empty();//���亯�� �ʱ�ȭ
	}
	else if(m_Mode==2)//������߱� ���
	{
		CClientApp *App=(CClientApp*)AfxGetApp();//AppŬ���� ����
		CString m_QuestionS=(App->QueS);//AppŬ������ QueS������ �����پ���.
		GetDlgItemText(IDC_ANSWER,m_AnswerC);//������� ������ ���´�.
		h='A';
		((CClientApp*)AfxGetApp())->SendData(h,m_CID,m_AnswerC);//���䵥���� ����
		if(!(m_AnswerC.Compare(m_QuestionS)))//������ ��������
		//Compare�Լ��� �Ἥ �� ���ڿ��� ������ �ƴ��� Ȯ���Ѵ�.(������ 0)
		{
			m_AnswerC.Empty();//����â ����

			if(m_AnswerC.IsEmpty())
			{
				EndTimeC=CTime::GetCurrentTime();//���������� �ð��� �����´�.
				CTimeSpan SubTime = EndTimeC - StartTimeC;//���۰� �� �ð��� ���̸� ���Ѵ�.
				int SubMinuteC = SubTime.GetMinutes();//�ð����̱���
				if(SubMinuteC < 1)//�ð����̿� ���� ���� �й�
				//1���̳��� ���߸� 10��
				{
					b=10;
					m_ScoreC+=b;
				}
				else if((1 <= SubMinuteC)&(SubMinuteC < 2))//1~2�л��� 7��
				{
					b=7;
					m_ScoreC+=b;
				}
				else if((2 <= SubMinuteC)&(SubMinuteC < 3))//2~3�л��� 3��
				{
					b=3;
					m_ScoreC+=b;
				}
				KillTimer(1);//������߸� Ÿ�̸� ����
				StartTimeC=0;//����,����ð� �ʱ�ȭ
				EndTimeC=0;
				m_GameTimebar.SetRange(0,0);
				PictureClear();//ȭ�������
				SetDlgItemText(IDC_ANSWER,_T(""));//����� ����
				ScoreC.Format(_T("%d"),m_ScoreC);//int->CString ����ȯ
				m_TextC.SetWindowTextW(ScoreC);//����â�� ����ī����
			}
		}
		else
		{
			AfxMessageBox(_T("Ʋ�Ƚ��ϴ�!"));
			SetDlgItemText(IDC_ANSWER,_T(""));//����� ����
			m_AnswerC.Empty();//���亯�� �ʱ�ȭ
		}
	}
	else //����������� �� ��
	{
		AfxMessageBox(_T("������߱� ��尡 �ƴմϴ�."));
		SetDlgItemText(IDC_ANSWER,_T(""));//����� ����
		m_AnswerC.Empty();//���亯�� �ʱ�ȭ
	}
}


void CClientDlg::OnBnClickedButtonQuestion()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_Mode==0)//��弱�� ������ ����, ���� ���� ���� ���ϰ� ����
	{
		AfxMessageBox(_T("��带 �������ּ���."));
		SetDlgItemText(IDC_QUESTION,_T(""));//������ ����
		m_QuestionC.Empty();//���� �ʱ�ȭ
	}
	else if(m_Mode==1)//����������� �� ��
	{
		GetDlgItemText(IDC_QUESTION, m_QuestionC);//������ ������ �޾ƿ´�.
		if(m_QuestionC.IsEmpty())//�������� ������� ��
			AfxMessageBox(_T("������ �������ּ���."));
		else
		{
			h='Q';
			AfxMessageBox(_T("������ �����Ǿ����ϴ�.\r\n�׸��� �׷��ּ���."));
			((CClientApp*)AfxGetApp())->SendData(h,m_CID,m_QuestionC);//���������� ����
			m_GameTimebar.SetRange(0,180);	//������ �޾ƿȰ� ���ÿ� �ð���� ����
			m_GameTimebar.SetPos(180);		//���ѽð� 180��=3��
			SetTimer(1,1000,NULL);//������ �����԰� ���ÿ� ���� Ÿ�̸� ����
		}
	}
	else //������߱� ��� �� ��
	{
		AfxMessageBox(_T("���� ���� ��尡 �ƴմϴ�."));
		SetDlgItemText(IDC_QUESTION,_T(""));//������ ����
		m_QuestionC.Empty();//�������� �ʱ�ȭ
	}
}


BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if ( pMsg->wParam == VK_RETURN)//Enter��ư ���ۼ���
      {
         return TRUE;
		 OnClickedSend();
      }
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CClientDlg::StopQuestion(void)
{
	CClientApp *App=(CClientApp*)AfxGetApp();//AppŬ���� ����
	GetDlgItemText(IDC_QUESTION,m_QuestionC);//������ ������ �޾ƿ´�.
	CString m_AnswerS=App->AnsS;//AppŬ������ AnsS ������ �����´�.
	if(!(m_QuestionC.Compare(m_AnswerS)))//������ ������ ��������
	//Compare�Լ��� �Ἥ �� ���ڿ��� ������ �ƴ��� Ȯ���Ѵ�.
	{
		CString notice;
		++gameturn;
		h='F';
		if(gameturn>App->unum)//������ ������ �������� �ѰԵǸ� 0���� �ʱ�ȭ
		{
			gameturn=0;
			circle++;//���Ӽ����� �Ѽ�Ŭ ���� ��Ŭ���� ����
		}
		if(circle==2)
		{
			int finishflag=7;
			notice.Format(_T("%d%s"),finishflag,RecieveID);
			App->SendData(h,m_CID,notice);//���Ӽ����� 3������ �� ������ �� ������ ����� ��û��
		}
		else
		{
			notice.Format(_T("%d%s"),gameturn,RecieveID);
			App->SendData(h,m_CID,notice);//���� ������ �г��Ӱ� ���Ӽ����� �ٸ� �����鿡�� ����
		}
		notice.Format(_T("%s���� ������ ������ϴ�!"),RecieveID);//���� ������ �г����� ���鼭 �˸�
		AfxMessageBox(notice);
		SetDlgItemText(IDC_QUESTION,_T(""));//���� �ʱ�ȭ
		m_QuestionC.Empty();//�������� �ʱ�ȭ
		PictureClear();//ȭ�� �����
		m_Thickness=1;//���β� �ʱ�ȭ
		m_color=RGB(0,0,0);//���� ���� �ʱ�ȭ
		m_ctrSpin.SetPos(1);//���� ��Ʈ���� ���� ��ġ�� ����
		RecieveID.Empty();
		if(circle!=2)
			OnBnClickedAnswermode();//���� ���ߴ� ���ʷ� �ٲ�
		else
			FinishGame();
	}
}


void CClientDlg::OnBnClickedButtonClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_list.ResetContent();//��ȭ����� ����.
}


void CClientDlg::OnBnClickedReconnect()//���� �翬��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CClientApp*)AfxGetApp())->Connect();
}

void CClientDlg::AllClear(void)//�����Ϳ����̲������� ������ �ʱ�ȭ
{
	SetDlgItemText(IDC_ANSWER,_T(""));//����� �ʱ�ȭ
	m_AnswerC.Empty();//���亯�� �ʱ�ȭ
	SetDlgItemText(IDC_QUESTION,_T(""));//������ �ʱ�ȭ
	m_QuestionC.Empty();//�������� �ʱ�ȭ
	m_ScoreC=0;//�����ʱ�ȭ
	m_Thickness=1;//���β� �ʱ�ȭ
	m_ctrSpin.SetPos(1);//���� ��Ʈ���� ���� ��ġ�� ����
	m_color=RGB(0,0,0);//���� ���� �ʱ�ȭ
	SetDlgItemText(IDC_SCORE,_T(""));//����ǥ��â �ʱ�ȭ(�Ӽ����� Simple->True)
	m_list.ResetContent();//ä�ù� �ʱ�ȭ
	PictureClear();//�׸� �ʱ�ȭ
}


void CClientDlg::DrawPicture(CPoint& ptStart, CPoint& ptEnd)
{
	if(m_Mode==2)//������߱� ����϶�
	{
		CClientApp *App=(CClientApp*)AfxGetApp();//AppŬ���� ����
		m_Thickness=App->ThicknessS;//������ ���β��� �޾ƿ´�.
		m_color=App->ColorS;//������ �������� �޾ƿ´�.
	}
		
	CClientDC dc(this);//DC�� �����Ѵ�
								
	CPen pen;//���������Ѵ�.
	pen.CreatePen(PS_SOLID, m_Thickness ,m_color);//���� �Ӽ��� �����Ѵ�.
	CPen* oldPen=dc.SelectObject(&pen);//DC�� ���� ����
	dc.MoveTo(ptStart);//���׸��� ������
	dc.LineTo(ptEnd);//���׸��� ����
	dc.SelectObject(oldPen);//DC�� ���� ����
}


void CClientDlg::PictureClear(void)
{
	Invalidate();//ȭ�������
}


void CClientDlg::OnBnClickedReady()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	h='R';
	CString Ready=_T("");
	((CClientApp*)AfxGetApp())->SendData(h,m_CID,Ready);//Ready��ȣ�� ������
	GetDlgItem(IDC_READY)->EnableWindow(FALSE);//��ư ��Ȱ��ȭ
}


void CClientDlg::FinishGame()
{
	KillTimer(1);	//Ÿ�̸� ����
	PictureClear();//ȭ�� �����.
	m_GameTimebar.SetRange(0,0);//Ÿ�̸� �� �ʱ�ȭ
	if(m_Mode==1)
	{
		SetDlgItemText(IDC_ANSWER,_T(""));//����� �����
		m_AnswerC.Empty();//���亯�� �ʱ�ȭ
	}
	else
	{
		SetDlgItemText(IDC_QUESTION,_T(""));//������ �����
		m_QuestionC.Empty();//�������� �ʱ�ȭ
	}
	AfxMessageBox(_T("������ �������ϴ�! \r\n����� Ȯ���ϼ���!"));
	Sendresult();
}

void CClientDlg::Sendresult()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	h='S';
	((CClientApp*)AfxGetApp())->SendData(h,m_CID,ScoreC);//���� ������ ����
}
