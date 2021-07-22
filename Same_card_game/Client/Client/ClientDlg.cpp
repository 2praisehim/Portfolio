
// ClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "ScoreBoardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CClientDlg 대화 상자




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


// CClientDlg 메시지 처리기

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData();
	m_ctrSpin.SetRange(1,20);//선두께 범위 설정
	UDACCEL accels[]={{0,1}};//두께 1씩 증가
	m_ctrSpin.SetAccel(1,accels);
	m_ctrSpin.SetPos(1);//스핀 컨트롤의 현재 위치값 지정

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_RECONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_READY)->EnableWindow(FALSE);
	m_TextC.SetWindowTextW(ScoreC);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnClickedConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemTextW(IDC_CLIENTID,m_CID);	//Editcontrol로 부터 ID값을 받아옴
	TCHAR *tchr;
	CString str=_T("");
	if(m_CID.IsEmpty())		//닉네임을 안적었을 때
		AfxMessageBox(_T("ID를 입력해주세요"));
	else	//닉네임을 적었을 때
	{
		if(m_CID.GetLength()>=10)	//닉네임이 10자 이상일때
		{
			AfxMessageBox(_T("ID를 10자 밑으로 설정해주세요"));
			SetDlgItemText(IDC_CLIENTID,_T(""));	//Edit칸 비우기
			m_CID=_T("");	//닉네임 변수 초기화
		}
		else
		{
			int NotEnglish=0;
			for(int i=0;i<m_CID.GetLength();i++)	//닉네임에 영어가 아닌게 있는지 판별
			{
				str=m_CID.Mid(i,1);
				tchr=(TCHAR*)(LPCTSTR)str;
				if(!IsCharAlpha(*tchr))
					NotEnglish++;					//있으면 변수증가
				
			}
			if(NotEnglish>0)	//닉네임에 영어가 있을 때
			{
				AfxMessageBox(_T("ID를 영문으로만 해주세요"));
				SetDlgItemText(IDC_CLIENTID,_T(""));	//Edit칸 비우기
				m_CID=_T("");	//닉네임 변수 초기화
			}
			else	//영어 일 때
				((CClientApp*)AfxGetApp())->Connect();		//연결시도
			
		}
	}
}


void CClientDlg::OnClickedSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strData;
	h='M';
	GetDlgItemText(IDC_DATA, strData);//채팅데이터 받아옴
	((CClientApp*)AfxGetApp())->SendData(h,m_CID,strData);//채팅 데이터 전송
	SetDlgItemText(IDC_DATA,_T(""));
}


void CClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	pen_flag=TRUE;//마우스가 눌린상태를 나타냄
	SetCapture(); //마우스 메세지를 모두 캡쳐
	m_cpDraw=point;//현재 위치를 m_cpDraw에 저장한다.

	if(m_Mode==1)//문제출제모드일때
	{
		if(!m_QuestionC.IsEmpty())//문제를 출제했을때
		{	
			h='P';
			((CClientApp*)AfxGetApp())->SendPicture(h,m_CID,point, point);
			//현재 위치를 전송
			DrawPicture(m_cpDraw, point);//그림을 그린다.
			m_cpDraw=point;//현재 위치 다시저장
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CClientDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	pen_flag = FALSE;
	ReleaseCapture();//마우스 메세지 캡쳐를 중단한다.

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CClientDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_Mode==1)//문제출제모드일때
	{
		if(!m_QuestionC.IsEmpty())//문제를 출제했을 때
		{
			Clear=_T("");
			h='E';
			((CClientApp*)AfxGetApp())->SendData(h,m_CID,Clear);
			//문제출제모드일때만 화면지워지는 신호를 보낸다.
			PictureClear();//화면 지우기
		}
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CClientDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	h='P';
	if(m_Mode==1)//문제출제 모드일때
	{
		if(!m_QuestionC.IsEmpty())//문제가 출제되어야만 그림을 그릴수 있게 설정
		{
			if(pen_flag)//마우스가 눌린상태일때
			{
				h='P';
				((CClientApp*)AfxGetApp())->SendPicture(h,m_CID,m_cpDraw, point);
				//위치를 전송한다.
				DrawPicture(m_cpDraw, point);//그림을 그린다.
				m_cpDraw=point;//현재 위치 다시저장
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientApp *App=(CClientApp*)AfxGetApp();//App클래스 선언
	timerC=CTime::GetCurrentTime(); //현재 시간을 얻어옴
	if(nIDEvent==1)
	{
		int pos=m_GameTimebar.GetPos();	// Progress의 위치를 가져온다
		if(pos>0)	//제한시간이 남아있다면
		{
			pos--;	//시간을 감소시킴
			m_GameTimebar.SetPos(pos);
		}
		else	//제한시간 3분이 끝나면
		{
			KillTimer(1);//타이머를 끝낸다.
			++gameturn;
			if(gameturn>App->unum)//게임의 순서가 유저수를 넘게되면 0으로 초기화
			{
				gameturn=0;
				++circle;//게임순서가 한서클 돌면 서클변수 증가
			}
			if(circle!=2)
			{
				if(m_Mode==1)//문제 출제모드일 때
					AfxMessageBox(_T("제한시간이 끝났습니다."));
				else if(m_Mode==2)//정답 맞추기 모드일 때
					AfxMessageBox(_T("제한시간안에 정답을 맞추지 못하였습니다 ㅠ"));
				if(gameturn==myturn)
					OnBnClickedQuestionmode();	//출제자 모드
				else
					OnBnClickedAnswermode();	//정답자 모드
			}
			else
			{
				if(m_Mode==1)//문제 출제모드일 때
				{
					AfxMessageBox(_T("제한시간이 끝났습니다."));
					int finishflag=7;
					CString str;
					h='F';
					str.Format(_T("%d"),finishflag);
					App->SendData(h,m_CID,str);//게임순서가 3바퀴를 다 돌았을 때 보내어 결과를 요청함
					FinishGame();
				}
				else if(m_Mode==2)//정답 맞추기 모드일 때
					AfxMessageBox(_T("제한시간안에 정답을 맞추지 못하였습니다 ㅠ"));
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CClientDlg::OnBnClickedLinecolor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_color=m_ColorButton.GetColor();//색 설정한값 선에 적용
	int R, G, B;
	h='L';
	//선에 적용된 색상의 R,G,B값을 받아온다.
	R=GetRValue(m_color);
	G=GetGValue(m_color);
	B=GetBValue(m_color);
	((CClientApp*)AfxGetApp())->SendColor(h,m_CID,R,G,B);
	//받아온 R,G,B값을 클라이언트에게 보낸다.
}


void CClientDlg::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	h='T';
	if(pNMUpDown->iDelta > 0)	//증가버튼 눌렀을때
	{
		if(m_Thickness >= 20)
			return;
			
		m_Thickness ++;		//선이 1단계 두꺼워진다.
		((CClientApp*)AfxGetApp())->SendThickness(h,m_CID,m_Thickness);
		//선두께가 바뀔때마다 서버에게 전송
	}
	else						//감소버튼 눌렀을때
	{
		if(m_Thickness <=1)
			return;
		
		m_Thickness --;		//선이 1단계 얇아진다.
		((CClientApp*)AfxGetApp())->SendThickness(h,m_CID,m_Thickness);
		//선두께가 바뀔때마다 서버에게 전송
	}

	*pResult = 0;
}


void CClientDlg::OnBnClickedQuestionmode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Mode=1;
	PictureClear();//화면지우기
	SetDlgItemText(IDC_ANSWER,_T(""));//정답란 지우기
	m_AnswerC.Empty();//정답변수 초기화
	b=0;//점수 초기화
	COLORREF black=(0,0,0);
	m_ColorButton.SetColor(black);//컬러버튼의 색을 검정색으로 초기화
	m_color=m_ColorButton.GetColor();//색 설정한값 선에 적용
	m_Thickness=1;//선두께 초기화
	KillTimer(1);//모드바뀌면 타이머 끄고
	StartTimeC=0;//시작,종료시간 초기화
	EndTimeC=0;
	m_GameTimebar.SetRange(0,0);//제한시간 초기화
	AfxMessageBox(_T("문제출제 모드입니다.\r\n문제를 먼저 출제해주세요!"));
}


void CClientDlg::OnBnClickedAnswermode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CClientApp *App=(CClientApp *)AfxGetApp();//App클래스 선언
	m_Mode=2;
	PictureClear();//화면지우기
	SetDlgItemText(IDC_QUESTION,_T(""));//문제란 지우기
	m_QuestionC.Empty();//문제변수 초기화
	b=0;//점수 초기화
	App->ColorS=(0,0,0);//검정색으로 초기화
	m_ColorButton.SetColor(App->ColorS);//컬러버튼의 색을 검정색으로 초기화
	App->ThicknessS=1;//선두께 초기화
	KillTimer(1);//모드바뀌면 타이머 끄고
	StartTimeC=0;//시작,종료시간 초기화
	EndTimeC=0;
	m_GameTimebar.SetRange(0,0);//제한시간 초기화
	AfxMessageBox(_T("정답맞추기 모드입니다.\r\n상대방이 그린 그림을 맞추세요!"));
}


void CClientDlg::OnBnClickedButtonAnswer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_Mode==0)//모드선택 전에는 문제, 정답 란에 쓰지 못하게 설정
	{
		AfxMessageBox(_T("모드를 설정해주세요."));
		SetDlgItemText(IDC_ANSWER,_T(""));//정답란 비우기
		m_AnswerC.Empty();//정답변수 초기화
	}
	else if(m_Mode==2)//정답맞추기 모드
	{
		CClientApp *App=(CClientApp*)AfxGetApp();//App클래스 선언
		CString m_QuestionS=(App->QueS);//App클래스의 QueS변수를 가져다쓴다.
		GetDlgItemText(IDC_ANSWER,m_AnswerC);//정답란의 변수를 얻어온다.
		h='A';
		((CClientApp*)AfxGetApp())->SendData(h,m_CID,m_AnswerC);//정답데이터 전송
		if(!(m_AnswerC.Compare(m_QuestionS)))//정답을 맞췄을때
		//Compare함수를 써서 두 문자열이 같은지 아닌지 확인한다.(같으면 0)
		{
			m_AnswerC.Empty();//정답창 비우기

			if(m_AnswerC.IsEmpty())
			{
				EndTimeC=CTime::GetCurrentTime();//정지순간의 시간을 가져온다.
				CTimeSpan SubTime = EndTimeC - StartTimeC;//시작과 끝 시간의 차이를 구한다.
				int SubMinuteC = SubTime.GetMinutes();//시간차이구함
				if(SubMinuteC < 1)//시간차이에 따른 점수 분배
				//1분이내에 맞추면 10점
				{
					b=10;
					m_ScoreC+=b;
				}
				else if((1 <= SubMinuteC)&(SubMinuteC < 2))//1~2분사이 7점
				{
					b=7;
					m_ScoreC+=b;
				}
				else if((2 <= SubMinuteC)&(SubMinuteC < 3))//2~3분사이 3점
				{
					b=3;
					m_ScoreC+=b;
				}
				KillTimer(1);//정답맞추면 타이머 끄고
				StartTimeC=0;//시작,종료시간 초기화
				EndTimeC=0;
				m_GameTimebar.SetRange(0,0);
				PictureClear();//화면지우기
				SetDlgItemText(IDC_ANSWER,_T(""));//정답란 비우기
				ScoreC.Format(_T("%d"),m_ScoreC);//int->CString 형변환
				m_TextC.SetWindowTextW(ScoreC);//점수창에 점수카운팅
			}
		}
		else
		{
			AfxMessageBox(_T("틀렸습니다!"));
			SetDlgItemText(IDC_ANSWER,_T(""));//정답란 비우기
			m_AnswerC.Empty();//정답변수 초기화
		}
	}
	else //문제출제모드 일 때
	{
		AfxMessageBox(_T("정답맞추기 모드가 아닙니다."));
		SetDlgItemText(IDC_ANSWER,_T(""));//정답란 비우기
		m_AnswerC.Empty();//정답변수 초기화
	}
}


void CClientDlg::OnBnClickedButtonQuestion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_Mode==0)//모드선택 전에는 문제, 정답 란에 쓰지 못하게 설정
	{
		AfxMessageBox(_T("모드를 설정해주세요."));
		SetDlgItemText(IDC_QUESTION,_T(""));//문제란 비우기
		m_QuestionC.Empty();//변수 초기화
	}
	else if(m_Mode==1)//문제출제모드 일 때
	{
		GetDlgItemText(IDC_QUESTION, m_QuestionC);//문제를 변수로 받아온다.
		if(m_QuestionC.IsEmpty())//문제란이 비어있을 때
			AfxMessageBox(_T("문제를 출제해주세요."));
		else
		{
			h='Q';
			AfxMessageBox(_T("문제가 출제되었습니다.\r\n그림을 그려주세요."));
			((CClientApp*)AfxGetApp())->SendData(h,m_CID,m_QuestionC);//문제데이터 전송
			m_GameTimebar.SetRange(0,180);	//문제를 받아옴과 동시에 시간재기 시작
			m_GameTimebar.SetPos(180);		//제한시간 180초=3분
			SetTimer(1,1000,NULL);//문제를 출제함과 동시에 순간 타이머 시작
		}
	}
	else //정답맞추기 모드 일 때
	{
		AfxMessageBox(_T("문제 출제 모드가 아닙니다."));
		SetDlgItemText(IDC_QUESTION,_T(""));//문제란 비우기
		m_QuestionC.Empty();//문제변수 초기화
	}
}


BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if ( pMsg->wParam == VK_RETURN)//Enter버튼 동작설정
      {
         return TRUE;
		 OnClickedSend();
      }
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CClientDlg::StopQuestion(void)
{
	CClientApp *App=(CClientApp*)AfxGetApp();//App클래스 선언
	GetDlgItemText(IDC_QUESTION,m_QuestionC);//문제를 변수로 받아온다.
	CString m_AnswerS=App->AnsS;//App클래스의 AnsS 변수를 가져온다.
	if(!(m_QuestionC.Compare(m_AnswerS)))//상대방이 정답을 맞췄을때
	//Compare함수를 써서 두 문자열이 같은지 아닌지 확인한다.
	{
		CString notice;
		++gameturn;
		h='F';
		if(gameturn>App->unum)//게임의 순서가 유저수를 넘게되면 0으로 초기화
		{
			gameturn=0;
			circle++;//게임순서가 한서클 돌면 서클변수 증가
		}
		if(circle==2)
		{
			int finishflag=7;
			notice.Format(_T("%d%s"),finishflag,RecieveID);
			App->SendData(h,m_CID,notice);//게임순서가 3바퀴를 다 돌았을 때 보내어 결과를 요청함
		}
		else
		{
			notice.Format(_T("%d%s"),gameturn,RecieveID);
			App->SendData(h,m_CID,notice);//맞춘 유저의 닉네임과 게임순서를 다른 유저들에게 보냄
		}
		notice.Format(_T("%s님이 정답을 맞췄습니다!"),RecieveID);//맞춘 유저의 닉네임을 띄우면서 알림
		AfxMessageBox(notice);
		SetDlgItemText(IDC_QUESTION,_T(""));//문제 초기화
		m_QuestionC.Empty();//문제변수 초기화
		PictureClear();//화면 지우기
		m_Thickness=1;//선두께 초기화
		m_color=RGB(0,0,0);//선의 색상 초기화
		m_ctrSpin.SetPos(1);//스핀 컨트롤의 현재 위치값 지정
		RecieveID.Empty();
		if(circle!=2)
			OnBnClickedAnswermode();//답을 맞추는 차례로 바뀜
		else
			FinishGame();
	}
}


