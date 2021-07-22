
// Client.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include"ConnectDlg.h"
#include "afxdialogex.h"
#include "ScoreBoardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClientApp 생성

CClientApp::CClientApp()
	: m_pClient(NULL)
	, AnsS(_T(""))
	, QueS(_T(""))
	, Disconnect(0)
	, StopDraw(_T(""))
	, ThicknessS(0)
	, unum(0)
	, anotherC(0)
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	m_pClient=NULL;
	Disconnect=0;
}


// 유일한 CClientApp 개체입니다.

CClientApp theApp;


// CClientApp 초기화

BOOL CClientApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}



void CClientApp::Connect(void)
{
	CConnectDlg dlg;
	CClientDlg *Dlg = (CClientDlg*)AfxGetMainWnd();//Dialog클래스 참조 선언
	char h='I';
	CString data=_T("");
	if(dlg.DoModal()==IDOK)//IP주소를 다적고 확인버튼을 눌렀을 때
	{
		m_pClient=new CClientSock;//클라이언트 소켓생성
		m_pClient->Create();
		m_pClient->Connect(dlg.m_strAddress,5000);//적힌IP주소,5000번포트에 연결
		SendData(h,Dlg->m_CID,data);//연결되면 클라이언트(자신)의 정보를 서버에게 보냄
		m_pMainWnd->GetDlgItem(IDC_SEND)->EnableWindow(TRUE);//연결되면 채팅보내기 버튼 활성화
		m_pMainWnd->GetDlgItem(IDC_RECONNECT)->EnableWindow(TRUE);//다시연결 버튼활성화
		m_pMainWnd->GetDlgItem(IDC_READY)->EnableWindow(TRUE);//준비버튼 활성화
		m_pMainWnd->GetDlgItem(IDC_CONNECT)->EnableWindow(FALSE);//연결버튼 비활성화
	}
}


