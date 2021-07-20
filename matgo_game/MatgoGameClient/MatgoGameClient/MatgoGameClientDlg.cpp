
// MatgoGameClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MatgoGameClient.h"
#include "MatgoGameClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BUFSIZE 512
// 비트맵 초기화
int bitmap[50] = { IDB_BITMAP0,IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3, IDB_BITMAP4,IDB_BITMAP5, IDB_BITMAP6,IDB_BITMAP7,
IDB_BITMAP8,IDB_BITMAP9, IDB_BITMAP10,IDB_BITMAP11, IDB_BITMAP12,IDB_BITMAP13, IDB_BITMAP14,IDB_BITMAP15, IDB_BITMAP16,IDB_BITMAP17,
IDB_BITMAP18,IDB_BITMAP19, IDB_BITMAP20,IDB_BITMAP21, IDB_BITMAP22,IDB_BITMAP23, IDB_BITMAP24,IDB_BITMAP25, IDB_BITMAP26,IDB_BITMAP27,
IDB_BITMAP28,IDB_BITMAP29, IDB_BITMAP30,IDB_BITMAP31, IDB_BITMAP32,IDB_BITMAP33, IDB_BITMAP34,IDB_BITMAP35,IDB_BITMAP36,IDB_BITMAP37,
IDB_BITMAP38,IDB_BITMAP39, IDB_BITMAP40,IDB_BITMAP41, IDB_BITMAP42,IDB_BITMAP43, IDB_BITMAP44,IDB_BITMAP45, IDB_BITMAP46,IDB_BITMAP47, IDB_BITMAP48,IDB_BITMAP49 };
// picture control 초기화
int picture[11] = { IDC_PICTURE1,IDC_PICTURE2,IDC_PICTURE3,IDC_PICTURE4, IDC_PICTURE5,IDC_PICTURE6, IDC_PICTURE7,IDC_PICTURE8,
IDC_PICTURE9,IDC_PICTURE10, IDC_PICTURE11 };

int openpicture[11] = { IDC_OPENPICTURE1,IDC_OPENPICTURE2,IDC_OPENPICTURE3, IDC_OPENPICTURE4, IDC_OPENPICTURE5, IDC_OPENPICTURE6, IDC_OPENPICTURE7,IDC_OPENPICTURE8 
,IDC_OPENPICTURE9,IDC_OPENPICTURE10,IDC_OPENPICTURE11};
int Gwang[5] = { 30,31,32,33,34};
static int n = 0;
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

extern SOCKET sock;					//소켓 연결 외부변수
extern Player player;				// player 클래스 외부변수
GameFunction gamefunc(bitmap,picture,openpicture);				// GameFunction 클래스 선언
CMatgoGameClientDlg *pMainDlg;					//GameFunction에서 메인 다이얼로그 컨트롤하기위해 메인 다이얼로그 객체선언
SelectPaeDlg selDlg;							//2장의 패를 선택하는 다이얼로그
CString Opplayer(_T(""));
CString Myplayer(_T(""));
bool go = false;
int goscore = 0;
bool Check = false;
bool Click = true;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMatgoGameClientDlg 대화 상자



CMatgoGameClientDlg::CMatgoGameClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MATGOGAMECLIENT_DIALOG, pParent)
	, myscore(_T(""))
	, opscore(_T(""))
	//, Opplayer(_T(""))
	//, Myplayer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatgoGameClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE1, pic1);
	DDX_Text(pDX, IDC_MYSCORE, myscore);
	DDX_Text(pDX, IDC_OPSCORE, opscore);
	DDX_Text(pDX, IDC_OPPLAYER, Opplayer);
	DDX_Text(pDX, IDC_PLAYER, Myplayer);
}

