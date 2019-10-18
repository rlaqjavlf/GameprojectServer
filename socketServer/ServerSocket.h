#pragma once
#include "ClientSocket.h"
// CServerSocket 명령 대상입니다.

#define WM_ACCEPT_SOCKET WM_USER+1

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	//sendMessage()활용을 위해
	//메인의 핸들을 받는 함수 중요!!!

	void SetWnd(HWND hWnd);
	HWND m_hWnd;
	//HWND:윈도우의 핸들(파일에 접근하기 위해 파일
	//핸들이 필요하듯이 윈도우 접근을 위한 값, 숫자로 이루어짐)
	//윈도우의 아이디라고 생각하면 됨

	virtual void OnAccept(int pErrorCode);
	//연결되기 전에 연결여부를 알기위해 사용한다. 같이 사용해야함
};


