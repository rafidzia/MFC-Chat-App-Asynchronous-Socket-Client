
// MFCSocketClientDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCSocketClientDemoApp:
// See MFCSocketClientDemo.cpp for the implementation of this class
//

class CMFCSocketClientDemoApp : public CWinApp
{
public:
	CMFCSocketClientDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCSocketClientDemoApp theApp;