BEGIN_MESSAGE_MAP(CMatgoGameClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	
	ON_BN_CLICKED(IDC_READYBtn, &CMatgoGameClientDlg::OnClickedReadybtn)
	
END_MESSAGE_MAP()


// CMatgoGameClientDlg 메시지 처리기

BOOL CMatgoGameClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	//char msg[] = "Hi";
//	int retval = send(sock, msg, strlen(msg), 0);
	pMainDlg = this;																//메인다이얼로그 객체 대입
	socket.Connect();																//소켓 연결
	CWinThread *thread = NULL;														//소켓 리시브 스레드 생성
	thread = AfxBeginThread(ThreadFirst, this);	
	if (thread == NULL)
		AfxMessageBox(L"Error");
	HBITMAP hbit;																	//묶음패 비트맵 이미지 출력
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAPBACK));
	CStatic *pic = (CStatic *)GetDlgItem(IDC_PICTURE11);
	pic->SetBitmap(hbit);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMatgoGameClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMatgoGameClientDlg::OnPaint()
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
		CPaintDC dc(this);
		CDC memdc;
		memdc.CreateCompatibleDC(&dc);
		CBitmap gwang,opgwang,dan,opdan,mung,opmung,pea,oppea, *oldbitmap;
		
		for (int i = 0; i < player.Gwang_len(); i++)					//자신 점수패(광) 비트맵 출력
		{
			gwang.LoadBitmapW(bitmap[player.Gwang_value(i)]);
			oldbitmap = memdc.SelectObject(&gwang);
			dc.BitBlt(480+(i*30), 860, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			gwang.DeleteObject();
		}
		for (int i = 0; i < player.Dan_len(); i++)					//자신 점수패(단) 비트맵 출력
		{
			dan.LoadBitmapW(bitmap[player.Dan_value(i)]);
			oldbitmap = memdc.SelectObject(&dan);
			dc.BitBlt(970 + (i * 30), 860, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			dan.DeleteObject();
		}
		for (int i = 0; i < player.Mung_len(); i++)					//자신 점수패(멍) 비트맵 출력
		{
			mung.LoadBitmapW(bitmap[player.Mung_value(i)]);
			oldbitmap = memdc.SelectObject(&mung);
			dc.BitBlt(680 + (i * 30), 860, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			mung.DeleteObject();
		}
		for (int i = 0; i < player.Peascore_len(); i++)					//자신 점수패(피) 비트맵 출력
		{
			pea.LoadBitmapW(bitmap[player.Peascore_value(i)]);
			oldbitmap = memdc.SelectObject(&pea);
			dc.BitBlt(480 + (i * 30), 618, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			pea.DeleteObject();
		}
		for (int i = 0; i < player.OpGwang_len(); i++)					//상대 점수패(광) 비트맵 출력
		{
			opgwang.LoadBitmapW(bitmap[player.OpGwang_value(i)]);
			oldbitmap = memdc.SelectObject(&opgwang);
			dc.BitBlt(0 + (i * 30), 0, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			opgwang.DeleteObject();
		}
		for (int i = 0; i < player.OpDan_len(); i++)					//상대 점수패(광) 비트맵 출력
		{
			opdan.LoadBitmapW(bitmap[player.OpDan_value(i)]);
			oldbitmap = memdc.SelectObject(&opdan);
			dc.BitBlt(490 + (i * 30), 0, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			opdan.DeleteObject();
		}
		for (int i = 0; i < player.OpMung_len(); i++)					//상대 점수패(멍) 비트맵 출력
		{
			opmung.LoadBitmapW(bitmap[player.OpMung_value(i)]);
			oldbitmap = memdc.SelectObject(&opmung);
			dc.BitBlt(245 + (i * 30), 0, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			opmung.DeleteObject();
		}
		for (int i = 0; i < player.OpPeascore_len(); i++)					//상대 점수패(피) 비트맵 출력
		{
			oppea.LoadBitmapW(bitmap[player.OpPeascore_value(i)]);
			oldbitmap = memdc.SelectObject(&oppea);
			dc.BitBlt(795 + (i * 30), 0, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			if (i > 14)
				dc.BitBlt(795 + (i * 30), 120, 75, 114, &memdc, 0, 0, SRCCOPY);
			oppea.DeleteObject();
		}
		CFont g_editFont;
		g_editFont.CreatePointFont(200, TEXT("굴림"));
		GetDlgItem(IDC_MYSCORE)->SetFont(&g_editFont);
		GetDlgItem(IDC_OPSCORE)->SetFont(&g_editFont);
		GetDlgItem(IDC_PLAYER)->SetFont(&g_editFont);
		GetDlgItem(IDC_OPPLAYER)->SetFont(&g_editFont);
		g_editFont.Detach();
		int score = gamefunc.myscore();
		int Opscore = gamefunc.opscore();
		myscore.Format(_T("%d  점"), score);
		opscore.Format(_T("%d  점"), Opscore);
		SetDlgItemText(IDC_MYSCORE, myscore);
		SetDlgItemText(IDC_OPSCORE, opscore);
		SetDlgItemText(IDC_PLAYER, Myplayer);
		SetDlgItemText(IDC_OPPLAYER, Opplayer);
		
		if (!Check)										
		{
			Check = true;
			if (score >= 7)						//플레이어가 7점이상으로 go,stop 판정
			{	
				if (!go)						//go를 한번도 안했을때
				{
					if (AfxMessageBox(_T("고 하시겠습니까 ? "), MB_YESNO | MB_ICONQUESTION) == IDYES)	//1
					{
						go = true;
						goscore = score;
					}
					else
						gamefunc.Stop();
				}
				else
				{								//이미 1go를 한상태
					if (score - goscore > 0)
						if (AfxMessageBox(_T("한번더 고 하시겠습니까 ? "), MB_YESNO | MB_ICONQUESTION) == IDYES)
							goscore = score;
						else
							gamefunc.Stop();
				}
			}
			if (go)								//플레이어가 1go 이상했을때 상대방이 득점하여 고박 발생할때
			{
				if (Opscore >= 7)
				{
					gamefunc.Gobak();
				}
			}
			Check = false;
		}

		CDialogEx::OnPaint();
	}
	
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMatgoGameClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatgoGameClientDlg::OnLButtonDown(UINT nFlags, CPoint point)					// 다이얼로그 클릭 리스너
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	HBITMAP hbit;
	if (Click)
	{
		for (int i = 0; i < 10; i++)
		{
			CStatic *pic = (CStatic *)GetDlgItem(picture[i]);
			pic->GetWindowRect(&rect);
			ScreenToClient(&rect);
			if (rect.PtInRect(point))
			{
				int pnum1, pnum2;
				pnum1 = player.PaeFind_value(i);
				if ((player.OpenFind_adr(pnum1)) != -1)					//선택한 패와 바닥패가 득점이 가능할때
				{
					if (player.OpenPaeFindCount(pnum1) == 2)			//선택한 패와 바닥패가 득점이 가능한 패가 2장일때
					{
						paedata = player.OpenPaeFind_adr(pnum1);
						selDlg.DoModal();								//자식 다이얼로그 생성해 패선택
						pnum2 = selDlg.SelectPae;
						gamefunc.SelectPae(pnum1, pnum2);
						Click = false;
					}
					else
					{
						pnum2 = player.OpenFind_value(player.OpenFind_adr(pnum1));		//선택한 패와 바닥패가 득점이 가능한 패가 1장일때
						gamefunc.SelectPae(pnum1, pnum2);
						Click = false;
					}
				}
				else if (pnum1 == 48 || pnum1 == 49)					//선택한패가 보너스패일때
				{
					gamefunc.SelectBonus(pnum1);
				}
				else {
					gamefunc.NSelectPae(pnum1);							//바닥패와 득점이 불가능할때
					Click = false;
				}

				pic->SetBitmap(NULL);
			}

		}
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

UINT CMatgoGameClientDlg::ThreadFirst(LPVOID _mothod)					// 소켓 통신 리시버 스레드
{
	CMatgoGameClientDlg *fir = (CMatgoGameClientDlg*)_mothod;	
	int retval;
	char buf[BUFSIZE + 1];
	char *Flag;
	char *Flag1;
	char *Data;
	char player1[] = "Player1";
	char NAME[] = "NAME";
	char INIT[] = "INIT";
	char MINE[] = "MINE";
	char BONUS[] = "BONUS";
	char OPBONUS[] = "OPBONUS";
	char OPSCORE[] = "OPSCORE";
	char OPEN[] = "OPEN";
	char OPOPEN[] = "OPOPEN";
	char NOPOPEN[] = "NOPOPEN";
	char OPADD[] = "OPADD";
	char NEWPAE[] = "NEWPAE";
	char WIN[] = "WIN";
	char LOSE[] = "LOSE";
	while (1)
	{
		retval = recv(sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR){
			AfxMessageBox(L"서버 종료");
			break;
		}
		else if (retval == 0)
			break;
		buf[retval] = '\0';
		Flag = strtok(buf, ",");
		if (!strncmp(Flag, INIT, sizeof(INIT) - 1)) {					//게임 시작시 서버로부터 패 10장, 바닥패 8장 수신
			Flag1 = strtok(NULL, ",");
			if (!strncmp(Flag1, MINE, sizeof(MINE) - 1)) {				//패 10장 
				Data = strtok(NULL, " ");
				gamefunc.init_pae(Data);
			}
			else {
				Data = strtok(NULL, " ");								//바닥패 8장
				gamefunc.init_openpae(Data);
			}
		}
		else if (!strncmp(Flag, NAME, sizeof(NAME) - 1))				//서버와 연결하고 플레이어명 표시(player1,player2)
		{
			Data = strtok(NULL, " ");
			if (!strncmp(Data, player1, sizeof(player1) - 1))
			{
				Myplayer.Format(_T("%S"), Data);
				Opplayer.Format(_T("%S"), "Player2");
				Click = true;
			}
			else
			{
				Myplayer.Format(_T("%S"), "Player2");
				Opplayer.Format(_T("%S"), "Player1");
				Click = false;
			}

			pMainDlg->Invalidate();
		}
		else if (!strncmp(Flag, BONUS, sizeof(BONUS) - 1)) {			//보너스패 받았을때
			Data = strtok(NULL, " ");
			gamefunc.Add_Bonus(Data);
		}
		else if (!strncmp(Flag, OPBONUS, sizeof(OPBONUS) - 1))			//상대방이 보너스패 얻을때
		{
			Data = strtok(NULL, " ");
			gamefunc.Op_Bonus(Data);
		}
		else if (!strncmp(Flag, OPEN, sizeof(OPEN) - 1))			//11: 새로운 바닥패 1장 수신
		{
			Data = strtok(NULL, " ");
			gamefunc.Open_Updatae(Data);
		}
		else if (!strncmp(Flag, OPSCORE, sizeof(OPSCORE) - 1))		//상대방이 득점 할때 득점패 2장 수신
		{
			Data = strtok(NULL, " ");
			gamefunc.OP_SCore(Data);
			Click = true;
		}
		else if (!strncmp(Flag, OPOPEN, sizeof(OPOPEN) - 1))		//상대방이 득점하고 묶음패에서 1장을 바닥패에 놓을때 1장 바닥패 수신
		{
			Data = strtok(NULL, " ");
			gamefunc.OP_open(Data);
			Click = true;
		}
		else if (!strncmp(Flag, NOPOPEN, sizeof(NOPOPEN) - 1))		//상대방이 득점못하고 묶음패에서 1장을 바닥패에 놓을때 1장 바닥패 수신
		{
			Data = strtok(NULL, " ");
			gamefunc.NOP_open(Data);
			Click = true;
		}
		else if (!strncmp(Flag, OPADD, sizeof(OPADD) - 1))			//상대방이 추가득점할때 득점패 2장 수신
		{
			Data = strtok(NULL, " ");
			gamefunc.OP_add(Data);
		}
		else if (!strncmp(Flag, NEWPAE, sizeof(NEWPAE) - 1))		//보너스를 내고 묶음패에서 1장을 수신
		{
			Data = strtok(NULL, " ");
			gamefunc.NewPae(Data);
		}
		else if (!strncmp(Flag, WIN, sizeof(WIN) - 1))				//서버로부터 승자판정을 수신
		{
			Check = false;
			pMainDlg->MessageBox(L"이겼습니다");
			pMainDlg->SendMessage(WM_CLOSE, 0, 0);
			
		}
		else if (!strncmp(Flag, LOSE, sizeof(LOSE) - 1))			//서버로부터 패자판정을 수신
		{
			Check = false;
			pMainDlg->MessageBox(L"졌습니다");
			pMainDlg->SendMessage(WM_CLOSE, 0, 0);
		}
	}

	return 0;
}





BOOL CMatgoGameClientDlg::DestroyWindow()						// 다이얼로그 종료시 
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	MessageBox(L"게임 종료");
	closesocket(sock);
	WSACleanup();

	return CDialogEx::DestroyWindow();
}


void CMatgoGameClientDlg::OnClickedReadybtn()					//게임준비 버튼 클릭 리스너
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char start[] = "start";
	int we = socket.Send(start);
	GetDlgItem(IDC_READYBtn)->ShowWindow(FALSE);

}



