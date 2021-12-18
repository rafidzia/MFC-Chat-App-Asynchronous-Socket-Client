
// MFCSocketClientDemoDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCSocketClientDemo.h"
#include "MFCSocketClientDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSocketClientDemoDlg dialog



CMFCSocketClientDemoDlg::CMFCSocketClientDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSOCKETCLIENTDEMO_DIALOG, pParent)
	, m_server(_T(""))
	, m_port(0)
	, m_message(_T(""))
	, m_username(_T(""))
	, m_strSliderVal(_T("110"))
	, m_Status1(_T("Disconnected"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSocketClientDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOST_SERVER, m_server);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_message);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richEdit);
	DDX_Text(pDX, IDC_USERNAME, m_username);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderCtrl);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_strSliderVal);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_Status1);
}

BEGIN_MESSAGE_MAP(CMFCSocketClientDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCSocketClientDemoDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCSocketClientDemoDlg::OnBnClickedButtonSend)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMFCSocketClientDemoDlg::OnBnClickedButtonDisconnect)
END_MESSAGE_MAP()


// CMFCSocketClientDemoDlg message handlers

BOOL CMFCSocketClientDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_sliderCtrl.SetRange(110, 220, TRUE);
	m_sliderCtrl.SetPos(110);
	CFont font1;
	font1.CreatePointFont(110, L"Times New Roman", NULL);
	m_richEdit.SetFont(&font1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCSocketClientDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCSocketClientDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCSocketClientDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCSocketClientDemoDlg::appendtoRichEdit(int code, CString message)
{
	int nOldLines = m_richEdit.GetLineCount();
	CString updatetext;
	if (code == 0) {
		updatetext.Format(L"me > %s\n", message);
	}
	else 
	{
		updatetext.Format(L"%s\n", message);
	}
	long nStart, nEnd;
	m_richEdit.GetSel(nStart, nEnd);
	m_richEdit.SetSel(nEnd, nEnd);
	m_richEdit.ReplaceSel(updatetext);
	int nNewLines = m_richEdit.GetLineCount();
	int nScroll = nNewLines - nOldLines;
	m_richEdit.LineScroll(nScroll);
}

void CClientSocket::OnReceive(int nErrorCode) {
	char buff[1000];
	int ibuf = Receive(buff, 1000);
	buff[ibuf] = '\0';
	CString out(buff);
	//Append to RichEdit
	//((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_richEdit;
	int nOldLines = ((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_richEdit.GetLineCount();
	long nStart, nEnd;
	((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_richEdit.GetSel(nStart, nEnd);
	((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_richEdit.SetSel(nEnd, nEnd);
	((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_richEdit.ReplaceSel(out);
	int nNewLines = ((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_richEdit.GetLineCount();
	int nScroll = nNewLines - nOldLines;
	((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_richEdit.LineScroll(nScroll);
	//AfxMessageBox(out);
}

void CClientSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0) {
		CString message = _T("User: ");
		message += ((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_username.GetString();
		((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_Status1.Format(L"Connected");
		((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->UpdateData(FALSE);
		if (((CMFCSocketClientDemoDlg*)AfxGetMainWnd())->m_clientSocket.Send(message.GetBuffer(message.GetLength()), message.GetLength() * 2)) {
		}
		else {
			AfxMessageBox(L"Failed to send message");
		}
	}
	
}

void CClientSocket::OnClose(int nErrorCode)
{
	//AfxMessageBox(L"Disconnect");
	CAsyncSocket::OnClose(nErrorCode);

	while (1)
	{
		char buffer1[1000];
		// m_tempBuffer is my internal receive buffer
		int numBytes = Receive(buffer1, 1000);
		if ((SOCKET_ERROR == numBytes) || (0 == numBytes))
		{
			break;
		}
		// ... process the remaining data here
	}
	// .. more app close stuff here
}


void CMFCSocketClientDemoDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	m_clientSocket.Create();
	m_clientSocket.Connect(m_server, m_port);
	/*if (m_clientSocket.Connect(m_server, m_port)) {
		//AfxMessageBox(L"Connection Successfull");
		//receiveMessage();
		CString message = _T("User: Alan14");
		if (m_clientSocket.Send(message.GetBuffer(message.GetLength()), message.GetLength() * 2)) {
			appendtoRichEdit(0, m_message.GetString());
			SetDlgItemText(IDC_EDIT_MESSAGE, L"");
		}
		else {
			AfxMessageBox(L"Failed to send message");
		}
	}
	else {
		AfxMessageBox(L"Connection Failed");
	}
	DWORD error = GetLastError();*/
}

void CMFCSocketClientDemoDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_clientSocket.Send(m_message.GetBuffer(m_message.GetLength()), m_message.GetLength() * 2 )) {
	   appendtoRichEdit(0, m_message.GetString());
	   SetDlgItemText(IDC_EDIT_MESSAGE, L""	);
   }else {
      AfxMessageBox(L"Failed to send message");
   }
}



void CMFCSocketClientDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar *)&m_sliderCtrl) {
		int value = m_sliderCtrl.GetPos();
		m_strSliderVal.Format(_T("%d"), value);
		CFont font1;
		font1.CreatePointFont(value, L"Times New Roman", NULL);
		m_richEdit.SetFont(&font1);
		UpdateData(FALSE);
	}
	else {
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}


void CMFCSocketClientDemoDlg::OnBnClickedButtonDisconnect()
{
	// TODO: Add your control notification handler code here
	//m_clientSocket.ShutDown(2);	// Stop both sending and receiving data.
	m_clientSocket.Close();
	m_Status1.Format(L"Disconnected");
	UpdateData(FALSE);
	appendtoRichEdit(1, _T("You are disconnected!!!"));
}
