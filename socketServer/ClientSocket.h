#pragma once

// CClientSocket ��� ����Դϴ�.

#define WM_CLIENT_MSG_RECV WM_USER+2
#define WM_CLIENT_CLOSE WM_USER+3
#define WM_Start_Bool WM_USER+4
#define WM_RSP_rock_RECV WM_USER+5
#define WM_RSP_scissors_RECV WM_USER+6
#define WM_RSP_paper_RECV WM_USER+7

/***************�޼���****************/
struct MyMessage {
	//LPCTSTR data;
	TCHAR strBuffer[1024];
};
struct ReceivMessages {
	int id;
	int size;
	MyMessage msg;
};

/****************Start����ü********************/
struct MyStart
{
	bool b_start;
	bool b_clickCheck;
	UINT portNum;

};
struct GameStart
{
	int id;
	int size;
	MyStart g_start;
};
/****************Count����ü********************/
struct MyCount
{
	int OnCount;
};
struct SendCount
{
	int id;
	int size;
	MyCount SendOnCount;
};
/********************���� ����ü*******************/
struct MyRock {
	int InRock;
	UINT PLAYER1;
	UINT PLAYER2;
};
struct SendMyRock {
	int id;
	int size;
	MyRock SendOutRock;
};

/********************���� ����ü*******************/
struct MyScissors {
	int InScissors;
	UINT PLAYER1;
	UINT PLAYER2;
};
struct SendMyScissors {
	int id;
	int size;
	MyRock SendOutScissors;
};
/********************�� ����ü*******************/
struct MyPaper {
	int InPaper;
	UINT PLAYER1;
	UINT PLAYER2;
};
struct SendMyPaper {
	int id;
	int size;
	MyRock SendOutPaper;
};


/********��Ʈ��ȣŬ���̾�Ʈ���� ������**********/
struct MyPortNum
{
	UINT PlayerPortNum;
	int PLAYER;
};
struct PortNum{
	int id;
	int size;
	MyPortNum SendPlayerPortNum;

};

/********���� ����� Ŭ���̾�Ʈ���� ������**********/
/*
struct MyEnemyValue
{
	int Enemy1Value;
	UINT Enemy1Port;
	int Enemy2Value;
	UINT Enemy2Port;

};
struct SendMyEnemyValue
{
	int id;
	int size;
	MyEnemyValue EnemyValue;

};
*/


struct MyEnemy1Value
{
	int Enemy1Value;
	UINT Enemy1Port;
	

};
struct SendMyEnemy1Value 
{
	int id;
	int size;
	MyEnemy1Value Enemy1Value;

};



struct MyEnemy2Value
{
	
	int Enemy2Value;
	UINT Enemy2Port;

};
struct SendMyEnemy2Value
{
	int id;
	int size;
	MyEnemy2Value Enemy2Value;

};



/********��������� Ŭ���̾�Ʈ���� ������**********/
struct MyResult
{
	int Player1Result;
	int Player2Result;
	int Playdraw;
	/*
	int Enemy1Value;
	int Enemy2Value;

	UINT Enemy1Port;
	UINT Enemy2Port;
	*/
};
struct SendMyResult
{
	int id;
	int size;
	MyResult SendOutResult;
};




class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	void SetWnd(HWND hWnd);
	HWND m_hWnd;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};
