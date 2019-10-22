#include "socket1.h"
#include "framework.h"
#include "S_udpDlg.h"
#include "S_udp.h"

Socket1::Socket1() {

}

Socket1::~Socket1() {

}

//服务端rec函数
void Socket1::OnReceive(int nErrorCode) {
	CSudpDlg* dig = (CSudpDlg*)theApp.m_pMainWnd; //获取对话框句柄
	TCHAR buff[4096];
	CString GetIP;
	UINT GetPort;
	ReceiveFrom(buff, 4096, GetIP, GetPort);
	CString data(buff);
	CString temp = data;

	dig->update(dig->s_date, dig->s_time);

	CString Answer = _T("错误请求");
	data.MakeLower();

	if (data == "time")
		Answer = dig->s_time;
	if (data == "date")
		Answer = dig->s_date;
	if (data == "mfc")
		Answer = "Hello World";

	//响应客户端程序
	SendToEx(Answer.GetBuffer(), (Answer.GetLength() + 1) * sizeof(WCHAR), GetPort, GetIP);
	CString record;
	record.Format(L":端口2000，收到IP=%s Port=%u请求,请求命令为[%s],响应为[%s]", GetIP, GetPort, temp, Answer);
	dig->s_log.AddString(dig->s_date + _T(" ") + dig->s_time + record);

	CAsyncSocket::OnReceive(nErrorCode);
}