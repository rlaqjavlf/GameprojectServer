#pragma once
#include "ClientSocket.h"
// CServerSocket ��� ����Դϴ�.

#define WM_ACCEPT_SOCKET WM_USER+1

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	//sendMessage()Ȱ���� ����
	//������ �ڵ��� �޴� �Լ� �߿�!!!

	void SetWnd(HWND hWnd);
	HWND m_hWnd;
	//HWND:�������� �ڵ�(���Ͽ� �����ϱ� ���� ����
	//�ڵ��� �ʿ��ϵ��� ������ ������ ���� ��, ���ڷ� �̷����)
	//�������� ���̵��� �����ϸ� ��

	virtual void OnAccept(int pErrorCode);
	//����Ǳ� ���� ���Ῡ�θ� �˱����� ����Ѵ�. ���� ����ؾ���
};


