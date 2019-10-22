#include "socket2.h"
#include "C_udp.h"
#include "C_udpDlg.h"
#include "framework.h"

Socket2::Socket2() {
	//��ʼ������
	GetBuff.Empty();
	GetIp.Empty();
	GetPort = 0;
}

Socket2::~Socket2() {

}

void Socket2::OnReceive(int nErrorCode) {
	TCHAR buff[4096];  //���ڻ����������������ص����ݱ�
	ReceiveFrom(buff, sizeof(buff), GetIp, GetPort);	//��������������
	CString data(buff);
	GetBuff = data;

	CCudpDlg* dig = (CCudpDlg*)theApp.m_pMainWnd;
	dig->c_sresponse = GetBuff;
	dig->UpdateData(false);

	CAsyncSocket::OnReceive(nErrorCode);
}