#pragma once

// CClientSocket command target

class CClientSocket : public CAsyncSocket
{
private:

public:
	CClientSocket();
	virtual ~CClientSocket();
	void OnReceive(int nErrorCode);
	void OnConnect(int nErrorCode);
	void OnClose(int nErrorCode);
};


