#include "socket1.h"
#include "framework.h"
#include "S_udpDlg.h"
#include "S_udp.h"

Socket1::Socket1() {

}

Socket1::~Socket1() {

}

//�����rec����
void Socket1::OnReceive(int nErrorCode) {
	CSudpDlg* dig = (CSudpDlg*)theApp.m_pMainWnd; //��ȡ�Ի�����
	TCHAR buff[4096];
	CString GetIP;
	UINT GetPort;
	ReceiveFrom(buff, 4096, GetIP, GetPort);
	CString data(buff);
	CString temp = data;

	dig->update(dig->s_date, dig->s_time);

	CString Answer = _T("��������");
	data.MakeLower();

	if (data == "time")
		Answer = dig->s_time;
	if (data == "date")
		Answer = dig->s_date;
	if (data == "mfc")
		Answer = "Hello World";

	//��Ӧ�ͻ��˳���
	SendToEx(Answer.GetBuffer(), (Answer.GetLength() + 1) * sizeof(WCHAR), GetPort, GetIP);
	CString record;
	record.Format(L":�˿�2000���յ�IP=%s Port=%u����,��������Ϊ[%s],��ӦΪ[%s]", GetIP, GetPort, temp, Answer);
	dig->s_log.AddString(dig->s_date + _T(" ") + dig->s_time + record);

	CAsyncSocket::OnReceive(nErrorCode);
}