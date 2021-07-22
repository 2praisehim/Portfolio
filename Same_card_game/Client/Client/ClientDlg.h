
// ClientDlg.h : 헤더 파일
//

#pragma once
#include"Resource.h"
#include"ClientSock.h"
#include "afxcolorbutton.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "atltime.h"
#include "atltypes.h"
#include "ScoreBoardDlg.h"


// CClientDlg 대화 상자
class CClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CLIENT_DIALOG };

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
	afx_msg void OnClickedConnect();
	afx_msg void OnClickedSend();
	CString m_QuestionC;
	CMFCColorButton m_ColorButton;
	CSpinButtonCtrl m_ctrSpin;
	int m_LineThickness;
	CString m_AnswerC;
	CStatic m_TextC;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_ScoreC;
	CString ScoreC;
	int m_Mode;
	BOOL pen_flag;
	CTime timerC;
	CTime StartTimeC;
	CTime EndTimeC;
	int m_Thickness;
	COLORREF m_color;
	afx_msg void OnBnClickedLinecolor();
	afx_msg void OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedQuestionmode();
	afx_msg void OnBnClickedAnswermode();
	afx_msg void OnBnClickedButtonAnswer();
	afx_msg void OnBnClickedButtonQuestion();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CPoint m_cpDraw;
	int b;
	CString m_ServerQ;
	void StopQuestion(void);
	afx_msg void OnBnClickedButtonClear();
	CListBox m_list;
	afx_msg void OnBnClickedReconnect();
	void AllClear(void);
	CStatic m_Picture;
	void DrawPicture(CPoint& ptStart, CPoint& ptEnd);
	CString Clear;
	void PictureClear(void);
	char h;
	CString m_CID;
	afx_msg void OnBnClickedReady();
	CString UserID[5];
	CString UserScoreSTR[5];
	int UserScore[5];
	CProgressCtrl m_GameTimebar;
	int myturn, gameturn, circle;
	CString RecieveID;
	void FinishGame();
	void Sendresult();
};
