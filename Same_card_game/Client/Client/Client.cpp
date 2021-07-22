
// Client.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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


// CClientApp ����

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
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
	m_pClient=NULL;
	Disconnect=0;
}


// ������ CClientApp ��ü�Դϴ�.

CClientApp theApp;


// CClientApp �ʱ�ȭ

BOOL CClientApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}



void CClientApp::Connect(void)
{
	CConnectDlg dlg;
	CClientDlg *Dlg = (CClientDlg*)AfxGetMainWnd();//DialogŬ���� ���� ����
	char h='I';
	CString data=_T("");
	if(dlg.DoModal()==IDOK)//IP�ּҸ� ������ Ȯ�ι�ư�� ������ ��
	{
		m_pClient=new CClientSock;//Ŭ���̾�Ʈ ���ϻ���
		m_pClient->Create();
		m_pClient->Connect(dlg.m_strAddress,5000);//����IP�ּ�,5000����Ʈ�� ����
		SendData(h,Dlg->m_CID,data);//����Ǹ� Ŭ���̾�Ʈ(�ڽ�)�� ������ �������� ����
		m_pMainWnd->GetDlgItem(IDC_SEND)->EnableWindow(TRUE);//����Ǹ� ä�ú����� ��ư Ȱ��ȭ
		m_pMainWnd->GetDlgItem(IDC_RECONNECT)->EnableWindow(TRUE);//�ٽÿ��� ��ưȰ��ȭ
		m_pMainWnd->GetDlgItem(IDC_READY)->EnableWindow(TRUE);//�غ��ư Ȱ��ȭ
		m_pMainWnd->GetDlgItem(IDC_CONNECT)->EnableWindow(FALSE);//�����ư ��Ȱ��ȭ
	}
}


