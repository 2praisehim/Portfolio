// SelectPaeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MatgoGameClient.h"
#include "SelectPaeDlg.h"
#include "afxdialogex.h"
extern CMatgoGameClientDlg *pMainDlg;

// SelectPaeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(SelectPaeDlg, CDialogEx)

int Selbitmap[50] = { IDB_BITMAP0,IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3, IDB_BITMAP4,IDB_BITMAP5, IDB_BITMAP6,IDB_BITMAP7,
IDB_BITMAP8,IDB_BITMAP9, IDB_BITMAP10,IDB_BITMAP11, IDB_BITMAP12,IDB_BITMAP13, IDB_BITMAP14,IDB_BITMAP15, IDB_BITMAP16,IDB_BITMAP17,
IDB_BITMAP18,IDB_BITMAP19, IDB_BITMAP20,IDB_BITMAP21, IDB_BITMAP22,IDB_BITMAP23, IDB_BITMAP24,IDB_BITMAP25, IDB_BITMAP26,IDB_BITMAP27,
IDB_BITMAP28,IDB_BITMAP29, IDB_BITMAP30,IDB_BITMAP31, IDB_BITMAP32,IDB_BITMAP33, IDB_BITMAP34,IDB_BITMAP35,IDB_BITMAP36,IDB_BITMAP37,
IDB_BITMAP38,IDB_BITMAP39, IDB_BITMAP40,IDB_BITMAP41, IDB_BITMAP42,IDB_BITMAP43, IDB_BITMAP44,IDB_BITMAP45, IDB_BITMAP46,IDB_BITMAP47, IDB_BITMAP48,IDB_BITMAP49 };

int SelPic[2] = { IDC_SELPICTURE1,IDC_SELPICTURE2 };
SelectPaeDlg::SelectPaeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECTDIALOG, pParent)
{

}

SelectPaeDlg::~SelectPaeDlg()
{
}

void SelectPaeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelectPaeDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// SelectPaeDlg �޽��� ó�����Դϴ�.


BOOL SelectPaeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	sel[0] = pMainDlg->paedata[0];
	sel[1]= pMainDlg->paedata[1];

	HBITMAP hbit;																			// �ڽ� ���̾�α׿� �ٴ��� �� ���� ������ �� 2�� ���
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(Selbitmap[sel[0]]));
	CStatic *Selpic1 = (CStatic *)GetDlgItem(IDC_SELPICTURE1);
	Selpic1->SetBitmap(hbit);
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(Selbitmap[sel[1]]));
	CStatic *Selpic2 = (CStatic *)GetDlgItem(IDC_SELPICTURE2);
	Selpic2->SetBitmap(hbit);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void SelectPaeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	HBITMAP hbit;

	for (int i = 0; i < 2; i++)
	{
		CStatic *CLKpic = (CStatic *)GetDlgItem(SelPic[i]);
		CLKpic->GetWindowRect(&rect);
		ScreenToClient(&rect);
		if (rect.PtInRect(point))				//���� �ϳ��� �и� Ŭ���ҽ� �θ� ���̾�α׷� ������ �� �ڽ� ���̾�α� ����
		{
			SelectPae = sel[i];
			SendMessage(WM_CLOSE, 0, 0);
		}

	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
