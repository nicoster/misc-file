#include <afxwin.h>         // MFC core and standard components
#include <afxsock.h>		// MFC socket extensions
#include <iostream>
#include <string>
using namespace std;

const int BUF_LEN = 1024;

class CDataSocket : public CAsyncSocket
{
	void OnConnect(int nErrorCode)
	{
		cout<<"OnConnect " << nErrorCode << endl;
		if (nErrorCode != 0)	// connect failed, quit
			PostQuitMessage(nErrorCode);
	}
	void OnReceive(int nErrorCode)
	{
		BYTE byBuf[BUF_LEN + 1];
		
		int nRecv = Receive(byBuf, BUF_LEN);
		do
		{
			cout<<"Recv "<< nRecv << endl;
			byBuf[nRecv] = '\0';
			cout<<byBuf<<endl;
		}while((nRecv = Receive(byBuf, BUF_LEN)) == BUF_LEN);
	}	
	void OnClose(int nErrorCode)
	{
		cout<<"OnClose "<< nErrorCode << endl;
	}
};

class CListenSocket : public CAsyncSocket
{
	void OnAccept(int nErrorCode)
	{
		cout<<"OnAccept "<< nErrorCode << endl;
		Accept(m_datasock);
		m_datasock.AsyncSelect(FD_CONNECT | FD_READ | FD_CLOSE);
	}
	
	CDataSocket m_datasock;
};

void main(int argc, char** argv)
{
	bool bServer = !(argc<=1);
	AfxSocketInit();
	CListenSocket sock;
	CDataSocket sock2;
	CAsyncSocket* psock = bServer ? (CAsyncSocket*)&sock : &sock2;
	
	if (bServer)
	{
		psock->Create(5000);
		psock->AsyncSelect(FD_ACCEPT);
		psock->Listen();
	}
	else
	{
		psock->Create();
		psock->Connect("127.0.0.1", 5000);
	}
	
	while(1)
	{
		MSG msg;
		while(PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, 0, 0, 0))
				DispatchMessage(&msg);
			else exit(msg.wParam);
		}
			
		string str;
		if (cin.gcount())
		{
			cin>>str;
			psock->Send(str.c_str(), str.size());
		}
	}

}
