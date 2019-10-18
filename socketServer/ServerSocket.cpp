// ServerSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "socketServer.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 멤버 함수
void CServerSocket::SetWnd(HWND hWnd) {
	m_hWnd = hWnd;
}

void CServerSocket::OnAccept(int nErrorCode) {
	CClientSocket* pClient = new CClientSocket;
	if (Accept(*pClient)) {
		pClient->SetWnd(m_hWnd);
	}
	else {
		delete pClient;
		AfxMessageBox(_T("ERROR: Failed can't accept net Client"));
	}
	SendMessage(m_hWnd, WM_ACCEPT_SOCKET, 0, (LPARAM)((LPCTSTR)pClient));
	CSocket::OnAccept(nErrorCode);
}