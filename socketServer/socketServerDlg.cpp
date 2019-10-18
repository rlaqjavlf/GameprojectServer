
// socketServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "socketServer.h"
#include "socketServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PORT 9999 //������ ��Ʈ����

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CsocketServerDlg ��ȭ ����



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

	//���۹�ư
	ON_MESSAGE(WM_Start_Bool, &CsocketServerDlg::OnClientStartRecv)
	//��������
	ON_MESSAGE(WM_RSP_rock_RECV, &CsocketServerDlg::OnClientRSPRecv)
	//��������
	ON_MESSAGE(WM_RSP_scissors_RECV, &CsocketServerDlg::OnClientRSPRecv)
	//�� ����
	ON_MESSAGE(WM_RSP_paper_RECV, &CsocketServerDlg::OnClientRSPRecv)

	ON_EN_CHANGE(IDC_EDIT_TorF, &CsocketServerDlg::OnChangeEditTorf)
	
	ON_WM_TIMER()
	
	ON_EN_CHANGE(IDC_EDIT_PortNum, &CsocketServerDlg::OnEnChangeEditPortnum)
	ON_EN_CHANGE(IDC_EDIT_PortNum2, &CsocketServerDlg::OnEnChangeEditPortnum2)
END_MESSAGE_MAP()


// CsocketServerDlg �޽��� ó����

BOOL CsocketServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_pServerSocket = new CServerSocket;
	m_pServerSocket->SetWnd(this->m_hWnd);

	m_pServerSocket->Create(PORT);
	m_pServerSocket->Listen();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CsocketServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CsocketServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*���� Ŭ���̾�Ʈ â���� Ŭ���̾�Ʈ ǥ�����ִºκ�*/
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

		//Cptrlist������ Client ���� ����
		m_ptrClientSocketList.RemoveAt(pos);
	}
	return 0;
}
/***************************************************/

/*Ŭ���̾�Ʈ���� ���� �޼����� �޾� �����޼��� â�� �Ѹ������ÿ� Ŭ���̾�Ʈ���� �ѷ���*/
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

	//m_list_msg�� �޼��� �߰�
	m_list_msg.InsertString(-1, lpszStr);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	 
	return 0;

}

