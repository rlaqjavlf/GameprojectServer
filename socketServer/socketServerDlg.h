
// socketServerDlg.h : 헤더 파일
//
#define START 1 // 카운트 시작 START를 정의 해준다
#pragma once
#include "ServerSocket.h"

// CsocketServerDlg 대화 상자
class CsocketServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CsocketServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETSERVER_DIALOG };
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

private:
	CClientSocket *m_pClientSocket;
	CServerSocket *m_pServerSocket;
public:
	CListBox m_list_client;
	CListBox m_list_msg;
	CPtrList m_ptrClientSocketList;
protected:
	//1
	afx_msg LRESULT OnAcceptSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientMsgRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientStartRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientRSPRecv(WPARAM wParam, LPARAM lParam);

	void Enemy1_Values();
	void Enemy2_Values();

	void CompareResult();


	
public:
	afx_msg void OnChangeEditTorf();
	bool m_Start;
	//CString m_Start_MSG;
	CString m_start_msg;

	int m_startCount;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	CString m_TimeCount;
	bool Start;
	CString m_RSP_msg;
	bool m_ClickCheck;
	
	UINT m_Player1;
	UINT m_Player2;
	
	CString m_PortPrint;
	CString m_portPrint2;
	
	afx_msg void OnEnChangeEditPortnum();
	afx_msg void OnEnChangeEditPortnum2();
	
	int RSP_Value;
	int RSP_Value2;
	
	int m_Player1_Choice;
	int m_Player2_Choice;
	
	int m_SendResult1;
	int m_SendResult2;
	int m_SendResult3;
	bool m_swich1;
	bool m_swich2;
	bool m_ClickCheck2;
};
