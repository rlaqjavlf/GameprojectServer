
// socketServerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "socketServer.h"
#include "socketServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PORT 9999 //임의의 포트설정

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEditTorf();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(IDC_EDIT_TorF, &CAboutDlg::OnEditTorf)
END_MESSAGE_MAP()


// CsocketServerDlg 대화 상자



CsocketServerDlg::CsocketServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKETSERVER_DIALOG, pParent)
	, m_Start(false)
	, m_start_msg(_T(""))
	, m_startCount(5)
	, m_TimeCount(_T(""))
	, Start(false)
	, m_RSP_msg(_T(""))
	, RSP_Value(0)
	, m_ClickCheck(false)
	, m_Player1(0)
	, m_Player2(0)
	, m_PortPrint(_T(""))
	, m_portPrint2(_T(""))
	, RSP_Value2(0)
	, m_Player1_Choice(0)
	, m_Player2_Choice(0)
	, m_SendResult1(0)
	, m_SendResult2(0)
	, m_SendResult3(0)

	, m_ClickCheck2(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsocketServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_list_client);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
	DDX_Text(pDX, IDC_EDIT_TorF, m_start_msg);
	//DDX_Text(pDX, IDC_EDIT_TorF, m_RSP_msg);
	DDX_Text(pDX, IDC_EDIT_PortNum, m_PortPrint);
	DDX_Text(pDX, IDC_EDIT_PortNum2, m_portPrint2);
}

BEGIN_MESSAGE_MAP(CsocketServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_ACCEPT_SOCKET, &CsocketServerDlg::OnAcceptSocket)
	ON_MESSAGE(WM_CLIENT_CLOSE, &CsocketServerDlg::OnClientClose)
	ON_MESSAGE(WM_CLIENT_MSG_RECV, &CsocketServerDlg::OnClientMsgRecv)

	//시작버튼
	ON_MESSAGE(WM_Start_Bool, &CsocketServerDlg::OnClientStartRecv)
	//바위선택
	ON_MESSAGE(WM_RSP_rock_RECV, &CsocketServerDlg::OnClientRSPRecv)
	//가위선택
	ON_MESSAGE(WM_RSP_scissors_RECV, &CsocketServerDlg::OnClientRSPRecv)
	//보 선택
	ON_MESSAGE(WM_RSP_paper_RECV, &CsocketServerDlg::OnClientRSPRecv)

	ON_EN_CHANGE(IDC_EDIT_TorF, &CsocketServerDlg::OnChangeEditTorf)
	
	ON_WM_TIMER()
	
	ON_EN_CHANGE(IDC_EDIT_PortNum, &CsocketServerDlg::OnEnChangeEditPortnum)
	ON_EN_CHANGE(IDC_EDIT_PortNum2, &CsocketServerDlg::OnEnChangeEditPortnum2)
END_MESSAGE_MAP()


// CsocketServerDlg 메시지 처리기

BOOL CsocketServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_pServerSocket = new CServerSocket;
	m_pServerSocket->SetWnd(this->m_hWnd);

	m_pServerSocket->Create(PORT);
	m_pServerSocket->Listen();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CsocketServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CsocketServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CsocketServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*서버 클라이언트 창에서 클라이언트 표시해주는부분*/
afx_msg LRESULT CsocketServerDlg::OnAcceptSocket(WPARAM wParam, LPARAM lParam)
{
	CString str;
	m_pClientSocket = (CClientSocket*)lParam;
	m_ptrClientSocketList.AddTail(m_pClientSocket);

	str.Format(_T("Client (%d)"), int(m_pClientSocket));
	m_list_client.InsertString(-1, str);

	m_pClientSocket = NULL;
	delete m_pClientSocket;
	return 0;
}
afx_msg LRESULT CsocketServerDlg::OnClientClose(WPARAM wParam, LPARAM lParam)
{
	CClientSocket *pClient = (CClientSocket*)lParam;
	CString str;
	UINT idx = 0;
	POSITION pos = m_ptrClientSocketList.Find(pClient);

	if (pos != NULL) {
		str.Format(_T("Client: (%d)"), (int)pClient);
		idx = m_list_client.SelectString(-1, (LPCTSTR)str);
		m_list_client.DeleteString(idx);

		//Cptrlist에서도 Client 완전 삭제
		m_ptrClientSocketList.RemoveAt(pos);
	}
	return 0;
}
/***************************************************/

