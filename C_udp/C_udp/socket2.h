#pragma once

#include <afxsock.h> 

class Socket2 :public CAsyncSocket {
public:
	Socket2();
	virtual ~Socket2();
	virtual void OnReceive(int nErrorCode);
public:
	CString GetBuff;//���ݱ�
	CString GetIp;//�������õ���IP��ַ
	UINT GetPort;//�˿�
};