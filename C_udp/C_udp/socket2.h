#pragma once

#include <afxsock.h> 

class Socket2 :public CAsyncSocket {
public:
	Socket2();
	virtual ~Socket2();
	virtual void OnReceive(int nErrorCode);
public:
	CString GetBuff;//数据报
	CString GetIp;//从主机得到的IP地址
	UINT GetPort;//端口
};