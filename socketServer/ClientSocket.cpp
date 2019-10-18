// ClientSocket.cpp : 구현 파일입니다.
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


// CClientSocket 멤버 함수
void CClientSocket::SetWnd(HWND hWnd) {
	m_hWnd = hWnd;
}




/*클라이언트->서버 받음*/
/*받을떄는 구조체 내부에 있는 객체로 받는다*/
void CClientSocket::OnReceive(int nErrorCode) {
	
	int header[2]; //구분 
	/****************************메세지 받는부분 *************************************/
	Receive((char *)header, sizeof(int) * 2);
	
	if (header[0] == 100) {//100이면 메세지
		MyMessage* msg = new MyMessage;
	
		CString strTmp=_T(""),strIPAddress=_T("");
		
		UINT uPortNumber = 0;
		//초기화작업
		ZeroMemory(msg->strBuffer, sizeof(msg->strBuffer));
		
		Receive((char *)msg, header[1]);
		GetPeerName(strIPAddress, uPortNumber);

		strTmp.Format(_T("[%s:%d]:%s"), strIPAddress, uPortNumber, msg->strBuffer);
		//CPP-> 메인다이얼로그로 보냄
		SendMessage(m_hWnd, WM_CLIENT_MSG_RECV, 0, (LPARAM)((LPCTSTR)strTmp));

	}
	else if (header[0]==200) {//200이면 시작버튼
		//AfxMessageBox(_T("여기는 200 "));OK
		//AfxMessageBox(_T("클라이언트에서 보낸 정보 잘받는지 확인"));
		
		MyStart* start = new MyStart;
		
		CString str;

		Receive((char *)start, header[1]);
		
		CString strIPAddress = _T("");
		UINT uPortNumber = 0;
		
		GetPeerName(strIPAddress, uPortNumber);

		start->portNum = uPortNumber;

	//	str.Format(_T("%d\n"),start);
		//AfxMessageBox(str);
		

		//CPP-> 메인다이얼로그로 보냄
		SendMessage(m_hWnd, WM_Start_Bool, 0, (LPARAM)start);

		
	}
	/*바위 받아오기*/
	else if (header[0] == 401) {
		//AfxMessageBox(_T("바위가 온다"));OK
		MyRock* rock = new MyRock;

		CString str;

		Receive((char *)rock, header[1]);

		//str.Format(_T("%d"), rock->InRock);

		//CPP-> 메인다이얼로그로 보냄 int형으로 보낸다
		SendMessage(m_hWnd, WM_RSP_rock_RECV, 0, (LPARAM)(rock));		
	}
	/*가위 받아오기*/
	else if (header[0] == 402) {
		MyScissors* scissors = new MyScissors;

		CString str;

		Receive((char *)scissors, header[1]);
		//str.Format(_T("%d"), scissors->InScissors);

		SendMessage(m_hWnd, WM_RSP_scissors_RECV, 0, (LPARAM)(scissors));
	}
	/*보 받아오기*/
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