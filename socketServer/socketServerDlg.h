
// socketServerDlg.h : ��� ����
//
#define START 1 // ī��Ʈ ���� START�� ���� ���ش�
#pragma once
#include "ServerSocket.h"

// CsocketServerDlg ��ȭ ����
class CsocketServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CsocketServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
