
// MatgoGameClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MatgoGameClient.h"
#include "MatgoGameClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BUFSIZE 512
// ��Ʈ�� �ʱ�ȭ
int bitmap[50] = { IDB_BITMAP0,IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3, IDB_BITMAP4,IDB_BITMAP5, IDB_BITMAP6,IDB_BITMAP7,
IDB_BITMAP8,IDB_BITMAP9, IDB_BITMAP10,IDB_BITMAP11, IDB_BITMAP12,IDB_BITMAP13, IDB_BITMAP14,IDB_BITMAP15, IDB_BITMAP16,IDB_BITMAP17,
IDB_BITMAP18,IDB_BITMAP19, IDB_BITMAP20,IDB_BITMAP21, IDB_BITMAP22,IDB_BITMAP23, IDB_BITMAP24,IDB_BITMAP25, IDB_BITMAP26,IDB_BITMAP27,
IDB_BITMAP28,IDB_BITMAP29, IDB_BITMAP30,IDB_BITMAP31, IDB_BITMAP32,IDB_BITMAP33, IDB_BITMAP34,IDB_BITMAP35,IDB_BITMAP36,IDB_BITMAP37,
IDB_BITMAP38,IDB_BITMAP39, IDB_BITMAP40,IDB_BITMAP41, IDB_BITMAP42,IDB_BITMAP43, IDB_BITMAP44,IDB_BITMAP45, IDB_BITMAP46,IDB_BITMAP47, IDB_BITMAP48,IDB_BITMAP49 };
// picture control �ʱ�ȭ
int picture[11] = { IDC_PICTURE1,IDC_PICTURE2,IDC_PICTURE3,IDC_PICTURE4, IDC_PICTURE5,IDC_PICTURE6, IDC_PICTURE7,IDC_PICTURE8,
IDC_PICTURE9,IDC_PICTURE10, IDC_PICTURE11 };

int openpicture[11] = { IDC_OPENPICTURE1,IDC_OPENPICTURE2,IDC_OPENPICTURE3, IDC_OPENPICTURE4, IDC_OPENPICTURE5, IDC_OPENPICTURE6, IDC_OPENPICTURE7,IDC_OPENPICTURE8 
,IDC_OPENPICTURE9,IDC_OPENPICTURE10,IDC_OPENPICTURE11};
int Gwang[5] = { 30,31,32,33,34};
static int n = 0;
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

extern SOCKET sock;					//���� ���� �ܺκ���
extern Player player;				// player Ŭ���� �ܺκ���
GameFunction gamefunc(bitmap,picture,openpicture);				// GameFunction Ŭ���� ����
CMatgoGameClientDlg *pMainDlg;					//GameFunction���� ���� ���̾�α� ��Ʈ���ϱ����� ���� ���̾�α� ��ü����
SelectPaeDlg selDlg;							//2���� �и� �����ϴ� ���̾�α�
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

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMatgoGameClientDlg ��ȭ ����



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


// CMatgoGameClientDlg �޽��� ó����

BOOL CMatgoGameClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	//char msg[] = "Hi";
//	int retval = send(sock, msg, strlen(msg), 0);
	pMainDlg = this;																//���δ��̾�α� ��ü ����
	socket.Connect();																//���� ����
	CWinThread *thread = NULL;														//���� ���ú� ������ ����
	thread = AfxBeginThread(ThreadFirst, this);	
	if (thread == NULL)
		AfxMessageBox(L"Error");
	HBITMAP hbit;																	//������ ��Ʈ�� �̹��� ���
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAPBACK));
	CStatic *pic = (CStatic *)GetDlgItem(IDC_PICTURE11);
	pic->SetBitmap(hbit);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMatgoGameClientDlg::OnPaint()
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
		CPaintDC dc(this);
		CDC memdc;
		memdc.CreateCompatibleDC(&dc);
		CBitmap gwang,opgwang,dan,opdan,mung,opmung,pea,oppea, *oldbitmap;
		
		for (int i = 0; i < player.Gwang_len(); i++)					//�ڽ� ������(��) ��Ʈ�� ���
		{
			gwang.LoadBitmapW(bitmap[player.Gwang_value(i)]);
			oldbitmap = memdc.SelectObject(&gwang);
			dc.BitBlt(480+(i*30), 860, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			gwang.DeleteObject();
		}
		for (int i = 0; i < player.Dan_len(); i++)					//�ڽ� ������(��) ��Ʈ�� ���
		{
			dan.LoadBitmapW(bitmap[player.Dan_value(i)]);
			oldbitmap = memdc.SelectObject(&dan);
			dc.BitBlt(970 + (i * 30), 860, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			dan.DeleteObject();
		}
		for (int i = 0; i < player.Mung_len(); i++)					//�ڽ� ������(��) ��Ʈ�� ���
		{
			mung.LoadBitmapW(bitmap[player.Mung_value(i)]);
			oldbitmap = memdc.SelectObject(&mung);
			dc.BitBlt(680 + (i * 30), 860, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			mung.DeleteObject();
		}
		for (int i = 0; i < player.Peascore_len(); i++)					//�ڽ� ������(��) ��Ʈ�� ���
		{
			pea.LoadBitmapW(bitmap[player.Peascore_value(i)]);
			oldbitmap = memdc.SelectObject(&pea);
			dc.BitBlt(480 + (i * 30), 618, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			pea.DeleteObject();
		}
		for (int i = 0; i < player.OpGwang_len(); i++)					//��� ������(��) ��Ʈ�� ���
		{
			opgwang.LoadBitmapW(bitmap[player.OpGwang_value(i)]);
			oldbitmap = memdc.SelectObject(&opgwang);
			dc.BitBlt(0 + (i * 30), 0, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			opgwang.DeleteObject();
		}
		for (int i = 0; i < player.OpDan_len(); i++)					//��� ������(��) ��Ʈ�� ���
		{
			opdan.LoadBitmapW(bitmap[player.OpDan_value(i)]);
			oldbitmap = memdc.SelectObject(&opdan);
			dc.BitBlt(490 + (i * 30), 0, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			opdan.DeleteObject();
		}
		for (int i = 0; i < player.OpMung_len(); i++)					//��� ������(��) ��Ʈ�� ���
		{
			opmung.LoadBitmapW(bitmap[player.OpMung_value(i)]);
			oldbitmap = memdc.SelectObject(&opmung);
			dc.BitBlt(245 + (i * 30), 0, 75, 114, &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(oldbitmap);
			opmung.DeleteObject();
		}
		for (int i = 0; i < player.OpPeascore_len(); i++)					//��� ������(��) ��Ʈ�� ���
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
		g_editFont.CreatePointFont(200, TEXT("����"));
		GetDlgItem(IDC_MYSCORE)->SetFont(&g_editFont);
		GetDlgItem(IDC_OPSCORE)->SetFont(&g_editFont);
		GetDlgItem(IDC_PLAYER)->SetFont(&g_editFont);
		GetDlgItem(IDC_OPPLAYER)->SetFont(&g_editFont);
		g_editFont.Detach();
		int score = gamefunc.myscore();
		int Opscore = gamefunc.opscore();
		myscore.Format(_T("%d  ��"), score);
		opscore.Format(_T("%d  ��"), Opscore);
		SetDlgItemText(IDC_MYSCORE, myscore);
		SetDlgItemText(IDC_OPSCORE, opscore);
		SetDlgItemText(IDC_PLAYER, Myplayer);
		SetDlgItemText(IDC_OPPLAYER, Opplayer);
		
		if (!Check)										
		{
			Check = true;
			if (score >= 7)						//�÷��̾ 7���̻����� go,stop ����
			{	
				if (!go)						//go�� �ѹ��� ��������
				{
					if (AfxMessageBox(_T("�� �Ͻðڽ��ϱ� ? "), MB_YESNO | MB_ICONQUESTION) == IDYES)	//1
					{
						go = true;
						goscore = score;
					}
					else
						gamefunc.Stop();
				}
				else
				{								//�̹� 1go�� �ѻ���
					if (score - goscore > 0)
						if (AfxMessageBox(_T("�ѹ��� �� �Ͻðڽ��ϱ� ? "), MB_YESNO | MB_ICONQUESTION) == IDYES)
							goscore = score;
						else
							gamefunc.Stop();
				}
			}
			if (go)								//�÷��̾ 1go �̻������� ������ �����Ͽ� ��� �߻��Ҷ�
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMatgoGameClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatgoGameClientDlg::OnLButtonDown(UINT nFlags, CPoint point)					// ���̾�α� Ŭ�� ������
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
				if ((player.OpenFind_adr(pnum1)) != -1)					//������ �п� �ٴ��а� ������ �����Ҷ�
				{
					if (player.OpenPaeFindCount(pnum1) == 2)			//������ �п� �ٴ��а� ������ ������ �а� 2���϶�
					{
						paedata = player.OpenPaeFind_adr(pnum1);
						selDlg.DoModal();								//�ڽ� ���̾�α� ������ �м���
						pnum2 = selDlg.SelectPae;
						gamefunc.SelectPae(pnum1, pnum2);
						Click = false;
					}
					else
					{
						pnum2 = player.OpenFind_value(player.OpenFind_adr(pnum1));		//������ �п� �ٴ��а� ������ ������ �а� 1���϶�
						gamefunc.SelectPae(pnum1, pnum2);
						Click = false;
					}
				}
				else if (pnum1 == 48 || pnum1 == 49)					//�������а� ���ʽ����϶�
				{
					gamefunc.SelectBonus(pnum1);
				}
				else {
					gamefunc.NSelectPae(pnum1);							//�ٴ��п� ������ �Ұ����Ҷ�
					Click = false;
				}

				pic->SetBitmap(NULL);
			}

		}
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

UINT CMatgoGameClientDlg::ThreadFirst(LPVOID _mothod)					// ���� ��� ���ù� ������
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
			AfxMessageBox(L"���� ����");
			break;
		}
		else if (retval == 0)
			break;
		buf[retval] = '\0';
		Flag = strtok(buf, ",");
		if (!strncmp(Flag, INIT, sizeof(INIT) - 1)) {					//���� ���۽� �����κ��� �� 10��, �ٴ��� 8�� ����
			Flag1 = strtok(NULL, ",");
			if (!strncmp(Flag1, MINE, sizeof(MINE) - 1)) {				//�� 10�� 
				Data = strtok(NULL, " ");
				gamefunc.init_pae(Data);
			}
			else {
				Data = strtok(NULL, " ");								//�ٴ��� 8��
				gamefunc.init_openpae(Data);
			}
		}
		else if (!strncmp(Flag, NAME, sizeof(NAME) - 1))				//������ �����ϰ� �÷��̾�� ǥ��(player1,player2)
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
		else if (!strncmp(Flag, BONUS, sizeof(BONUS) - 1)) {			//���ʽ��� �޾�����
			Data = strtok(NULL, " ");
			gamefunc.Add_Bonus(Data);
		}
		else if (!strncmp(Flag, OPBONUS, sizeof(OPBONUS) - 1))			//������ ���ʽ��� ������
		{
			Data = strtok(NULL, " ");
			gamefunc.Op_Bonus(Data);
		}
		else if (!strncmp(Flag, OPEN, sizeof(OPEN) - 1))			//11: ���ο� �ٴ��� 1�� ����
		{
			Data = strtok(NULL, " ");
			gamefunc.Open_Updatae(Data);
		}
		else if (!strncmp(Flag, OPSCORE, sizeof(OPSCORE) - 1))		//������ ���� �Ҷ� ������ 2�� ����
		{
			Data = strtok(NULL, " ");
			gamefunc.OP_SCore(Data);
			Click = true;
		}
		else if (!strncmp(Flag, OPOPEN, sizeof(OPOPEN) - 1))		//������ �����ϰ� �����п��� 1���� �ٴ��п� ������ 1�� �ٴ��� ����
		{
			Data = strtok(NULL, " ");
			gamefunc.OP_open(Data);
			Click = true;
		}
		else if (!strncmp(Flag, NOPOPEN, sizeof(NOPOPEN) - 1))		//������ �������ϰ� �����п��� 1���� �ٴ��п� ������ 1�� �ٴ��� ����
		{
			Data = strtok(NULL, " ");
			gamefunc.NOP_open(Data);
			Click = true;
		}
		else if (!strncmp(Flag, OPADD, sizeof(OPADD) - 1))			//������ �߰������Ҷ� ������ 2�� ����
		{
			Data = strtok(NULL, " ");
			gamefunc.OP_add(Data);
		}
		else if (!strncmp(Flag, NEWPAE, sizeof(NEWPAE) - 1))		//���ʽ��� ���� �����п��� 1���� ����
		{
			Data = strtok(NULL, " ");
			gamefunc.NewPae(Data);
		}
		else if (!strncmp(Flag, WIN, sizeof(WIN) - 1))				//�����κ��� ���������� ����
		{
			Check = false;
			pMainDlg->MessageBox(L"�̰���ϴ�");
			pMainDlg->SendMessage(WM_CLOSE, 0, 0);
			
		}
		else if (!strncmp(Flag, LOSE, sizeof(LOSE) - 1))			//�����κ��� ���������� ����
		{
			Check = false;
			pMainDlg->MessageBox(L"�����ϴ�");
			pMainDlg->SendMessage(WM_CLOSE, 0, 0);
		}
	}

	return 0;
}





BOOL CMatgoGameClientDlg::DestroyWindow()						// ���̾�α� ����� 
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	MessageBox(L"���� ����");
	closesocket(sock);
	WSACleanup();

	return CDialogEx::DestroyWindow();
}


void CMatgoGameClientDlg::OnClickedReadybtn()					//�����غ� ��ư Ŭ�� ������
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char start[] = "start";
	int we = socket.Send(start);
	GetDlgItem(IDC_READYBtn)->ShowWindow(FALSE);

}