void CClientDlg::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_list.ResetContent();//대화목록을 비운다.
}


void CClientDlg::OnBnClickedReconnect()//서버 재연결
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CClientApp*)AfxGetApp())->Connect();
}

void CClientDlg::AllClear(void)//서버와연결이끊어지면 모든것을 초기화
{
	SetDlgItemText(IDC_ANSWER,_T(""));//정답란 초기화
	m_AnswerC.Empty();//정답변수 초기화
	SetDlgItemText(IDC_QUESTION,_T(""));//문제란 초기화
	m_QuestionC.Empty();//문제변수 초기화
	m_ScoreC=0;//점수초기화
	m_Thickness=1;//선두께 초기화
	m_ctrSpin.SetPos(1);//스핀 컨트롤의 현재 위치값 지정
	m_color=RGB(0,0,0);//선의 색상 초기화
	SetDlgItemText(IDC_SCORE,_T(""));//점수표시창 초기화(속성에서 Simple->True)
	m_list.ResetContent();//채팅방 초기화
	PictureClear();//그림 초기화
}


void CClientDlg::DrawPicture(CPoint& ptStart, CPoint& ptEnd)
{
	if(m_Mode==2)//정답맞추기 모드일때
	{
		CClientApp *App=(CClientApp*)AfxGetApp();//App클래스 선언
		m_Thickness=App->ThicknessS;//서버의 선두께를 받아온다.
		m_color=App->ColorS;//서버의 선색상을 받아온다.
	}
		
	CClientDC dc(this);//DC를 생성한다
								
	CPen pen;//펜을생성한다.
	pen.CreatePen(PS_SOLID, m_Thickness ,m_color);//펜의 속성을 설정한다.
	CPen* oldPen=dc.SelectObject(&pen);//DC에 펜을 선택
	dc.MoveTo(ptStart);//선그리기 시작점
	dc.LineTo(ptEnd);//선그리기 끝점
	dc.SelectObject(oldPen);//DC의 펜을 복구
}


void CClientDlg::PictureClear(void)
{
	Invalidate();//화면지우기
}


void CClientDlg::OnBnClickedReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	h='R';
	CString Ready=_T("");
	((CClientApp*)AfxGetApp())->SendData(h,m_CID,Ready);//Ready신호를 보낸다
	GetDlgItem(IDC_READY)->EnableWindow(FALSE);//버튼 비활성화
}


void CClientDlg::FinishGame()
{
	KillTimer(1);	//타이머 삭제
	PictureClear();//화면 지운다.
	m_GameTimebar.SetRange(0,0);//타이머 바 초기화
	if(m_Mode==1)
	{
		SetDlgItemText(IDC_ANSWER,_T(""));//정답란 지우기
		m_AnswerC.Empty();//정답변수 초기화
	}
	else
	{
		SetDlgItemText(IDC_QUESTION,_T(""));//문제란 지우기
		m_QuestionC.Empty();//문제변수 초기화
	}
	AfxMessageBox(_T("게임이 끝났습니다! \r\n결과를 확인하세요!"));
	Sendresult();
}

void CClientDlg::Sendresult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	h='S';
	((CClientApp*)AfxGetApp())->SendData(h,m_CID,ScoreC);//점수 데이터 보냄
}