/*클라이언트에서 보낸 메세지를 받아 서버메세지 창에 뿌림과동시에 클라이언트에도 뿌려줌*/
afx_msg LRESULT CsocketServerDlg::OnClientMsgRecv(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszStr = (LPCTSTR)lParam;

	//Broadcasting
	POSITION pos = m_ptrClientSocketList.GetHeadPosition();

	while (pos != NULL) {
		CClientSocket* pClient = 
			(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL) {
			//pClient->Send(lpszStr, lstrlen(lpszStr) * 2);
			ReceivMessages* temp = new ReceivMessages;
			temp->id = 100;
			temp->size = sizeof(MyMessage);
			_tcscpy(temp->msg.strBuffer, lpszStr);

			pClient->Send((char *)temp, sizeof(MyMessage));
		}
	}

	//m_list_msg에 메세지 추가
	m_list_msg.InsertString(-1, lpszStr);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	 
	return 0;

}

//클라이언트한테 받은 시작버튼값
afx_msg LRESULT CsocketServerDlg::OnClientStartRecv(WPARAM wParam, LPARAM lParam)
{
	MyStart* Start = (MyStart*)lParam;
				//전역변수 설정함
				m_Start = TRUE;
				//재시작할때 초기화
			
				m_Player1_Choice = 0;
				m_Player2_Choice = 0;
				
				m_SendResult1 = 0;
				m_SendResult2 = 0;
				m_SendResult3 = 0;


	//포트넘버 클라이언트로 보내기
	PortNum* PN = new PortNum;

		m_Start = Start->b_start;
		m_ClickCheck = Start->b_clickCheck;
	
		
		//Start->portNum;
		//Player1
		if (m_Player1 == 0) {
			PN->SendPlayerPortNum.PLAYER = 1;
			m_Player1 = Start->portNum;
			m_PortPrint.Format(_T("Player1Num : %d"), m_Player1);
			UpdateData(FALSE);

					/*생성된 포트번호 각 Player들에게 보낸다 */
					//보낼때는 겉에있는걸로보낸다
					PN->id = 500;
					PN->size = sizeof(MyPortNum);
					PN->SendPlayerPortNum.PlayerPortNum = m_Player1;
			
			POSITION pos = m_ptrClientSocketList.GetHeadPosition();
			while (pos != NULL) {
				CClientSocket* pClient =
					(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
				if (pClient != NULL) {
					pClient->Send((char *)PN, sizeof(PortNum));
				}
			}
					delete PN;

		
		}
		//Player2
		else if (m_Player2 == 0) {
			PN->SendPlayerPortNum.PLAYER = 2;

			m_Player2=Start->portNum;
			m_portPrint2.Format(_T("Player2Num : %d"), m_Player2);
			UpdateData(FALSE);

					/*생성된 포트번호 각 Player들에게 보낸다 */
					//보낼때는 겉에있는걸로보낸다

					PN->id = 500;
					PN->size = sizeof(MyPortNum);
					PN->SendPlayerPortNum.PlayerPortNum = m_Player2;

			POSITION pos = m_ptrClientSocketList.GetHeadPosition();
			while (pos != NULL) {
				CClientSocket* pClient =
					(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
				if (pClient != NULL) {
					pClient->Send((char *)PN, sizeof(PortNum));

				}
			}
					delete PN;
		}

		
			if (m_Start == TRUE && m_Player1 != 0) {
				m_start_msg.Format(_T("Player1가(이) 준비함"));
				UpdateData(FALSE);
			}
			if (m_Start == TRUE && m_Player2 != 0) {
				m_start_msg.Format(_T("Player2가(이) 준비함"));
				UpdateData(FALSE);
			}

			if ((m_Start == TRUE && m_Player1 != 0) && (m_Start == TRUE && m_Player2 != 0)) {

				m_start_msg.Format(_T("게임시작"));
				UpdateData(FALSE);
				SetTimer(START, 1000, NULL);
				m_ClickCheck = FALSE;
				m_ClickCheck2 = FALSE;
				//m_ClickCheck = FALSE;
			}
	return 0;
}


void CsocketServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((m_Start == TRUE && m_Player1 != 0) && (m_Start == TRUE && m_Player2 != 0)) {
		if (nIDEvent == START) {
			//m_TimeCount.Format(_T("%d"), m_startCount--);
			//	UpdateData(FALSE);
			//
			SendCount* SC = new SendCount;
			SC->id = 300;
			SC->size = sizeof(MyCount);
			SC->SendOnCount.OnCount = m_startCount--;


			POSITION pos = m_ptrClientSocketList.GetHeadPosition();

			while (pos != NULL) {
				CClientSocket* pClient =
					(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
				if (pClient != NULL) {
					pClient->Send((int *)SC, sizeof(SendCount));
				}
			}
			//pClient->Send((char *)SC, sizeof(SendCount));
			delete SC;


			// 0되면 초기화
			if (m_startCount < 0) {
					m_Start = FALSE;
					KillTimer(START);
					m_startCount = 5;
					/*초기화*/
					
					m_Player1 = 0;
					m_Player2 = 0;
					m_Player1_Choice = 0;
					m_Player2_Choice = 0;
					m_SendResult1 = 0;
					m_SendResult2 = 0;
					m_SendResult3 = 0;
					Invalidate();
			}
			if (m_ClickCheck == TRUE && m_ClickCheck2==TRUE) {
					KillTimer(START);
					m_startCount = 5;
					m_Start = FALSE;
					/*초기화*/
					
					m_Player1 = 0;
					m_Player2 = 0;
					m_Player1_Choice = 0;
					m_Player2_Choice = 0;
					m_SendResult1 = 0;
					m_SendResult2 = 0;
					m_SendResult3 = 0;
					Invalidate();
			}

		}
	}
	//Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}





//결과값 비교하기 함수
//결과처리는 별도 함수로 아님 한번에 ?
afx_msg LRESULT CsocketServerDlg::OnClientRSPRecv(WPARAM wParam, LPARAM lParam) 
{
	

	//MyStart* Start = (MyStart*)lParam;
		MyRock* RSP_Value1 = (MyRock*)lParam;
		MyScissors* RSP_Value2 = (MyScissors*)lParam;
		MyPaper* RSP_Value3 = (MyPaper*)lParam;


		if (m_Start == TRUE && RSP_Value1->PLAYER1==m_Player1 && RSP_Value2->PLAYER1 == m_Player1 && RSP_Value3->PLAYER1 == m_Player1) {

			if (RSP_Value1->InRock == 1) {
				m_PortPrint.Format(_T("Player1은 바위를 골랐다"));
				UpdateData(FALSE);
			
				m_Player1_Choice = RSP_Value1->InRock;
				//m_Player1_Choice = 1;
			}
			else if (RSP_Value2->InScissors == 2) {
				m_PortPrint.Format(_T("Player1은 가위를 골랐다"));
				UpdateData(FALSE);
			
				m_Player1_Choice = RSP_Value2->InScissors;
				//m_Player1_Choice = 2;
			}
			else if (RSP_Value3->InPaper == 3) {
				m_PortPrint.Format(_T("Player1은 보를 골랐다"));
				UpdateData(FALSE);

				m_Player1_Choice = RSP_Value3->InPaper;
				//m_Player1_Choice = 3;
			}
			else {
				m_PortPrint.Format(_T("P1 에러에러"));
				UpdateData(FALSE);
			}
			m_ClickCheck = TRUE;
		}

	 if (m_Start == TRUE && RSP_Value1->PLAYER2 == m_Player2 && RSP_Value2->PLAYER2 == m_Player2 && RSP_Value3->PLAYER2 == m_Player2) {
			
			m_ClickCheck = TRUE;

			if (RSP_Value1->InRock == 1) {
				m_portPrint2.Format(_T("Player2은 바위를 골랐다"));
				UpdateData(FALSE);

				m_Player2_Choice = RSP_Value1->InRock;
			
			}
			else if (RSP_Value2->InScissors == 2) {
				m_portPrint2.Format(_T("Player2은 가위를 골랐다"));
				UpdateData(FALSE);

				m_Player2_Choice = RSP_Value2->InScissors;

			}
			else if (RSP_Value3->InPaper == 3) {
				m_portPrint2.Format(_T("Player2은 보를 골랐다"));
				UpdateData(FALSE);

				m_Player2_Choice = RSP_Value3->InPaper;
				
			}
			else {
				m_portPrint2.Format(_T("P2 에러에러"));
				UpdateData(FALSE);
			}
			m_ClickCheck2 = TRUE;
		}

		/*상대 value 보내기*/
	 
		if (m_Player1_Choice != NULL) {
			Enemy1_Values();
			
			
		 }
		if (m_Player2_Choice != NULL) {
			Enemy2_Values();
			
	   	}
		CompareResult();
		return 0;
}
/*상대방 초이스 보내기*/

void CsocketServerDlg::Enemy1_Values() {
	


	//m_ClickCheck = TRUE;
	POSITION pos = m_ptrClientSocketList.GetHeadPosition();


	SendMyEnemy1Value* SEV1 = new SendMyEnemy1Value;
	SEV1->id = 710;
	SEV1->size = sizeof(MyEnemy1Value);
	SEV1->Enemy1Value.Enemy1Value = m_Player2_Choice;
	SEV1->Enemy1Value.Enemy1Port = m_Player1;

	while (pos != NULL)
	{
		CClientSocket* pClient =
			(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL) {
			pClient->Send((char *)SEV1, sizeof(SendMyEnemy1Value));
		}
	}
	
	
	delete SEV1;
	
	CompareResult();
	//m_ClickCheck = FALSE;

}
void CsocketServerDlg::Enemy2_Values() {


//	m_ClickCheck = TRUE;
	POSITION pos = m_ptrClientSocketList.GetHeadPosition();

	SendMyEnemy2Value* SEV2 = new SendMyEnemy2Value;
	SEV2->id = 720;
	SEV2->size = sizeof(MyEnemy2Value);
	SEV2->Enemy2Value.Enemy2Value = m_Player1_Choice;
	SEV2->Enemy2Value.Enemy2Port = m_Player2;

	//POSITION pos = m_ptrClientSocketList.GetHeadPosition();
	while (pos != NULL)
	{
		CClientSocket* pClient =
			(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL) {
			pClient->Send((char *)SEV2, sizeof(SendMyEnemy2Value));
		}
	}
	delete SEV2;
	CompareResult();
//	m_ClickCheck = FALSE;

}


void CsocketServerDlg::CompareResult() {



	if (m_Player1_Choice == m_Player2_Choice) {
		m_start_msg.Format(_T("비겼다"));
		UpdateData(FALSE);

		//Client로 갈 최종결과값
		m_SendResult3 = 5;

	}
	if ((m_Player1_Choice == 1 && m_Player2_Choice == 2) || (m_Player1_Choice == 2 && m_Player2_Choice == 3) || (m_Player1_Choice == 3 && m_Player2_Choice == 1)) {
		m_PortPrint.Format(_T("Player1이 승리"));
		UpdateData(FALSE);
		//Client로 갈 최종결과값
		m_SendResult1 = 1;
	}
	else if ((m_Player1_Choice == 1 && m_Player2_Choice == 3) || (m_Player1_Choice == 2 && m_Player2_Choice == 1) || (m_Player1_Choice == 3 && m_Player2_Choice == 2)) {
		m_PortPrint.Format(_T("Player1이 패배"));
		UpdateData(FALSE);
		//Client로 갈 최종결과값
		m_SendResult1 = 2;
	}


	if ((m_Player2_Choice==1 && m_Player1_Choice==2) || (m_Player2_Choice == 2 && m_Player1_Choice == 3) || (m_Player2_Choice == 3 && m_Player1_Choice == 1)) {
		m_portPrint2.Format(_T("Player2이 승리"));
		UpdateData(FALSE);
		//Client로 갈 최종결과값
		m_SendResult2 = 3;
	}
	else if ((m_Player2_Choice == 1 && m_Player1_Choice == 3) || (m_Player2_Choice == 2 && m_Player1_Choice == 1) || (m_Player2_Choice == 3 && m_Player1_Choice == 2)) {
		m_portPrint2.Format(_T("Player2이 패배"));
		UpdateData(FALSE);
		//Client로 갈 최종결과값
		m_SendResult2 = 4;
	}

	/*Client로 갈 최종결과값 보내는 코드*/
	
	SendMyResult* SR = new SendMyResult;

	SR->id = 600;
	SR->size = sizeof(MyResult);

	SR->SendOutResult.Player1Result = m_SendResult1;
	SR->SendOutResult.Player2Result = m_SendResult2;
	SR->SendOutResult.Playdraw = m_SendResult3;


	
	POSITION pos = m_ptrClientSocketList.GetHeadPosition();
	
	while (pos != NULL) {
		CClientSocket* pClient =
			(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		
		if (pClient != NULL) {
			pClient->Send((char *)SR, sizeof(SendMyResult));
		}
	}
	delete SR;


}


void CsocketServerDlg::OnEnChangeEditPortnum()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CsocketServerDlg::OnEnChangeEditPortnum2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

//클라이언트가 서버한테보낸거 여기다가 뿌려줌 상태메세지 ㅅㅂ
void CsocketServerDlg::OnChangeEditTorf()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
	/*각 상대방 초이스 보내자*/

	/*
	SendMyEnemyValue* SEV = new SendMyEnemyValue;
	SEV->id = 700;
	SEV->size = sizeof(MyEnemyValue);

	SEV->EnemyValue.Enemy1Value = m_Player2_Choice;
	SEV->EnemyValue.Enemy2Value = m_Player1_Choice;
	SEV->EnemyValue.Enemy1Port = m_Player1;
	SEV->EnemyValue.Enemy2Port = m_Player2;


	POSITION pos = m_ptrClientSocketList.GetHeadPosition();
	while (pos != NULL)
	{
	CClientSocket* pClient =
	(CClientSocket*)m_ptrClientSocketList.GetNext(pos);
	if (pClient != NULL) {
	pClient->Send((char *)SEV, sizeof(SendMyEnemyValue));
	}

	}
	delete SEV;
	*/

	/*SendMyEnemy1Value 구조체 삽입자리 */