//Ŭ���̾�Ʈ���� ���� ���۹�ư��
afx_msg LRESULT CsocketServerDlg::OnClientStartRecv(WPARAM wParam, LPARAM lParam)
{
	MyStart* Start = (MyStart*)lParam;
				//�������� ������
				m_Start = TRUE;
				//������Ҷ� �ʱ�ȭ
			
				m_Player1_Choice = 0;
				m_Player2_Choice = 0;
				
				m_SendResult1 = 0;
				m_SendResult2 = 0;
				m_SendResult3 = 0;


	//��Ʈ�ѹ� Ŭ���̾�Ʈ�� ������
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

					/*������ ��Ʈ��ȣ �� Player�鿡�� ������ */
					//�������� �ѿ��ִ°ɷκ�����
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

					/*������ ��Ʈ��ȣ �� Player�鿡�� ������ */
					//�������� �ѿ��ִ°ɷκ�����

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
				m_start_msg.Format(_T("Player1��(��) �غ���"));
				UpdateData(FALSE);
			}
			if (m_Start == TRUE && m_Player2 != 0) {
				m_start_msg.Format(_T("Player2��(��) �غ���"));
				UpdateData(FALSE);
			}

			if ((m_Start == TRUE && m_Player1 != 0) && (m_Start == TRUE && m_Player2 != 0)) {

				m_start_msg.Format(_T("���ӽ���"));
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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


			// 0�Ǹ� �ʱ�ȭ
			if (m_startCount < 0) {
					m_Start = FALSE;
					KillTimer(START);
					m_startCount = 5;
					/*�ʱ�ȭ*/
					
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
					/*�ʱ�ȭ*/
					
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





//����� ���ϱ� �Լ�
//���ó���� ���� �Լ��� �ƴ� �ѹ��� ?
afx_msg LRESULT CsocketServerDlg::OnClientRSPRecv(WPARAM wParam, LPARAM lParam) 
{
	

	//MyStart* Start = (MyStart*)lParam;
		MyRock* RSP_Value1 = (MyRock*)lParam;
		MyScissors* RSP_Value2 = (MyScissors*)lParam;
		MyPaper* RSP_Value3 = (MyPaper*)lParam;


		if (m_Start == TRUE && RSP_Value1->PLAYER1==m_Player1 && RSP_Value2->PLAYER1 == m_Player1 && RSP_Value3->PLAYER1 == m_Player1) {

			if (RSP_Value1->InRock == 1) {
				m_PortPrint.Format(_T("Player1�� ������ �����"));
				UpdateData(FALSE);
			
				m_Player1_Choice = RSP_Value1->InRock;
				//m_Player1_Choice = 1;
			}
			else if (RSP_Value2->InScissors == 2) {
				m_PortPrint.Format(_T("Player1�� ������ �����"));
				UpdateData(FALSE);
			
				m_Player1_Choice = RSP_Value2->InScissors;
				//m_Player1_Choice = 2;
			}
			else if (RSP_Value3->InPaper == 3) {
				m_PortPrint.Format(_T("Player1�� ���� �����"));
				UpdateData(FALSE);

				m_Player1_Choice = RSP_Value3->InPaper;
				//m_Player1_Choice = 3;
			}
			else {
				m_PortPrint.Format(_T("P1 ��������"));
				UpdateData(FALSE);
			}
			m_ClickCheck = TRUE;
		}

	 if (m_Start == TRUE && RSP_Value1->PLAYER2 == m_Player2 && RSP_Value2->PLAYER2 == m_Player2 && RSP_Value3->PLAYER2 == m_Player2) {
			
			m_ClickCheck = TRUE;

			if (RSP_Value1->InRock == 1) {
				m_portPrint2.Format(_T("Player2�� ������ �����"));
				UpdateData(FALSE);

				m_Player2_Choice = RSP_Value1->InRock;
			
			}
			else if (RSP_Value2->InScissors == 2) {
				m_portPrint2.Format(_T("Player2�� ������ �����"));
				UpdateData(FALSE);

				m_Player2_Choice = RSP_Value2->InScissors;

			}
			else if (RSP_Value3->InPaper == 3) {
				m_portPrint2.Format(_T("Player2�� ���� �����"));
				UpdateData(FALSE);

				m_Player2_Choice = RSP_Value3->InPaper;
				
			}
			else {
				m_portPrint2.Format(_T("P2 ��������"));
				UpdateData(FALSE);
			}
			m_ClickCheck2 = TRUE;
		}

		/*��� value ������*/
	 
		if (m_Player1_Choice != NULL) {
			Enemy1_Values();
			
			
		 }
		if (m_Player2_Choice != NULL) {
			Enemy2_Values();
			
	   	}
		CompareResult();
		return 0;
}
/*���� ���̽� ������*/

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
		m_start_msg.Format(_T("����"));
		UpdateData(FALSE);

		//Client�� �� ���������
		m_SendResult3 = 5;

	}
	if ((m_Player1_Choice == 1 && m_Player2_Choice == 2) || (m_Player1_Choice == 2 && m_Player2_Choice == 3) || (m_Player1_Choice == 3 && m_Player2_Choice == 1)) {
		m_PortPrint.Format(_T("Player1�� �¸�"));
		UpdateData(FALSE);
		//Client�� �� ���������
		m_SendResult1 = 1;
	}
	else if ((m_Player1_Choice == 1 && m_Player2_Choice == 3) || (m_Player1_Choice == 2 && m_Player2_Choice == 1) || (m_Player1_Choice == 3 && m_Player2_Choice == 2)) {
		m_PortPrint.Format(_T("Player1�� �й�"));
		UpdateData(FALSE);
		//Client�� �� ���������
		m_SendResult1 = 2;
	}


	if ((m_Player2_Choice==1 && m_Player1_Choice==2) || (m_Player2_Choice == 2 && m_Player1_Choice == 3) || (m_Player2_Choice == 3 && m_Player1_Choice == 1)) {
		m_portPrint2.Format(_T("Player2�� �¸�"));
		UpdateData(FALSE);
		//Client�� �� ���������
		m_SendResult2 = 3;
	}
	else if ((m_Player2_Choice == 1 && m_Player1_Choice == 3) || (m_Player2_Choice == 2 && m_Player1_Choice == 1) || (m_Player2_Choice == 3 && m_Player1_Choice == 2)) {
		m_portPrint2.Format(_T("Player2�� �й�"));
		UpdateData(FALSE);
		//Client�� �� ���������
		m_SendResult2 = 4;
	}

	/*Client�� �� ��������� ������ �ڵ�*/
	
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CsocketServerDlg::OnEnChangeEditPortnum2()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

//Ŭ���̾�Ʈ�� �������׺����� ����ٰ� �ѷ��� ���¸޼��� ����
void CsocketServerDlg::OnChangeEditTorf()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
	/*�� ���� ���̽� ������*/

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

	/*SendMyEnemy1Value ����ü �����ڸ� */
