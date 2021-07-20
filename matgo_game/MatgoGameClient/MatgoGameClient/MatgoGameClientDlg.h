
// MatgoGameClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "Socket.h"
#include "GameFunction.h"
#include "SelectPaeDlg.h"
// CMatgoGameClientDlg 대화 상자
class CMatgoGameClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMatgoGameClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATGOGAMECLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic pic1;
	Socket socket;
	int *paedata;


	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	
	static UINT ThreadFirst(LPVOID _mothod);



	virtual BOOL DestroyWindow();
	afx_msg void OnClickedReadybtn();
	
	CString myscore;
	CString opscore;
	 
};