void CClientApp::SendData(char& header, CString& id, CString& str)
	//ä�õ����͸� �������� ������.
{
	CClientDlg *dlg = (CClientDlg*)AfxGetMainWnd();//DialogŬ���� ���� ����
	packet.header=header;//��������� ��Ŷ���������� ����
	packet.ID=id;
	packet.IDlen='0'+packet.ID.GetLength();
	packet.data=str;
	CString sdata;
	sdata.Format(_T("%c%c%s%s"),packet.header,packet.IDlen,packet.ID,packet.data);	//packet������ �Ѱ��� ���ڿ� �����ͷ� ����
	m_pClient->Send((LPCTSTR)(sdata), sizeof(TCHAR)*((sdata).GetLength()+1));	//�������� ������ ����
	if(packet.header=='M')		//ä�� �������϶�
	{
		CString strText;
		strText.Format(_T("[��]:%s"), str);
		((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);//Listbox(ä��â)�� ���
		dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);//��ũ�� �ڵ�������
	}
	else if(packet.header=='A')	//���� �������϶�
	{
		CString answer;
		answer.Format(_T("[��]:����:%s"),str);
		((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//������ ä������ ������
		dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);//��ũ�� �ڵ�������
	}	
}


void CClientApp::ReceiveData(void)
{
	CClientDlg *dlg = (CClientDlg*)AfxGetMainWnd();//DialogŬ���� ���� ����
	char buf[200];
	m_pClient-> Receive(buf, sizeof(buf));//�����͸� �޾Ƽ� buf�� ����
	CString data((LPCTSTR) buf);//char -> CString ����ȯ
	CString strText, strPoint[4], strColor[3], ID;
	int idlen;
	CPoint ptStart, ptEnd;		//�׸������͸� �ޱ����� �������ش�.
	idlen=_ttoi(data.Mid(1,1));	//��������� �г����� ���̸� ������ ����
	ID=data.Mid(2,idlen);		//��������� �г����� ������ ����
	if(ID.Compare(dlg->m_CID))	//���� �����Ͱ� �ڽ��� �����Ͱ� �ƴҶ��� �޾ƿ�
	{
		if(data.Left(1)=='Q')//���������͸� �޾ƿ��� ��
		{
			QueS=data.Mid(2+idlen);//���� �����͸� ��������
			dlg->m_GameTimebar.SetRange(0,180);	//������ �޾ƿȰ� ���ÿ� �ð���� ����
			dlg->m_GameTimebar.SetPos(180);		//���ѽð� 180��=3��
			dlg->SetTimer(1,1000,NULL);//������ �޾ƿȰ� ���ÿ� ���� Ÿ�̸� ����
			dlg->StartTimeC=CTime::GetCurrentTime();//���۵Ǵ� ������ �ð��� ������
		}
		else if(data.Left(1)=='A')//���䵥���͸� �޾ƿ��� ��
		{
			CString answer;
			if(unum==1)//1:1����϶�
			{
				answer.Format(_T("[����][%s]:����:%s"),ID,data.Mid(2+idlen));
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//�ٸ� ������ ���� ä��â�� ǥ��
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
				AnsS=data.Mid(2+idlen);//���� �����͸� ��������
				dlg->RecieveID=ID;//������(����)�� ID�޾ƿ�
				dlg->StopQuestion();//StopQuestion�Լ� ����
			}
			else
			{
				if(!ID.Compare(dlg->UserID[0]))//������ ���� ����� ����(����)�� ��
				{
					answer.Format(_T("[����][%s]:����:%s"),ID,data.Mid(2+idlen));
					((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//�ٸ� ������ ���� ä��â�� ǥ��
					dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
				}
				else
				{
					answer.Format(_T("[%s]:����:%s"),ID,data.Mid(2+idlen));
					((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, answer);//�ٸ� ������ ���� ä��â�� ǥ��
					dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
				}
				if(dlg->myturn==dlg->gameturn)//���� �������� ������ �� StopQuestion�Լ� ����
				{
					AnsS=data.Mid(2+idlen);//���� �����͸� ��������
					dlg->RecieveID=ID;//������ ID�޾ƿ�
					dlg->StopQuestion();
				}
			}
		}
		else if(data.Left(1)=='S')//���������� �޾ƿ��� ��
		{
			for(int i=0;i<5;i++)
			//���������͸� '$'�� ���� �����Ͽ� �迭����������
			{
				AfxExtractSubString( dlg->UserScoreSTR[i], data.Mid(2+idlen), i+1, '$');
				dlg->UserScore[i]=_ttoi(dlg->UserScoreSTR[i]);
			}
			CScoreBoardDlg open;
			open.DoModal();//��ü ������ ���̾�α� ���
		}
		else if(data.Left(1)=='P')//�׸������͸� �޾ƿ��� ��
		{
			//���ڿ��� $�� ���� ������.
			for(int j=0;j<4;j++)
			{
				AfxExtractSubString( strPoint[j], data.Mid(2+idlen), (j+1), '$');
			}
			//CString->int�� ����ȯ���־� ��ǥ���� �־��ش�.
			ptStart.x=_ttoi(strPoint[0]);
			ptStart.y=_ttoi(strPoint[1]);
			ptEnd.x=_ttoi(strPoint[2]);
			ptEnd.y=_ttoi(strPoint[3]);
			dlg->DrawPicture(ptStart, ptEnd);//���������͸� ȭ�鿡 �׷��ش�.
		}
		else if(data.Left(1)=='T')//���β��� ���� �����͸� �޾��� ��
		{
			ThicknessS=_ttoi(data.Mid(2+idlen));//���β��� ����ȯ�Ͽ� int������ ����
		}
		else if(data.Left(1)=='L')//������ ���� �����͸� �޾��� ��
		{
			int R,G,B;
			//���ڿ��� $�� ���� ������.
			for(int k=0;k<3;k++)
			{
				AfxExtractSubString( strColor[k], data.Mid(2+idlen), k+1, '$');
			}
			//CString->int�� ����ȯ���־� R,G,B�� �־��ش�.
			R=_ttoi(strColor[0]);
			G=_ttoi(strColor[1]);
			B=_ttoi(strColor[2]);
			ColorS=RGB(R,G,B);//�޾ƿ� �������� ������ �����Ѵ�.
		}
		else if(data.Left(1)=='E')//ȭ�� �������� ��ȣ�� �޾ƿ��� ��
		{
			dlg->PictureClear();//�Ȱ��� ȭ���� �����.
		}
		else if(data.Left(1)=='M')//ä�õ����͸� �޾ƿ��� ��
		{
			if(!ID.Compare(dlg->UserID[0]))//ä���� ������ ����(����)�� ��
			{
				strText.Format(_T("[����][%s]:%s"),ID,data.Mid(2+idlen));//�����̶� ���� ���� ǥ������
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,strText);
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			}
			else	//ä���� ������ Ŭ���̾�Ʈ(�Ϲ�����)�� ��
			{
				strText.Format(_T("[%s]:%s"),ID,data.Mid(2+idlen));
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,strText);
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			}
		}
		else if(data.Left(1)=='U')//User���� �����͸� �޾ƿ��� ��(���ӽ���)
		{
			unum=_ttoi(data.Mid(2+idlen,1));//������ ������ �������� �� ���� �޾ƿ�
			for(int j=1;j<(unum+1);j++)//User�� ����ŭ ����
			{
				AfxExtractSubString( dlg->UserID[j], data.Mid(3+idlen), j, '$');//������ �������� �г��� ���ʴ�� ����
			}
			CString startgame;
			startgame.Format(_T("������ �����մϴ�"));
			((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,startgame);//������ ���۵Ǿ����� ä��â�� ������ ���
			dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			dlg->OnBnClickedAnswermode();//������ ���� ���ӽ���
		}
		else if(data.Left(1)=='I')//Server(������)�� ����� ���� �����͸� �޾ƿ��� ��
		{
			anotherC++;
			if((anotherC==1)&&(!data.Mid(3+idlen).Compare(dlg->m_CID)))//�ڽ��� ����� ���� ���
			{
				dlg->UserID[0]=ID;	//Server(����)�� �г����� ������ ����+
				CString insertgame;
				dlg->myturn=_ttoi(data.Mid(2+idlen,1));
				insertgame.Format(_T("���濡 �����Ͽ����ϴ�."));
				((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1,insertgame);
				dlg->m_list.SetTopIndex(dlg->m_list.GetCount()-1);
			}
		}
		else if(data.Left(1)=='F')//�ٸ� ������ ������ ����ٴ� ��ȣ�� ���Ӽ����� �޾ƿ��� ��
		{
			if(!(data.Mid(3+idlen).Compare(dlg->m_CID)))//������ ����� �ڽ��� ��
				AfxMessageBox(_T("�����Դϴ�!"));
			else//������ ����� �ٸ� ������ ��
			{
				if(data.Mid(3+idlen).GetLength()>0)
				{
					strText.Format(_T("%s���� ������ ���߼̽��ϴ�."),data.Mid(3+idlen));//���� ������ �г����� ���
					AfxMessageBox(strText);
				}
			}
			dlg->gameturn=_ttoi(data.Mid(2+idlen,1));//������ int������ ��ȯ
			if(dlg->gameturn==dlg->myturn)//�� ���ʰ� �Ǿ��� ��	
				dlg->OnBnClickedQuestionmode();	//������ ���
			else if(dlg->gameturn==7)//������ ������ ��
				dlg->FinishGame();//FinishGame�Լ� ����
			else //�� ���ʰ� �ƴ� ���
				dlg->OnBnClickedAnswermode();	//������ ���
		}
	}
}	


void CClientApp::CloseChild(void)
{
	CClientDlg *dlg = (CClientDlg*)AfxGetMainWnd();//DialogŬ���� ���� ����
	dlg->AllClear();//DlgŬ������ AllClear�Լ� ����
	AfxMessageBox(_T("������ ������ ���������ϴ�."));
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
	//�� �������� x���� y���� �ѹ��� ������ �����͸� �������� ������.
	SendData(header, id, Picture);
}


void CClientApp::SendThickness(char& header, CString& id, int& thickness)
{
	CString strThick;
	strThick.Format(_T("%d"),thickness);
	SendData(header, id, strThick);
	//���β��� ���� �����͸� Ŭ���̾�Ʈ���� ������.
}


void CClientApp::SendColor(char& header, CString& id, int& Red, int& Green, int& Blue)
{
	CString strColor;
	strColor.Format(_T("$%d$%d$%d"), Red, Green, Blue);
	//�޾ƿ� ������ �����͸� �ѹ��� �����Ͽ� Ŭ���̾�Ʈ���� ������.
	SendData(header, id, strColor);
}
