#include "socket2.h"
#include "C_udp.h"
#include "C_udpDlg.h"
#include "framework.h"

Socket2::Socket2() {
	//初始化变量
	GetBuff.Empty();
	GetIp.Empty();
	GetPort = 0;
}

Socket2::~Socket2() {

}

void Socket2::OnReceive(int nErrorCode) {
	TCHAR buff[4096];  //用于缓冲区接收主机返回的数据报
	ReceiveFrom(buff, sizeof(buff), GetIp, GetPort);	//从主机接收数据
	CString data(buff);
	GetBuff = data;

	CCudpDlg* dig = (CCudpDlg*)theApp.m_pMainWnd;
	dig->c_sresponse = GetBuff;
	dig->UpdateData(false);

	CAsyncSocket::OnReceive(nErrorCode);
}