void CClientApp::SendData(char& header, CString& id, CString& str)
	//채팅데이터를 서버에게 보낸다.
{
	CClientDlg *dlg = (CClientDlg*)AfxGetMainWnd();//Dialog클래스 참조 선언
	packet.header=header;//멤버변수를 패킷구조변수에 대입
	packet.ID=id;
	packet.IDlen='0'+packet.ID.GetLength();
	packet.data=str;
	CString sdata;
	sdata.Format(_T("%c%c%s%s"),packet.header,packet.IDlen,packet.ID,packet.data);	//packet구조를 한개의 문자열 데이터로 만듬
	m_pClient->Send((LPCTSTR)(sdata), sizeof(TCHAR)*((sdata).GetLength()+1));	//서버에게 데이터 보냄
	if(packet.header=='M')		//채팅 데이터일때
	{
		CString strText;
		strText.Format(_T("[나]:%s"), str);
		((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);//Listbox(채팅창)에 띄움
		dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);//스크롤 자동내리기
	}
	else if(packet.header=='A')	//정답 데이터일때
	{
		CString answer;
		answer.Format(_T("[나]:정답:%s"),str);
		((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//정답을 채팅으로 보여줌
		dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);//스크롤 자동내리기
	}	
}


void CClientApp::ReceiveData(void)
{
	CClientDlg *dlg = (CClientDlg*)AfxGetMainWnd();//Dialog클래스 참조 선언
	char buf[200];
	m_pClient-> Receive(buf, sizeof(buf));//데이터를 받아서 buf에 저장
	CString data((LPCTSTR) buf);//char -> CString 형변환
	CString strText, strPoint[4], strColor[3], ID;
	int idlen;
	CPoint ptStart, ptEnd;		//그림데이터를 받기위해 선언해준다.
	idlen=_ttoi(data.Mid(1,1));	//보낸사람의 닉네임의 길이를 변수에 저장
	ID=data.Mid(2,idlen);		//보낸사람의 닉네임을 변수에 저장
	if(ID.Compare(dlg->m_CID))	//받은 데이터가 자신의 데이터가 아닐때만 받아옴
	{
		if(data.Left(1)=='Q')//문제데이터를 받아왔을 때
		{
			QueS=data.Mid(2+idlen);//실제 데이터만 새로저장
			dlg->m_GameTimebar.SetRange(0,180);	//문제를 받아옴과 동시에 시간재기 시작
			dlg->m_GameTimebar.SetPos(180);		//제한시간 180초=3분
			dlg->SetTimer(1,1000,NULL);//문제를 받아옴과 동시에 순간 타이머 시작
			dlg->StartTimeC=CTime::GetCurrentTime();//시작되는 순간의 시간을 가져옴
		}
		else if(data.Left(1)=='A')//정답데이터를 받아왔을 때
		{
			CString answer;
			if(unum==1)//1:1통신일때
			{
				answer.Format(_T("[방장][%s]:정답:%s"),ID,data.Mid(2+idlen));
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//다른 유저의 정답 채팅창에 표시
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
				AnsS=data.Mid(2+idlen);//실제 데이터만 새로저장
				dlg->RecieveID=ID;//맞춘사람(서버)의 ID받아옴
				dlg->StopQuestion();//StopQuestion함수 실행
			}
			else
			{
				if(!ID.Compare(dlg->UserID[0]))//정답을 적은 사람이 서버(방장)일 때
				{
					answer.Format(_T("[방장][%s]:정답:%s"),ID,data.Mid(2+idlen));
					((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//다른 유저의 정답 채팅창에 표시
					dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
				}
				else
				{
					answer.Format(_T("[%s]:정답:%s"),ID,data.Mid(2+idlen));
					((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//다른 유저의 정답 채팅창에 표시
					dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
				}
				if(dlg->myturn==dlg->gameturn)//내가 문제내는 차례일 때 StopQuestion함수 실행
				{
					AnsS=data.Mid(2+idlen);//실제 데이터만 새로저장
					dlg->RecieveID=ID;//맞춘사람 ID받아옴
					dlg->StopQuestion();
				}
			}
		}
		else if(data.Left(1)=='S')//점수데이터 받아왔을 때
		{
			for(int i=0;i<5;i++)
			//점수데이터를 '$'에 따라 구별하여 배열변수에저장
			{
				AfxExtractSubString( dlg->UserScoreSTR[i], data.Mid(2+idlen), i+1, '$');
				dlg->UserScore[i]=_ttoi(dlg->UserScoreSTR[i]);
			}
			CScoreBoardDlg open;
			open.DoModal();//전체 점수판 다이얼로그 띄움
		}
		else if(data.Left(1)=='P')//그림데이터를 받아왔을 때
		{
			//문자열을 $에 따라서 나눈다.
			for(int j=0;j<4;j++)
			{
				AfxExtractSubString( strPoint[j], data.Mid(2+idlen), (j+1), '$');
			}
			//CString->int로 형변환해주어 좌표값에 넣어준다.
			ptStart.x=_ttoi(strPoint[0]);
			ptStart.y=_ttoi(strPoint[1]);
			ptEnd.x=_ttoi(strPoint[2]);
			ptEnd.y=_ttoi(strPoint[3]);
			dlg->DrawPicture(ptStart, ptEnd);//받은데이터를 화면에 그려준다.
		}
		else if(data.Left(1)=='T')//선두께에 대한 데이터를 받았을 때
		{
			ThicknessS=_ttoi(data.Mid(2+idlen));//선두께를 형변환하여 int변수에 저장
		}
		else if(data.Left(1)=='L')//선색상에 대한 데이터를 받았을 때
		{
			int R,G,B;
			//문자열을 $에 따라서 나눈다.
			for(int k=0;k<3;k++)
			{
				AfxExtractSubString( strColor[k], data.Mid(2+idlen), k+1, '$');
			}
			//CString->int로 형변환해주어 R,G,B에 넣어준다.
			R=_ttoi(strColor[0]);
			G=_ttoi(strColor[1]);
			B=_ttoi(strColor[2]);
			ColorS=RGB(R,G,B);//받아온 색정보를 변수에 대입한다.
		}
		else if(data.Left(1)=='E')//화면 지워지는 신호를 받아왔을 때
		{
			dlg->PictureClear();//똑같이 화면을 지운다.
		}
		else if(data.Left(1)=='M')//채팅데이터를 받아왔을 때
		{
			if(!ID.Compare(dlg->UserID[0]))//채팅을 보낸게 서버(방장)일 때
			{
				strText.Format(_T("[방장][%s]:%s"),ID,data.Mid(2+idlen));//방장이란 것을 따로 표시해줌
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,strText);
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			}
			else	//채팅을 보낸게 클라이언트(일반유저)일 때
			{
				strText.Format(_T("[%s]:%s"),ID,data.Mid(2+idlen));
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,strText);
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			}
		}
		else if(data.Left(1)=='U')//User들의 데이터를 받아왔을 때(게임시작)
		{
			unum=_ttoi(data.Mid(2+idlen,1));//방장을 제외한 유저들의 총 수를 받아옴
			for(int j=1;j<(unum+1);j++)//User의 수만큼 저장
			{
				AfxExtractSubString( dlg->UserID[j], data.Mid(3+idlen), j, '$');//나머지 유저들의 닉네임 차례대로 저장
			}
			CString startgame;
			startgame.Format(_T("게임을 시작합니다"));
			((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,startgame);//게임이 시작되었음을 채팅창에 공지로 띄움
			dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			dlg->OnBnClickedAnswermode();//정답자 모드로 게임시작
		}
		else if(data.Left(1)=='I')//Server(방장의)와 연결된 정보 데이터를 받아왔을 때
		{
			anotherC++;
			if((anotherC==1)&&(!data.Mid(3+idlen).Compare(dlg->m_CID)))//자신이 연결될 때만 띄움
			{
				dlg->UserID[0]=ID;	//Server(방장)의 닉네임을 변수에 저장+
				CString insertgame;
				dlg->myturn=_ttoi(data.Mid(2+idlen,1));
				insertgame.Format(_T("대기방에 참가하였습니다."));
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,insertgame);
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			}
		}
		else if(data.Left(1)=='F')//다른 유저가 정답을 맞췄다는 신호와 게임순서를 받아왔을 때
		{
			if(!(data.Mid(3+idlen).Compare(dlg->m_CID)))//정답을 맞춘게 자신일 때
				AfxMessageBox(_T("정답입니다!"));
			else//정답을 맞춘게 다른 유저일 때
			{
				if(data.Mid(3+idlen).GetLength()>0)
				{
					strText.Format(_T("%s님이 정답을 맞추셨습니다."),data.Mid(3+idlen));//맞춘 유저의 닉네임을 띄움
					AfxMessageBox(strText);
				}
			}
			dlg->gameturn=_ttoi(data.Mid(2+idlen,1));//순서를 int형으로 변환
			if(dlg->gameturn==dlg->myturn)//내 차례가 되었을 때	
				dlg->OnBnClickedQuestionmode();	//출제자 모드
			else if(dlg->gameturn==7)//게임이 끝났을 때
				dlg->FinishGame();//FinishGame함수 실행
			else //내 차례가 아닌 경우
				dlg->OnBnClickedAnswermode();	//정답자 모드
		}
	}
}	


void CClientApp::CloseChild(void)
{
	CClientDlg *dlg = (CClientDlg*)AfxGetMainWnd();//Dialog클래스 참조 선언
	dlg->AllClear();//Dlg클래스의 AllClear함수 실행
	AfxMessageBox(_T("서버와 연결이 끊어졌습니다."));
	m_pMainWnd->GetDlgItem(IDC_CONNECT)->EnableWindow(TRUE);
	m_pMainWnd->GetDlgItem(IDC_RECONNECT)->EnableWindow(FALSE);
}


void CClientApp::CleanUp(void)
{
	if(m_pClient)
		delete m_pClient;
}


void CClientApp::SendPicture(char& header, CString& id, CPoint& ptStart, CPoint& ptEnd)
{
	CString Picture;
	Picture.Format(_T("$%d$%d$%d$%d"), ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	//각 포인터의 x값과 y값을 한번에 저장한 데이터를 서버에게 보낸다.
	SendData(header, id, Picture);
}


void CClientApp::SendThickness(char& header, CString& id, int& thickness)
{
	CString strThick;
	strThick.Format(_T("%d"),thickness);
	SendData(header, id, strThick);
	//선두께에 대한 데이터를 클라이언트에게 보낸다.
}


void CClientApp::SendColor(char& header, CString& id, int& Red, int& Green, int& Blue)
{
	CString strColor;
	strColor.Format(_T("$%d$%d$%d"), Red, Green, Blue);
	//받아온 선색상 데이터를 한번에 저장하여 클라이언트에게 보낸다.
	SendData(header, id, strColor);
}
