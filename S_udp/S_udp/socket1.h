#pragma once
#include <afxsock.h> 
//

class Socket1 :public CAsyncSocket {
public:
	Socket1();
	virtual ~Socket1();
	virtual void OnReceive(int nErrorCode);
	//��Ҫ�õ��ľ����������
};