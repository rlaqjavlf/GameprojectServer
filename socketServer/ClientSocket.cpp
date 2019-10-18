// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "socketServer.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��� �Լ�
void CClientSocket::SetWnd(HWND hWnd) {
	m_hWnd = hWnd;
}




/*Ŭ���̾�Ʈ->���� ����*/
/*�������� ����ü ���ο� �ִ� ��ü�� �޴´�*/
void CClientSocket::OnReceive(int nErrorCode) {
	
	int header[2]; //���� 
	/****************************�޼��� �޴ºκ� *************************************/
	Receive((char *)header, sizeof(int) * 2);
	
	if (header[0] == 100) {//100�̸� �޼���
		MyMessage* msg = new MyMessage;
	
		CString strTmp=_T(""),strIPAddress=_T("");
		
		UINT uPortNumber = 0;
		//�ʱ�ȭ�۾�
		ZeroMemory(msg->strBuffer, sizeof(msg->strBuffer));
		
		Receive((char *)msg, header[1]);
		GetPeerName(strIPAddress, uPortNumber);

		strTmp.Format(_T("[%s:%d]:%s"), strIPAddress, uPortNumber, msg->strBuffer);
		//CPP-> ���δ��̾�α׷� ����
		SendMessage(m_hWnd, WM_CLIENT_MSG_RECV, 0, (LPARAM)((LPCTSTR)strTmp));

	}
	else if (header[0]==200) {//200�̸� ���۹�ư
		//AfxMessageBox(_T("����� 200 "));OK
		//AfxMessageBox(_T("Ŭ���̾�Ʈ���� ���� ���� �߹޴��� Ȯ��"));
		
		MyStart* start = new MyStart;
		
		CString str;

		Receive((char *)start, header[1]);
		
		CString strIPAddress = _T("");
		UINT uPortNumber = 0;
		
		GetPeerName(strIPAddress, uPortNumber);

		start->portNum = uPortNumber;

	//	str.Format(_T("%d\n"),start);
		//AfxMessageBox(str);
		

		//CPP-> ���δ��̾�α׷� ����
		SendMessage(m_hWnd, WM_Start_Bool, 0, (LPARAM)start);

		
	}
	/*���� �޾ƿ���*/
	else if (header[0] == 401) {
		//AfxMessageBox(_T("������ �´�"));OK
		MyRock* rock = new MyRock;

		CString str;

		Receive((char *)rock, header[1]);

		//str.Format(_T("%d"), rock->InRock);

		//CPP-> ���δ��̾�α׷� ���� int������ ������
		SendMessage(m_hWnd, WM_RSP_rock_RECV, 0, (LPARAM)(rock));		
	}
	/*���� �޾ƿ���*/
	else if (header[0] == 402) {
		MyScissors* scissors = new MyScissors;

		CString str;

		Receive((char *)scissors, header[1]);
		//str.Format(_T("%d"), scissors->InScissors);

		SendMessage(m_hWnd, WM_RSP_scissors_RECV, 0, (LPARAM)(scissors));
	}
	/*�� �޾ƿ���*/
	else if (header[0] == 403) {
		MyPaper* paper = new MyPaper;

		CString str;

		Receive((char *)paper, header[1]);
		//str.Format(_T("%d"), paper->InPaper);
		SendMessage(m_hWnd, WM_RSP_paper_RECV, 0, (LPARAM)(paper));
	}
	


	
	
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode) {
	CSocket::OnClose(nErrorCode);
}