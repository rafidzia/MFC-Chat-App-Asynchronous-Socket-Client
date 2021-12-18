
// MFCSocketClientDemoDlg.h : header file
//

#pragma once
#include "CClientSocket.h";

// CMFCSocketClientDemoDlg dialog
class CMFCSocketClientDemoDlg : public CDialogEx
{
// Construction
public:
	CMFCSocketClientDemoDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSOCKETCLIENTDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();	
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	CString m_server;
	UINT m_port;
	CString m_message;
	afx_msg void OnBnClickedButtonSend();
	CRichEditCtrl m_richEdit;
	virtual void appendtoRichEdit(int code, CString message);
	CClientSocket m_clientSocket;
	CString m_username;
	CSliderCtrl m_sliderCtrl;
	CString m_strSliderVal;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CString m_Status1;
	afx_msg void OnBnClickedButtonDisconnect();
};